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

#include "../snd.h"
#include "mod-ogg-internal.h"

char *
_mod_ogg_repr (_mod_ogg_context_t * ogg_context, u_int32_t id)
{
  char *ret = NULL;
  SDL_version version;

  memset (&version, 0, sizeof (SDL_version));
  version = *SDL_Linked_Version ();
  ret =
    lw6sys_new_sprintf (_x_
			("%u ogg SDL version %u.%u.%u volume %0.1f-%0.1f-%0.1f"),
			id, version.major, version.minor, version.patch,
			ogg_context->volume.fx, ogg_context->volume.water,
			ogg_context->volume.music);

  return ret;
}
