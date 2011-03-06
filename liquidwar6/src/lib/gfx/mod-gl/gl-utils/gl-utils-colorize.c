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

#include "../../gfx.h"
#include "gl-utils.h"

SDL_Surface *
mod_gl_utils_colorize_surface (mod_gl_utils_context_t *
			       utils_context, SDL_Surface * surface,
			       lw6map_color_couple_t * color, int has_alpha)
{
  SDL_Surface *colorized_surface = NULL;
  int x, y;
  lw6sys_color_8_t color_8;
  lw6sys_color_hsv_t color_hsv;
  int a;

  colorized_surface =
    mod_gl_utils_create_surface (utils_context, surface->w, surface->h);

  for (y = 0; y < surface->h; ++y)
    {
      for (x = 0; x < surface->w; ++x)
	{
	  color_8 =
	    lw6sys_color_i_to_8 (mod_gl_utils_getpixel (surface, x, y));
	  if (has_alpha)
	    {
	      a = color_8.a;
	    }
	  else
	    {
	      a = 255;
	    }
	  lw6sys_color_rgb_to_hsv (&color_hsv, color_8);
	  color_8 = lw6sys_color_ponderate (color->bg,
					    color->fg, color_hsv.v);
	  color_8.a = a;
	  mod_gl_utils_putpixel (colorized_surface, x, y,
				 lw6sys_color_8_to_i (color_8));
	}
    }

  return colorized_surface;
}
