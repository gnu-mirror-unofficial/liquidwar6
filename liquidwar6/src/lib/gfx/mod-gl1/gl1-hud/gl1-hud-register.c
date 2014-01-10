/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014  Christian Mauduit <ufoot@ufoot.org>

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

#include <string.h>

#include "../mod-gl1.h"

#include "gl1-floating/gl1-floating.h"
#include "gl1-tactical/gl1-tactical.h"

mod_gl1_hud_backend_t *
mod_gl1_hud_create_backend (mod_gl1_utils_context_t * utils_context,
			    char *name)
{
  mod_gl1_hud_backend_t *(*init_func) (mod_gl1_utils_context_t *
				       utils_context) = NULL;
  mod_gl1_hud_backend_t *backend = NULL;

  if (strcmp (name, "floating") == 0)
    {
      init_func = mod_gl1_hud_floating_create_backend;
    }
  else if (strcmp (name, "tactical") == 0)
    {
      init_func = mod_gl1_hud_tactical_create_backend;
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_ ("hud backend \"%s\" does not exists"), name);
    }

  if (init_func)
    {
      backend = init_func (utils_context);
      if (backend)
	{
	  backend->backend_name = lw6sys_str_copy (name);
	}
    }

  return backend;
}

void
mod_gl1_hud_destroy_backend (mod_gl1_utils_context_t * utils_context,
			     mod_gl1_hud_backend_t * backend)
{
  if (backend)
    {
      if (backend->backend_name)
	{
	  LW6SYS_FREE (backend->backend_name);
	}
      LW6SYS_FREE (backend);
    }
}
