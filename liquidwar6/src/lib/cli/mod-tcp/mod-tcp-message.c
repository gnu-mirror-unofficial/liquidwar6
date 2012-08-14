/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012  Christian Mauduit <ufoot@ufoot.org>

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

#include "../cli.h"
#include "mod-tcp-internal.h"

int
_mod_tcp_send (_mod_tcp_context_t * tcp_context,
	       lw6cnx_connection_t * connection,
	       u_int32_t physical_ticket_sig, u_int32_t logical_ticket_sig,
	       u_int64_t logical_from_id, u_int64_t logical_to_id,
	       const char *message)
{
  int ret = 0;
  _mod_tcp_specific_data_t *specific_data =
    (_mod_tcp_specific_data_t *) connection->backend_specific_data;
  char *line = NULL;

  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("mod_tcp send \"%s\""), message);
  line = lw6msg_envelope_generate (LW6MSG_ENVELOPE_MODE_TELNET,
				   lw6sys_build_get_version (),
				   connection->password_send_checksum,
				   physical_ticket_sig,
				   logical_ticket_sig,
				   connection->local_id_int,
				   connection->remote_id_int,
				   logical_from_id, logical_to_id, message);
  if (line)
    {
      if (specific_data->state == _MOD_TCP_STATE_CONNECTED
	  && lw6net_socket_is_valid (specific_data->sock))
	{
	  if (lw6cnx_connection_lock_send (connection))
	    {
	      if (lw6net_send_line_tcp (specific_data->sock, line))
		{
		  if (specific_data->send_failed_once)
		    {
		      lw6sys_log (LW6SYS_LOG_DEBUG,
				  _x_
				  ("mod_tcp send succeeded but has failed before"));
		    }
		  specific_data->send_succeeded_once = 1;
		  lw6sys_log (LW6SYS_LOG_DEBUG,
			      _x_ ("mod_tcp sent \"%s\" sock=%d"), line,
			      specific_data->sock);
		  ret = 1;
		}
	      lw6cnx_connection_unlock_send (connection);
	    }
	}
      else
	{
	  if (specific_data->send_succeeded_once)
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG,
			  _x_
			  ("mod_tcp send failed but has succeeded before"));
	    }
	  specific_data->send_failed_once = 1;
	  lw6sys_log (LW6SYS_LOG_DEBUG,
		      _x_
		      ("mod_tcp can't send \"%s\", not connected sock=%d state=%d"),
		      message, specific_data->sock, specific_data->state);
	  if (lw6cnx_connection_lock_send (connection))
	    {
	      if (!specific_data->send_backlog)
		{
		  specific_data->send_backlog =
		    lw6sys_list_new (lw6sys_free_callback);
		}
	      if (specific_data->send_backlog)
		{
		  // order is important, we prefer popping them the right order
		  lw6sys_list_push_back (&(specific_data->send_backlog),
					 line);
		  lw6sys_log (LW6SYS_LOG_DEBUG,
			      _x_ ("mod_tcp send put line in backlog"));
		  // don't want to free this as it's in the list
		  line = NULL;
		}
	      lw6cnx_connection_unlock_send (connection);
	    }
	}
    }

  if (line)
    {
      LW6SYS_FREE (line);
    }

  return ret;
}

