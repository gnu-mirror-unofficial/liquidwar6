/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013  Christian Mauduit <ufoot@ufoot.org>

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
#endif // HAVE_CONFIG_H

#include "shared-sdl-internal.h"

#define SUB "gfx/sdl"
#define DEBUG "sdl-debug"

int
shared_sdl_path_init (_lw6gfx_sdl_path_t * path, int argc, const char *argv[])
{
  char *data_root_dir = NULL;
  char *user_dir = NULL;
  int ret = 0;

  data_root_dir = lw6sys_get_data_dir (argc, argv);
  if (data_root_dir)
    {
      path->data_dir = lw6sys_path_concat (data_root_dir, SUB);
      LW6SYS_FREE (data_root_dir);
    }

  user_dir = lw6sys_get_user_dir (argc, argv);
  if (user_dir)
    {
      path->debug_dir = lw6sys_path_concat (user_dir, DEBUG);
      LW6SYS_FREE (user_dir);
    }

  ret = (path->data_dir && path->debug_dir);

  if (!ret)
    {
      shared_sdl_path_quit (path);
    }

  return ret;
}

void
shared_sdl_path_quit (_lw6gfx_sdl_path_t * path)
{
  if (path->debug_dir)
    {
      LW6SYS_FREE (path->debug_dir);
    }
  if (path->data_dir)
    {
      LW6SYS_FREE (path->data_dir);
    }
}
