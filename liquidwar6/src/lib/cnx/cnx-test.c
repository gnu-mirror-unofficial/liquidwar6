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

#include "cnx.h"

#define _TEST_LOCAL_URL "http://ufoot.org:8056/"
#define _TEST_REMOTE_URL "http://ufoot.hd.free.fr:8056/"
#define _TEST_REMOTE_IP "127.0.0.1"
#define _TEST_REMOTE_PORT 8888
#define _TEST_PASSWORD "toto"
#define _TEST_LOCAL_ID 0x1234123412341234LL
#define _TEST_REMOTE_ID 0x2345234523452345LL
#define _TEST_NEXT_FOO_DELAY 5000
#define _TEST_PASSWORD_SEED "http://"
#define _TEST_PASSWORD1 "abc"
#define _TEST_PASSWORD2 "XY"
#define _TEST_TICKET_TABLE_HASH_SIZE 11
#define _TEST_TICKET_TABLE_ID1 "1234123412341234"
#define _TEST_TICKET_TABLE_ID2 "2345234523452345"

static void
_recv_callback_func (void *func_data, char *msg)
{
  lw6sys_log (LW6SYS_LOG_NOTICE, _("received \"%s\""), msg);
}

/*
 * Testing functions in connection.c
 */
static int
test_connection ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    lw6cnx_connection_t *cnx = NULL;
    int64_t now = 0;

    now = lw6sys_get_timestamp ();
    cnx =
      lw6cnx_connection_new (_TEST_LOCAL_URL, _TEST_REMOTE_URL,
			     _TEST_REMOTE_IP, _TEST_REMOTE_PORT,
			     _TEST_PASSWORD, _TEST_LOCAL_ID, _TEST_REMOTE_ID,
			     _recv_callback_func, NULL);
    if (cnx)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("cnx_connection object creation works"));
	if (lw6cnx_connection_should_send_foo (cnx, now))
	  {
	    lw6cnx_connection_init_foo_bar_key (cnx, now,
						_TEST_NEXT_FOO_DELAY);
	    if (!lw6cnx_connection_should_send_foo (cnx, now))
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE,
			    _("cnx_connection foo scheduling works"));
	      }
	    else
	      {
		lw6sys_log (LW6SYS_LOG_WARNING,
			    _
			    ("cnx_connection object returns true when queried if foo message should be sent, when key has just been initialized"));
		ret = 0;
	      }
	  }
	else
	  {
	    lw6sys_log (LW6SYS_LOG_WARNING,
			_
			("new cnx_connection object returns false when queried if foo message should be sent"));
	    ret = 0;
	  }
	lw6cnx_connection_free (cnx);
      }
    else
      {
	lw6sys_log (LW6SYS_LOG_WARNING,
		    _("cnx_connection object creation failed"));
	ret = 0;
      }

    /*
     * Trying with some NULL fields
     */
    cnx =
      lw6cnx_connection_new (_TEST_LOCAL_URL, _TEST_REMOTE_URL,
			     _TEST_REMOTE_IP, _TEST_REMOTE_PORT,
			     NULL, _TEST_LOCAL_ID, _TEST_REMOTE_ID,
			     NULL, NULL);
    if (cnx)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _
		    ("cnx_connection object creation works, even with \"some\" NULLs"));
	lw6cnx_connection_free (cnx);
      }
    else
      {
	lw6sys_log (LW6SYS_LOG_WARNING,
		    _("cnx_connection object creation failed"));
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/*
 * Testing functions in password.c
 */
static int
test_password ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    char *checksum = NULL;

    checksum = lw6cnx_password_checksum (NULL, NULL);
    if (checksum)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("checksum for password NULL is \"%s\""), checksum);
	LW6SYS_FREE (checksum);
      }
    else
      {
	ret = 0;
      }
    checksum = lw6cnx_password_checksum (NULL, "");
    if (checksum)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("checksum for empty password is \"%s\""), checksum);
	LW6SYS_FREE (checksum);
      }
    else
      {
	ret = 0;
      }
    checksum = lw6cnx_password_checksum (_TEST_PASSWORD_SEED, "");
    if (checksum)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _
		    ("checksum for empty password with seed \"%s\" is \"%s\""),
		    _TEST_PASSWORD_SEED, checksum);
	LW6SYS_FREE (checksum);
      }
    else
      {
	ret = 0;
      }
    checksum = lw6cnx_password_checksum (_TEST_PASSWORD_SEED, _TEST_PASSWORD1);
    if (checksum)
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _("checksum for password \"%s\" is \"%s\""),
		    _TEST_PASSWORD1, checksum);
	if (lw6cnx_password_verify
	    (_TEST_PASSWORD_SEED, _TEST_PASSWORD1, _TEST_PASSWORD1))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE, _("same password test works"));
	  }
	else
	  {
	    ret = 0;
	  }
	if (lw6cnx_password_verify
	    (_TEST_PASSWORD_SEED, _TEST_PASSWORD1, checksum))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_("same password test works using checksum"));
	  }
	else
	  {
	    ret = 0;
	  }
	if (lw6cnx_password_verify (_TEST_PASSWORD_SEED, NULL, _TEST_PASSWORD2))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_("same password test works when it's NULL here"));
	  }
	else
	  {
	    ret = 0;
	  }
	if (!lw6cnx_password_verify
	    (_TEST_PASSWORD_SEED, _TEST_PASSWORD1, _TEST_PASSWORD2))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_("same password test detects wrong passwords"));
	  }
	else
	  {
	    ret = 0;
	  }
	if (!lw6cnx_password_verify (NULL, _TEST_PASSWORD1, _TEST_PASSWORD2))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_("same password test detects wrong seed"));
	  }
	else
	  {
	    ret = 0;
	  }
	LW6SYS_FREE (checksum);
      }
    else
      {
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/*
 * Testing functions in ticketable.c
 */
static int
test_ticket_table ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    lw6cnx_ticket_table_t ticket_table;
    u_int32_t ticket = 0;

    lw6cnx_ticket_table_zero (&ticket_table);
    if (lw6cnx_ticket_table_init
	(&ticket_table, _TEST_TICKET_TABLE_HASH_SIZE))
      {
	ticket =
	  lw6cnx_ticket_table_get_recv (&ticket_table,
					_TEST_TICKET_TABLE_ID1);
	lw6sys_log (LW6SYS_LOG_NOTICE, _("ticket generated %08x"), ticket);
	ticket =
	  lw6cnx_ticket_table_get_recv (&ticket_table,
					_TEST_TICKET_TABLE_ID2);
	lw6sys_log (LW6SYS_LOG_NOTICE, _("ticket generated %08x"), ticket);
	if (!lw6cnx_ticket_table_was_recv_exchanged
	    (&ticket_table, _TEST_TICKET_TABLE_ID1))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_
			("recv ticket reported as *not* exchanged, this is right"));
	    lw6cnx_ticket_table_ack_recv (&ticket_table,
					  _TEST_TICKET_TABLE_ID1);
	    if (lw6cnx_ticket_table_was_recv_exchanged
		(&ticket_table, _TEST_TICKET_TABLE_ID1))
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE,
			    _
			    ("recv ticket now reported as exchanged, this is right"));
	      }
	    else
	      {
		lw6sys_log (LW6SYS_LOG_WARNING,
			    _
			    ("recv ticket now reported as *not* exchanged, this is wrong"));
		ret = 0;
	      }
	  }
	else
	  {
	    lw6sys_log (LW6SYS_LOG_WARNING,
			_
			("recv ticket reported as exchanged, this is wrong"));
	    ret = 0;
	  }

	if (!lw6cnx_ticket_table_get_send
	    (&ticket_table, _TEST_TICKET_TABLE_ID1))
	  {
	    lw6sys_log (LW6SYS_LOG_NOTICE,
			_("send ticket does not exist yet, this is right"));
	    lw6cnx_ticket_table_set_send (&ticket_table,
					  _TEST_TICKET_TABLE_ID1,
					  lw6sys_generate_id_32 ());
	    if (lw6cnx_ticket_table_get_send
		(&ticket_table, _TEST_TICKET_TABLE_ID1))
	      {
		lw6sys_log (LW6SYS_LOG_NOTICE,
			    _("send ticket now exists, this is right"));
	      }
	    else
	      {
		lw6sys_log (LW6SYS_LOG_WARNING,
			    _
			    ("send ticket still does not exist, this is wrong"));
		ret = 0;
	      }
	  }
	else
	  {
	    lw6sys_log (LW6SYS_LOG_WARNING,
			_("send ticket does exist, this is wrong"));
	    ret = 0;
	  }
	lw6cnx_ticket_table_clear (&ticket_table);
      }
  }
  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/**
 * lw6cnx_test
 *
 * @mode: 0 for check only, 1 for full test
 *
 * Runs the @cnx module test suite.
 *
 * Return value: 1 if test is successfull, 0 on error.
 */
int
lw6cnx_test (int mode)
{
  int ret = 0;

  if (lw6sys_false ())
    {
      /*
       * Just to make sure most functions are stuffed in the binary
       */
      lw6sys_test (mode);
      lw6glb_test (mode);
    }

  ret = test_connection () && test_password() && test_ticket_table ();

  return ret;
}