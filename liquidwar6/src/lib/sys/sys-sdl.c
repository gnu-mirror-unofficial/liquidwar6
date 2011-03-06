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

#include "sys.h"

static int registered_use = 0;

/**
 * lw6sys_sdl_register:
 *
 * Function used to avoid initializing SDL several times in a program.
 * AFAIK Allegro has a @was_init function, but SDL doesn't. With this
 * function - which every LW6 sub-module should use - one can know
 * globally, for the whole program, wether SDL has been initialized 
 * or not.
 *
 * @Return value: 1 if SDL has never been initialized, 0 if it has 
 *   already been set up.
 */
int
lw6sys_sdl_register ()
{
  int ret = (registered_use <= 0);

  registered_use++;

  return ret;
}

/**
 * lw6sys_sdl_unregister:
 *
 * Call this whenever you are done with SDL and exit it, so that
 * the @lw6sys_sdl_register function works correctly.
 *
 * Return value: 1 if SDL needs to be unregistered, that is, if
 *   it has already been initialized, else 0.
 */
int
lw6sys_sdl_unregister ()
{
  int ret = 0;

  if (registered_use > 0)
    {
      registered_use--;
    }

  ret = (registered_use <= 0);

  return ret;
}
