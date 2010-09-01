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
#include "mod-http-internal.h"

int
_mod_http_send (_http_context_t * http_context,
		lw6cnx_connection_t * connection, char *message)
{
  int ret = 0;

  lw6sys_log (LW6SYS_LOG_DEBUG, _("mod_http send \"%s\""), message);
  // todo

  return ret;
}

void
_mod_http_poll (_http_context_t * http_context,
		lw6cnx_connection_t * connection)
{
  lw6sys_log (LW6SYS_LOG_DEBUG, _("mod_http poll"));
  // todo
}
