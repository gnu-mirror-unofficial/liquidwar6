/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011  Christian Mauduit <ufoot@ufoot.org>

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

#include "../srv.h"
#include "mod-httpd-internal.h"

int
_mod_httpd_analyse_tcp (_mod_httpd_context_t * httpd_context,
			lw6srv_tcp_accepter_t * tcp_accepter,
			lw6nod_info_t * node_info,
			u_int64_t * remote_id, char **remote_url)
{
  int ret = 0;
  char *pos = NULL;
  char *line = NULL;
  char *msg = NULL;

  line = tcp_accepter->first_line;
  lw6sys_log (LW6SYS_LOG_DEBUG,
	      _x_ ("trying to recognize httpd protocol in \"%s\""), line);

  if (remote_id)
    {
      (*remote_id) = 0;
    }
  if (remote_url)
    {
      (*remote_url) = NULL;
    }

  if (!lw6net_tcp_is_alive (tcp_accepter->sock))
    {
      ret |= LW6SRV_ANALYSE_DEAD;
      lw6net_socket_close (tcp_accepter->sock);
      tcp_accepter->sock = -1;
    }

  if (strlen (line) >=
      _MOD_HTTPD_PROTOCOL_UNDERSTANDABLE_SIZE || strchr (line, '\n'))
    {
      if (lw6sys_str_starts_with
	  (line, _MOD_HTTPD_PROTOCOL_GET_STRING)
	  || lw6sys_str_starts_with (line,
				     _MOD_HTTPD_PROTOCOL_POST_STRING)
	  || lw6sys_str_starts_with (line, _MOD_HTTPD_PROTOCOL_HEAD_STRING))
	{
	  lw6sys_log (LW6SYS_LOG_DEBUG,
		      _x_ ("recognized httpd protocol \"%s\""), line);
	  pos = line;
	  while ((*pos) && !lw6sys_chr_is_space (*pos))
	    {
	      pos++;
	    }
	  while (lw6sys_chr_is_space (*pos))
	    {
	      pos++;
	    }
	  if (lw6sys_str_starts_with (pos, _MOD_HTTPD_PROTOCOL_LW6_STRING))
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("httpd LW6 message \"%s\""),
			  pos);
	      if (lw6msg_envelope_analyse
		  (pos, LW6MSG_ENVELOPE_MODE_URL, node_info->const_info.url,
		   node_info->const_info.password, 0,
		   node_info->const_info.id_int, &msg, NULL, NULL, remote_id,
		   NULL, NULL, NULL, remote_url))
		{
		  ret |= LW6SRV_ANALYSE_UNDERSTANDABLE;
		  lw6sys_log (LW6SYS_LOG_DEBUG,
			      _x_ ("httpd message \"%s\" OK"), line);
		  if (msg)
		    {
		      /*
		       * We need to pass msg else remote_url isn't processed
		       */
		      LW6SYS_FREE (msg);
		    }
		}
	      else
		{
		  if (strchr (line, '\n'))
		    {
		      lw6sys_log (LW6SYS_LOG_DEBUG,
				  _x_ ("unable to analyse message \"%s\""),
				  line);
		      ret |= LW6SRV_ANALYSE_DEAD;
		    }
		  else
		    {
		      lw6sys_log (LW6SYS_LOG_DEBUG,
				  _x_
				  ("unable to analyse message \"%s\" but line does not seem complete, assuming some data is still missing, giving it another chance"),
				  line);
		    }
		}
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("out of band httpd \"%s\""),
			  pos);
	      ret |= LW6SRV_ANALYSE_UNDERSTANDABLE | LW6SRV_ANALYSE_OOB;
	    }
	}
    }

  /*
   * Here, maybe we didn't recognize HTTPD protocol, but since we're
   * in timeout, we decide so send an error 500 answer anyway.
   */
  if (lw6net_tcp_is_alive (tcp_accepter->sock)
      && !_mod_httpd_timeout_ok (httpd_context,
				 tcp_accepter->creation_timestamp))
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _x_
		  ("timeout on receive (first_line=\"%s\") so sending request to http handler, which will probably return error 500"),
		  line);
      ret |= (LW6SRV_ANALYSE_UNDERSTANDABLE | LW6SRV_ANALYSE_OOB);
    }

  return ret;
}

int
_mod_httpd_analyse_udp (_mod_httpd_context_t * httpd_context,
			lw6srv_udp_buffer_t * udp_buffer,
			lw6nod_info_t * node_info,
			u_int64_t * remote_id, char **remote_url)
{
  int ret = 0;

  if (remote_id)
    {
      (*remote_id) = 0;
    }
  if (remote_url)
    {
      (*remote_url) = NULL;
    }

  /*
   * UDP is never handled by mod_httpd, return always false
   */

  return ret;
}

int
_mod_httpd_feed_with_tcp (_mod_httpd_context_t * httpd_context,
			  lw6cnx_connection_t * connection,
			  lw6srv_tcp_accepter_t * tcp_accepter)
{
  int ret = 0;
  _mod_httpd_specific_data_t *specific_data =
    (_mod_httpd_specific_data_t *) connection->backend_specific_data;
  _mod_httpd_reply_thread_data_t *reply_thread_data = NULL;
  void *thread_handler = NULL;

  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("mod_httpd feed with tcp \"%s\""),
	      tcp_accepter->first_line);

  if (lw6net_socket_is_valid (tcp_accepter->sock))
    {
      reply_thread_data =
	(_mod_httpd_reply_thread_data_t *)
	LW6SYS_MALLOC (sizeof (_mod_httpd_reply_thread_data_t));
      if (reply_thread_data)
	{
	  reply_thread_data->httpd_context = httpd_context;
	  reply_thread_data->cnx = connection;
	  reply_thread_data->sock = tcp_accepter->sock;
	  reply_thread_data->creation_timestamp = lw6sys_get_timestamp ();
	  reply_thread_data->do_not_finish = 0;
	  thread_handler =
	    lw6sys_thread_create (_mod_httpd_reply_thread_func,
				  _mod_httpd_reply_thread_join,
				  (void *) reply_thread_data);
	  if (thread_handler)
	    {
	      lw6sys_list_push_back (&(specific_data->reply_threads),
				     thread_handler);
	      ret = 1;
	    }
	}
    }

  if (!ret)
    {
      if (lw6net_socket_is_valid (tcp_accepter->sock))
	{
	  lw6net_socket_close (tcp_accepter->sock);
	  tcp_accepter->sock = LW6NET_SOCKET_INVALID;
	}
      if (reply_thread_data)
	{
	  LW6SYS_FREE (reply_thread_data);
	}
    }

  return ret;
}

int
_mod_httpd_feed_with_udp (_mod_httpd_context_t * httpd_context,
			  lw6cnx_connection_t * connection,
			  lw6srv_udp_buffer_t * udp_buffer)
{
  int ret = 0;

  // todo

  return ret;
}
