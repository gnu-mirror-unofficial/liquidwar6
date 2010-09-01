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

#include "../cli.h"
#include "mod-udp-internal.h"

int
_mod_udp_send (_udp_context_t * udp_context, lw6cnx_connection_t * connection,
	       char *message)
{
  int ret = 0;
  _udp_specific_data_t *specific_data =
    (_udp_specific_data_t *) connection->backend_specific_data;
  char *line;

  lw6sys_log (LW6SYS_LOG_DEBUG, _("mod_udp send \"%s\""), message);
  line = lw6sys_new_sprintf ("%s %s %s %s %s %s",
			     LW6MSG_LW6,
			     lw6sys_build_get_version (),
			     connection->local_id,
			     connection->remote_id,
			     connection->password_send_checksum, message);
  if (line)
    {
      if (lw6net_send_line_udp
	  (specific_data->sock, line, connection->remote_ip,
	   connection->remote_port))
	{
	  lw6sys_log (LW6SYS_LOG_NOTICE, _("mod_udp sent \"%s\""), line);
	  ret = 1;
	}
      LW6SYS_FREE (line);
    }

  return ret;
}

void
_mod_udp_poll (_udp_context_t * udp_context, lw6cnx_connection_t * connection)
{
  lw6sys_log (LW6SYS_LOG_DEBUG, _("mod_udp poll"));
  // todo
}