void
_mod_tcp_poll (_mod_tcp_context_t * tcp_context,
	       lw6cnx_connection_t * connection)
{
  _mod_tcp_specific_data_t *specific_data =
    (_mod_tcp_specific_data_t *) connection->backend_specific_data;
  _mod_tcp_connect_data_t *connect_data = NULL;
  char buffer[LW6CLI_CONTENT_BUFFER_SIZE + 1];
  char *envelope_line = NULL;
  char *msg = NULL;
  char *line = NULL;
  u_int32_t physical_ticket_sig = 0;
  u_int32_t logical_ticket_sig = 0;
  u_int64_t physical_from_id = 0;
  u_int64_t physical_to_id = 0;
  u_int64_t logical_from_id = 0;
  u_int64_t logical_to_id = 0;

  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("mod_tcp poll"));
  switch (specific_data->state)
    {
    case _MOD_TCP_STATE_CLOSED:
      connect_data =
	(_mod_tcp_connect_data_t *)
	LW6SYS_CALLOC (sizeof (_mod_tcp_connect_data_t));
      if (connect_data)
	{
	  connect_data->tcp_context = tcp_context;
	  connect_data->connection = connection;
	  specific_data->state = _MOD_TCP_STATE_CONNECTING;
	  specific_data->connect_thread =
	    lw6sys_thread_create (_mod_tcp_connect_func, NULL, connect_data);
	  if (specific_data->connect_thread)
	    {
	      // OK
	    }
	  else
	    {
	      specific_data->state = _MOD_TCP_STATE_CLOSED;
	      LW6SYS_FREE (connect_data);
	    }
	}
      break;
    case _MOD_TCP_STATE_CONNECTING:
      // nothing to do, just wait until it's connected or not
      break;
    case _MOD_TCP_STATE_CONNECT_DONE:
      if (specific_data->connect_thread)
	{
	  lw6sys_thread_join (specific_data->connect_thread);
	  specific_data->connect_thread = NULL;
	}
      if (lw6net_socket_is_valid (specific_data->sock))
	{
	  specific_data->state = _MOD_TCP_STATE_CONNECTED;
	  /*
	   * We schedule a foo/bar soon so that connection does not stay
	   * "idle" and fires a server error because of a timeout.
	   */
	  lw6cnx_connection_init_foo_bar_key (connection,
					      lw6sys_get_timestamp (),
					      LW6SYS_SLEEP_DELAY);
	}
      else
	{
	  specific_data->state = _MOD_TCP_STATE_CLOSED;
	}
      break;
    case _MOD_TCP_STATE_CONNECTED:
      if (lw6net_socket_is_valid (specific_data->sock))
	{
	  if (lw6net_tcp_is_alive (specific_data->sock))
	    {
	      /*
	       * Send
	       */
	      if (lw6cnx_connection_lock_send (connection))
		{
		  if (specific_data->send_backlog)
		    {
		      while ((line =
			      lw6sys_list_pop_front (&
						     (specific_data->send_backlog)))
			     != NULL)
			{
			  if (lw6net_send_line_tcp
			      (specific_data->sock, line))
			    {
			      lw6sys_log (LW6SYS_LOG_DEBUG,
					  _x_
					  ("mod_tcp sent \"%s\" from backlog sock=%d"),
					  line, specific_data->sock);
			    }
			  LW6SYS_FREE (line);
			}
		      specific_data->send_backlog = NULL;
		    }
		  lw6cnx_connection_unlock_send (connection);
		}

	      /*
	       * Recv
	       */
	      memset (buffer, 0, LW6CLI_CONTENT_BUFFER_SIZE + 1);
	      if (lw6net_tcp_peek
		  (specific_data->sock, buffer, LW6CLI_CONTENT_BUFFER_SIZE,
		   0))
		{
		  if (strchr (buffer, '\n'))
		    {
		      envelope_line =
			lw6net_recv_line_tcp (specific_data->sock);
		      if (envelope_line)
			{
			  lw6sys_log (LW6SYS_LOG_DEBUG,
				      _x_
				      ("mod_tcp received envelope \"%s\""),
				      envelope_line);
			  if (lw6msg_envelope_analyse
			      (envelope_line, LW6MSG_ENVELOPE_MODE_TELNET,
			       connection->local_url, connection->password,
			       connection->remote_id_int,
			       connection->local_id_int, &msg,
			       &physical_ticket_sig, &logical_ticket_sig,
			       &physical_from_id, &physical_to_id,
			       &logical_from_id, &logical_to_id, NULL))
			    {
			      lw6sys_log (LW6SYS_LOG_DEBUG,
					  _x_ ("mod_tcp analysed msg \"%s\""),
					  msg);
			      if (connection->recv_callback_func)
				{
				  connection->recv_callback_func
				    (connection->recv_callback_data,
				     (void *) connection, physical_ticket_sig,
				     logical_ticket_sig, logical_from_id,
				     logical_to_id, msg);
				}
			      else
				{
				  lw6sys_log (LW6SYS_LOG_DEBUG,
					      _x_
					      ("no recv callback defined"));
				}
			      LW6SYS_FREE (msg);
			    }
			  LW6SYS_FREE (envelope_line);
			}
		    }
		}
	    }
	  else
	    {
	      lw6net_socket_close (&(specific_data->sock));
	      specific_data->state = _MOD_TCP_STATE_CLOSED;
	    }
	}
      else
	{
	  specific_data->sock = LW6NET_SOCKET_INVALID;
	  specific_data->state = _MOD_TCP_STATE_CLOSED;
	}
      break;
    default:
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("unvalid state %d"),
		  specific_data->state);
    }
}
