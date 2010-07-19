/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010  Christian Mauduit <ufoot@ufoot.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  

  Liquid War 6 homepage : http://www.gnu.org/software/liquidwar6/
  Contact author        : ufoot@ufoot.org
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "net.h"

#define TEST_ARGC 1
#define TEST_ARGV0 "prog"

#define TEST_UNREACHABLE_IP "209.85.135.99"
#define TEST_UNREACHABLE_PORT 8000
#define TEST_TCP_DELAY 0.1f
#define TEST_UDP_DELAY 1.0f
#define TEST_BUF1_STR "foo"
#define TEST_LINE1 "foo"
#define TEST_LINE2 "a\tb\tc"
#define TEST_LINE3 "azerty azerty azerty azerty azerty azerty azerty azerty azerty azerty azerty azerty"

/*
 * Testing functions in if.c
 */
static int
test_if ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    char *ip = NULL;
    char *public_url = NULL;

    lw6sys_log (LW6SYS_LOG_NOTICE, _("trying to guess local interface IP"));
    ip = lw6net_if_guess_local ();
    if (ip)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE, _("local interface IP is \"%s\""), ip);
	LW6SYS_FREE (ip);
      }
    else
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _
		    ("unable to guess local interface, this is a problem only if machine *really* has no network available"));
      }
    public_url = lw6net_if_guess_public_url (LW6NET_DEFAULT_PORT);
    if (public_url)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("public URL on default port would be \"%s\""),
		    public_url);
	LW6SYS_FREE (public_url);
      }
    else
      {
	lw6sys_log (LW6SYS_LOG_WARNING, _("unable to guess public URL"));
	ret = 0;
      }
    public_url = lw6net_if_guess_public_url (LW6NET_HTTP_PORT);
    if (public_url)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("public URL on http port would be \"%s\""), public_url);
	LW6SYS_FREE (public_url);
      }
    else
      {
	lw6sys_log (LW6SYS_LOG_WARNING, _("unable to guess public URL"));
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

static int
prepare_2_tcp_socks (int *sock1, int *sock2)
{
  int ret = 0;
  int listening_sock = -1;
  int connect_sock = -1;
  int accept_sock = -1;
  void *handler = NULL;
  char *accept_ip = NULL;
  int accept_port = 0;

  lw6sys_log (LW6SYS_LOG_NOTICE, _("listening on port %d (TCP)"),
	      LW6NET_DEFAULT_PORT);
  listening_sock =
    lw6net_tcp_listen (LW6NET_ADDRESS_ANY, LW6NET_DEFAULT_PORT);
  if (listening_sock >= 0)
    {
      lw6sys_log (LW6SYS_LOG_NOTICE,
		  _("TCP socket %d listening on port %d"), listening_sock,
		  LW6NET_DEFAULT_PORT);

      lw6sys_log (LW6SYS_LOG_NOTICE,
		  _("trying to connect on localhost %s:%d"),
		  LW6NET_ADDRESS_LOOPBACK, LW6NET_DEFAULT_PORT);
      handler =
	lw6net_tcp_async_connect_init (LW6NET_ADDRESS_LOOPBACK,
				       LW6NET_DEFAULT_PORT);

      if (handler)
	{
	  while (!(lw6net_tcp_async_connect_get (&connect_sock, handler)))
	    {
	      // loop until connect exits...
	      lw6sys_sleep (TEST_TCP_DELAY);
	    }
	  lw6net_tcp_async_connect_exit (handler);
	  if (connect_sock >= 0)
	    {
	      lw6sys_log (LW6SYS_LOG_NOTICE,
			  _("TCP socket %d connected on %s:%d"),
			  connect_sock, LW6NET_ADDRESS_LOOPBACK,
			  LW6NET_DEFAULT_PORT);
	      accept_sock =
		lw6net_tcp_accept (&accept_ip,
				   &accept_port, listening_sock,
				   TEST_TCP_DELAY);
	      if (accept_sock >= 0)
		{
		  lw6sys_log (LW6SYS_LOG_NOTICE,
			      _("TCP socket %d accepted %s:%d"),
			      accept_sock, accept_ip, accept_port);
		}
	      if (accept_ip)
		{
		  LW6SYS_FREE (accept_ip);
		}
	    }
	}
    }
  if (accept_sock >= 0 && connect_sock >= 0)
    {
      (*sock1) = accept_sock;
      (*sock2) = connect_sock;
      ret = 1;
    }
  else
    {
      if (accept_sock >= 0)
	{
	  lw6net_socket_close (accept_sock);
	}
      if (connect_sock >= 0)
	{
	  lw6net_socket_close (connect_sock);
	}
      (*sock1) = (*sock2) = -1;
    }
  if (listening_sock >= 0)
    {
      lw6net_socket_close (listening_sock);
    }

  return ret;
}

/*
 * Testing functions in tcp.c
 */
static int
test_tcp ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    int sock1 = -1;
    int sock2 = -1;
    int ret_tmp = 0;
    char *buf1_send = NULL;
    char *buf1_recv = NULL;
    int size;
    int received;

    /*
       lw6sys_log (LW6SYS_LOG_NOTICE,
       _("trying to connect on unreachable point %s:%d"),
       TEST_UNREACHABLE_IP, TEST_UNREACHABLE_PORT);
       handler =
       lw6net_tcp_async_connect_init (TEST_UNREACHABLE_IP,
       TEST_UNREACHABLE_PORT);
     */
    if (prepare_2_tcp_socks (&sock1, &sock2))
      {

	size = strlen (TEST_BUF1_STR) + 1;
	buf1_send = lw6sys_str_copy (TEST_BUF1_STR);
	buf1_recv = LW6SYS_CALLOC (strlen (TEST_BUF1_STR) + 1);

	if (buf1_send && buf1_recv)
	  {
	    if (lw6net_tcp_send (sock1, buf1_send, size, TEST_TCP_DELAY, 1))
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE,
			    _("sent \"%s\" on TCP socket %d"),
			    buf1_send, sock1);
		received =
		  lw6net_tcp_peek (sock2, NULL, size, TEST_TCP_DELAY);
		lw6sys_log (LW6SYS_LOG_NOTICE,
			    _
			    ("%d bytes available on TCP socket %d"),
			    received, sock2);
		if (received == size
		    && lw6net_tcp_recv (sock2,
					buf1_recv, size, TEST_TCP_DELAY, 1))
		  {
		    lw6sys_log (LW6SYS_LOG_NOTICE,
				_
				("received \"%s\" on TCP socket %d"),
				buf1_recv, sock2);
		    ret_tmp = 1;
		  }
	      }
	  }
      }
    if (!ret_tmp)
      {
	ret = 0;
      }

    if (buf1_send)
      {
	LW6SYS_FREE (buf1_send);
      }
    if (buf1_recv)
      {
	LW6SYS_FREE (buf1_recv);
      }
    if (sock1 >= 0)
      {
	lw6net_socket_close (sock1);
      }
    if (sock2 >= 0)
      {
	lw6net_socket_close (sock2);
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

static int
prepare_2_udp_socks (int *sock1, int *sock2)
{
  int ret = 0;
  int server_sock = -1;
  int client_sock = -1;

  lw6sys_log (LW6SYS_LOG_NOTICE, _("listening on port %d (UDP)"),
	      LW6NET_DEFAULT_PORT);
  server_sock = lw6net_udp_server (LW6NET_ADDRESS_ANY, LW6NET_DEFAULT_PORT);
  if (server_sock >= 0)
    {
      lw6sys_log (LW6SYS_LOG_NOTICE,
		  _("UDP socket %d listening on port %d"), server_sock,
		  LW6NET_DEFAULT_PORT);
      client_sock = lw6net_udp_client ();
    }
  if (server_sock >= 0 && client_sock >= 0)
    {
      (*sock1) = server_sock;
      (*sock2) = client_sock;
      ret = 1;
    }
  else
    {
      if (server_sock >= 0)
	{
	  lw6net_socket_close (server_sock);
	}
      if (client_sock >= 0)
	{
	  lw6net_socket_close (client_sock);
	}
      (*sock1) = (*sock2) = -1;
    }

  return ret;
}

/*
 * Testing functions in udp.c
 */
static int
test_udp ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    int sock1 = -1;
    int sock2 = -1;
    int ret_tmp = 0;
    char *buf1_send = NULL;
    char *buf1_recv = NULL;
    int size;
    char *incoming_ip = NULL;
    int incoming_port = 0;

    if (prepare_2_udp_socks (&sock1, &sock2))
      {
	size = strlen (TEST_BUF1_STR) + 1;
	buf1_send = lw6sys_str_copy (TEST_BUF1_STR);
	buf1_recv = LW6SYS_CALLOC (strlen (TEST_BUF1_STR) + 1);

	if (buf1_send && buf1_recv)
	  {
	    if (lw6net_udp_send
		(sock2, buf1_send, size,
		 LW6NET_ADDRESS_LOOPBACK, LW6NET_DEFAULT_PORT) == size)
	      {
		lw6sys_sleep (TEST_UDP_DELAY);
		if (lw6net_udp_peek
		    (sock1, buf1_recv, size,
		     &incoming_ip, &incoming_port) == size)
		  {
		    if (incoming_ip)
		      {
			lw6sys_log (LW6SYS_LOG_NOTICE,
				    _
				    ("%d bytes available on socket %d (%s:%d)"),
				    size, sock1, incoming_ip, incoming_port);
			LW6SYS_FREE (incoming_ip);
		      }
		    if (lw6net_udp_recv
			(sock1, buf1_recv, size,
			 &incoming_ip, &incoming_port) == size)
		      {
			if (incoming_ip)
			  {
			    lw6sys_log (LW6SYS_LOG_NOTICE,
					_
					("received \"%s\" on socket %d (%s:%d)"),
					buf1_recv, sock1, incoming_ip,
					incoming_port);
			    LW6SYS_FREE (incoming_ip);
			  }
			ret_tmp = 1;
		      }
		  }
	      }
	  }
      }
    if (buf1_send)
      {
	LW6SYS_FREE (buf1_send);
      }
    if (buf1_recv)
      {
	LW6SYS_FREE (buf1_recv);
      }
    if (sock1 >= 0)
      {
	lw6net_socket_close (sock1);
      }
    if (sock2 >= 0)
      {
	lw6net_socket_close (sock2);
      }

    if (!ret_tmp)
      {
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/*
 * Testing functions in line.c
 */
static int
test_line ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    int sock1 = -1;
    int sock2 = -1;
    int ret_tmp = 0;
    int i;
    char *line;

    if (prepare_2_tcp_socks (&sock1, &sock2))
      {
	if (lw6net_send_line_tcp (sock1, TEST_LINE1) &&
	    lw6net_send_line_tcp (sock1, TEST_LINE2) &&
	    lw6net_send_line_tcp (sock1, TEST_LINE3))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE, _("lines sent"));
	    ret_tmp = 1;
	    for (i = 0; i < 4; ++i)
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE, _("receiving line %d"), i + 1);
		line = lw6net_recv_line_tcp (sock2);
		if (line)
		  {
		    lw6sys_log (LW6SYS_LOG_NOTICE,
				_("received line \"%s\""), line);
		    LW6SYS_FREE (line);
		  }
		else
		  {
		    if (i < 3)
		      {
			ret_tmp = 0;
		      }
		  }
	      }
	  }
      }
    if (sock1 >= 0)
      {
	lw6net_socket_close (sock1);
      }
    if (sock2 >= 0)
      {
	lw6net_socket_close (sock2);
      }

    if (!ret_tmp)
      {
	ret = 0;
      }
  }

  {
    int sock1 = -1;
    int sock2 = -1;
    int ret_tmp = 0;
    int i;
    char *line;
    char *incoming_ip;
    int incoming_port;

    if (prepare_2_udp_socks (&sock1, &sock2))
      {
	if (lw6net_send_line_udp
	    (sock2, TEST_LINE1, LW6NET_ADDRESS_LOOPBACK,
	     LW6NET_DEFAULT_PORT)
	    && lw6net_send_line_udp (sock2, TEST_LINE2,
				     LW6NET_ADDRESS_LOOPBACK,
				     LW6NET_DEFAULT_PORT)
	    && lw6net_send_line_udp (sock2, TEST_LINE3,
				     LW6NET_ADDRESS_LOOPBACK,
				     LW6NET_DEFAULT_PORT))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE, _("lines sent"));
	    ret_tmp = 1;
	    for (i = 0; i < 4; ++i)
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE, _("receiving line %d"), i + 1);
		line =
		  lw6net_recv_line_udp (sock1, &incoming_ip, &incoming_port);
		if (line)
		  {
		    if (incoming_ip)
		      {
			lw6sys_log (LW6SYS_LOG_NOTICE,
				    _("received line \"%s\" from %s:%d"),
				    line, incoming_ip, incoming_port);
			LW6SYS_FREE (incoming_ip);
		      }
		    LW6SYS_FREE (line);
		  }
		else
		  {
		    if (i < 3)
		      {
			ret_tmp = 0;
		      }
		  }
	      }
	  }
      }
    if (sock1 >= 0)
      {
	lw6net_socket_close (sock1);
      }
    if (sock2 >= 0)
      {
	lw6net_socket_close (sock2);
      }

    if (!ret_tmp)
      {
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/**
 * lw6net_test
 *
 * @mode: 0 for check only, 1 for full test
 *
 * Runs the @net module test suite. This one could fail if some
 * sockets are already bound, for instance. It's still run even
 * in check-only (mode=0) mode.
 *
 * Return value: 1 if test is successfull, 0 on error.
 */
int
lw6net_test (int mode)
{
  int ret = 0;
  int argc = TEST_ARGC;
  char *argv[TEST_ARGC] = { TEST_ARGV0 };

  if (lw6sys_false ())
    {
      /*
       * Just to make sure most functions are stuffed in the binary
       */
      lw6sys_test (mode);
      lw6cfg_test (mode);
    }

  ret = lw6net_init (argc, argv) && test_if () && test_tcp () && test_udp ()
    && test_line ();

  if (ret)
    {
      lw6net_quit ();
    }

  return ret;
}
