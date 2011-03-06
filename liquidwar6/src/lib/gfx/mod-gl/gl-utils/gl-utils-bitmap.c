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

#define _TEST_PNG1 ".png"
#define _TEST_PNG2 ".PNG"

static u_int32_t seq_id = 0;

static void
_set_defaults (mod_gl_utils_context_t * utils_context,
	       mod_gl_utils_bitmap_t * bitmap)
{
  // some values not set, already at zero because of CALLOC
  bitmap->wrap = GL_REPEAT;
  bitmap->filter = GL_LINEAR;
  bitmap->s1 = 0.0f;
  bitmap->t1 = 0.0f;
  bitmap->s2 = mod_gl_utils_texture_scale (bitmap->surface->w);
  bitmap->t2 = mod_gl_utils_texture_scale (bitmap->surface->h);
  bitmap->texture_w = mod_gl_utils_power_of_two_ge (bitmap->surface->w);
  bitmap->texture_h = mod_gl_utils_power_of_two_ge (bitmap->surface->h);
  bitmap->last_refresh = mod_gl_utils_timer_get_timestamp (utils_context);
  //mod_gl_utils_bitmap_refresh (utils_context, bitmap);
}

static int
_has_alpha (char *filename)
{
  int ret = 0;

  if (strstr (filename, _TEST_PNG1) || strstr (filename, _TEST_PNG2))
    {
      ret = 1;
    }

  return ret;
}

mod_gl_utils_bitmap_t *
mod_gl_utils_bitmap_new (mod_gl_utils_context_t *
			 utils_context, int width, int height)
{
  mod_gl_utils_bitmap_t *ret = NULL;

  ret =
    (mod_gl_utils_bitmap_t *) LW6SYS_CALLOC (sizeof (mod_gl_utils_bitmap_t));
  if (ret)
    {
      ret->id = 0;
      while (!ret->id)
	{
	  ret->id = ++seq_id;
	}

      ret->surface =
	mod_gl_utils_create_surface (utils_context, width, height);
      if (ret->surface)
	{
	  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("new bitmap %d %dx%d"), ret->id,
		      width, height);
	  ret->has_alpha = 1;
	  _set_defaults (utils_context, ret);
	}
      else
	{
	  LW6SYS_FREE (ret);
	  ret = NULL;
	}
    }

  return ret;
}

mod_gl_utils_bitmap_t *
mod_gl_utils_bitmap_load (mod_gl_utils_context_t *
			  utils_context, char *filename)
{
  mod_gl_utils_bitmap_t *ret = NULL;

  ret =
    (mod_gl_utils_bitmap_t *) LW6SYS_CALLOC (sizeof (mod_gl_utils_bitmap_t));
  if (ret)
    {
      ret->id = 0;
      while (!ret->id)
	{
	  ret->id = ++seq_id;
	}

      ret->surface = mod_gl_utils_load_image (utils_context, filename);
      if (ret->surface)
	{
	  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("bitmap %u \"%s\" %dx%d loaded"),
		      ret->id, filename, ret->surface->w, ret->surface->h);
	  ret->filename = lw6sys_str_copy (filename);
	  if (ret->surface->format->BytesPerPixel == 4)
	    {
	      ret->has_alpha = _has_alpha (filename);
	    }
	  _set_defaults (utils_context, ret);
	}
      else
	{
	  LW6SYS_FREE (ret);
	  ret = NULL;
	}
    }

  return ret;
}

mod_gl_utils_bitmap_t *
mod_gl_utils_surface2bitmap (mod_gl_utils_context_t
			     * utils_context, SDL_Surface * surface)
{
  mod_gl_utils_bitmap_t *ret = NULL;

  ret =
    (mod_gl_utils_bitmap_t *) LW6SYS_CALLOC (sizeof (mod_gl_utils_bitmap_t));
  if (ret)
    {
      ret->id = 0;
      while (!ret->id)
	{
	  ret->id = ++seq_id;
	}

      ret->surface = surface;
      lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("bitmap %u from surface %dx%d"),
		  ret->id, ret->surface->w, ret->surface->h);
      ret->has_alpha = 1;
      _set_defaults (utils_context, ret);
    }

  return ret;
}

void
mod_gl_utils_bitmap_free (mod_gl_utils_context_t *
			  utils_context, mod_gl_utils_bitmap_t * bitmap)
{
  if (bitmap)
    {
      lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("free bitmap %u"), bitmap->id);
      if (bitmap->filename)
	{
	  LW6SYS_FREE (bitmap->filename);
	}
      if (bitmap->surface)
	{
	  mod_gl_utils_delete_surface (utils_context, bitmap->surface);
	}
      if (bitmap->colorized_surface)
	{
	  mod_gl_utils_delete_surface (utils_context,
				       bitmap->colorized_surface);
	}
      if (bitmap->texture)
	{
	  mod_gl_utils_schedule_delete_texture (utils_context,
						bitmap->texture);
	}
      LW6SYS_FREE (bitmap);
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("trying to free NULL bitmap"));
    }
}

int
mod_gl_utils_bitmap_colorize (mod_gl_utils_context_t *
			      utils_context, mod_gl_utils_bitmap_t * bitmap,
			      int colorize, lw6map_color_couple_t * color)
{
  int ret = 0;

  bitmap->colorize = colorize;
  if (colorize)
    {
      if ((!bitmap->colorized_surface)
	  || (!lw6map_color_is_same (color, &(bitmap->colorize_color))))
	{
	  lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("colorize bitmap %u"),
		      bitmap->id);
	  if (bitmap->colorized_surface)
	    {
	      mod_gl_utils_delete_surface (utils_context,
					   bitmap->colorized_surface);
	      bitmap->colorized_surface = NULL;
	    }
	  bitmap->colorize_color = *color;
	  bitmap->colorized_surface =
	    mod_gl_utils_colorize_surface (utils_context, bitmap->surface,
					   color, bitmap->has_alpha);
	  mod_gl_utils_bitmap_clear_texture (utils_context, bitmap);
	}
    }
  else
    {
      if (bitmap->colorized_surface)
	{
	  mod_gl_utils_delete_surface (utils_context,
				       bitmap->colorized_surface);
	  bitmap->colorized_surface = NULL;
	}
    }

  return ret;
}

int
mod_gl_utils_bitmap_set_wrap (mod_gl_utils_context_t *
			      utils_context, mod_gl_utils_bitmap_t * bitmap,
			      GLint wrap)
{
  int ret = 0;

  switch (wrap)
    {
    case GL_REPEAT:
    case GL_CLAMP:
    case GL_CLAMP_TO_EDGE:
      bitmap->wrap = wrap;
      ret = 1;
      break;
    default:
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("unknow GL wrap %d"), wrap);
    }

  return ret;
}

int
mod_gl_utils_bitmap_set_filter (mod_gl_utils_context_t *
				utils_context, mod_gl_utils_bitmap_t * bitmap,
				GLint filter)
{
  int ret = 0;

  /*
   * This is where mipmaping and/or linear filtering is enabled
   * or disabled based on gfx_quality value.
   */
  switch (utils_context->render_param.gfx_quality)
    {
    case LW6GUI_GFX_QUALITY_LOW:
      filter = GL_NEAREST;
      break;
    case LW6GUI_GFX_QUALITY_STANDARD:
      switch (filter)
	{
	case GL_LINEAR_MIPMAP_NEAREST:
	case GL_LINEAR_MIPMAP_LINEAR:
	  filter = GL_LINEAR;
	  break;
	}
      break;
    case LW6GUI_GFX_QUALITY_HIGH:
      // keep given filter
      break;
    default:
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("unknown gfx_quality %d"),
		  utils_context->render_param.gfx_quality);
      break;
    }

  switch (filter)
    {
    case GL_NEAREST:
    case GL_LINEAR:
      bitmap->mipmap = 0;
      if (filter != bitmap->filter)
	{
	  /*
	   * OK, this might sound overkill to delete the texture
	   * just because we change the filtering. In practice
	   * this is rare, a given texture is always rendered
	   * with the same options. In fact, should there be a
	   * bitmap that would be displayed in the same frame with
	   * 2 different filters, we would create 2 bitmaps.
	   * Here the idea is that when one switches from GL_LINEAR
	   * to say GL_LINEAR_MIMAP_LINEAR one has to activate 
	   * mimapping, and that is done at texture creation.
	   */
	  mod_gl_utils_bitmap_clear_texture (utils_context, bitmap);
	  bitmap->filter = filter;
	}
      ret = 1;
      break;
    case GL_LINEAR_MIPMAP_NEAREST:
    case GL_LINEAR_MIPMAP_LINEAR:
      bitmap->mipmap = 1;
      if (filter != bitmap->filter)
	{
	  mod_gl_utils_bitmap_clear_texture (utils_context, bitmap);
	  bitmap->filter = filter;
	}
      ret = 1;
      break;
    default:
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("unknow GL filter %d"), filter);
    }

  return ret;
}

int
mod_gl_utils_bitmap_set_texture_coords (mod_gl_utils_context_t *
					utils_context,
					mod_gl_utils_bitmap_t * bitmap,
					float s1, float t1, float s2,
					float t2)
{
  int ret = 0;

  if (s1 != t2)
    {
      bitmap->s1 = s1;
      bitmap->s2 = s2;
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("same texture coords s1=%f s2=%f"),
		  s1, s2);
    }

  if (t1 != t2)
    {
      bitmap->t1 = t1;
      bitmap->t2 = t2;
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("same texture coords t1=%f t2=%f"),
		  t1, t2);
    }

  return ret;
}

void
mod_gl_utils_bitmap_clear_texture (mod_gl_utils_context_t *
				   utils_context,
				   mod_gl_utils_bitmap_t * bitmap)
{
  if (bitmap->texture)
    {
      mod_gl_utils_schedule_delete_texture (utils_context, bitmap->texture);
      bitmap->texture = 0;
    }
}

void
mod_gl_utils_bitmap_clear_texture_now (mod_gl_utils_context_t *
				       utils_context,
				       mod_gl_utils_bitmap_t * bitmap)
{
  if (bitmap->texture)
    {
      mod_gl_utils_delete_texture (utils_context, bitmap->texture);
      bitmap->texture = 0;
    }
}

int
mod_gl_utils_bitmap_refresh (mod_gl_utils_context_t *
			     utils_context, mod_gl_utils_bitmap_t * bitmap)
{
  int ret = 0;

  if (bitmap->last_refresh <
      mod_gl_utils_timer_get_bitmap_refresh (utils_context))
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _x_ ("bitmap %u is too old bitmap->last_refresh=%"
		       LW6SYS_PRINTF_LL
		       "d timer_get_bitmap_refresh returned %"
		       LW6SYS_PRINTF_LL "d, refreshing"), bitmap->id,
		  bitmap->last_refresh,
		  mod_gl_utils_timer_get_bitmap_refresh (utils_context));
      mod_gl_utils_bitmap_clear_texture_now (utils_context, bitmap);
      bitmap->last_refresh = mod_gl_utils_timer_get_timestamp (utils_context);
    }
  if (!bitmap->texture)
    {
      lw6sys_log (LW6SYS_LOG_DEBUG, _x_ ("refresh bitmap %u"), bitmap->id);

      /*
       * Calling set_filter with self value will cause gfx_quality
       * rules to be applied if needed.
       */
      mod_gl_utils_bitmap_set_filter (utils_context, bitmap, bitmap->filter);

      if (bitmap->colorize && bitmap->colorized_surface)
	{
	  bitmap->texture =
	    mod_gl_utils_surface2texture (utils_context,
					  bitmap->colorized_surface,
					  bitmap->mipmap);
	}
      else
	{
	  if (bitmap->surface)
	    {
	      bitmap->texture =
		mod_gl_utils_surface2texture (utils_context, bitmap->surface,
					      bitmap->mipmap);
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_WARNING,
			  _x_ ("no surface for bitmap \"%u\""), bitmap->id);
	    }
	}
      if (bitmap->texture)
	{
	  ret = 1;
	}
    }
  else
    {
      ret = 1;
    }

  return ret;
}

int
mod_gl_utils_bitmap_refresh_force (mod_gl_utils_context_t *
				   utils_context,
				   mod_gl_utils_bitmap_t * bitmap)
{
  int ret = 0;

  mod_gl_utils_bitmap_clear_texture (utils_context, bitmap);
  ret = mod_gl_utils_bitmap_refresh (utils_context, bitmap);

  return ret;
}

int
mod_gl_utils_bitmap_bind (mod_gl_utils_context_t *
			  utils_context, mod_gl_utils_bitmap_t * bitmap)
{
  int ret = 0;

  if (bitmap)
    {
      mod_gl_utils_bitmap_refresh (utils_context, bitmap);
      glBindTexture (GL_TEXTURE_2D, bitmap->texture);
      if (!glIsTexture (bitmap->texture))
	{
	  mod_gl_utils_bitmap_refresh_force (utils_context, bitmap);
	  glBindTexture (GL_TEXTURE_2D, bitmap->texture);
	}
      if (glIsTexture (bitmap->texture))
	{
	  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, bitmap->wrap);
	  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, bitmap->wrap);
	  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			   bitmap->filter);
	  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			   bitmap->filter);
	  ret = 1;
	}
      else
	{
	  lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("unable to bind texture %d"),
		      bitmap->texture);
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("trying to bind NULL bitmap"));
    }

  return ret;
}

int
mod_gl_utils_bitmap_display (mod_gl_utils_context_t *
			     utils_context, mod_gl_utils_bitmap_t * bitmap,
			     float x1, float y1, float x2, float y2)
{
  int ret = 0;

  ret = mod_gl_utils_bitmap_bind (utils_context, bitmap);

  glMatrixMode (GL_TEXTURE);
  glPushMatrix ();
  glLoadIdentity ();
  glBegin (GL_QUADS);
  glTexCoord2d (bitmap->s1, bitmap->t1);
  glVertex3f (x1, y1, 0.0f);	// top left
  glTexCoord2d (bitmap->s2, bitmap->t1);
  glVertex3f (x2, y1, 0.0f);	// top right
  glTexCoord2d (bitmap->s2, bitmap->t2);
  glVertex3f (x2, y2, 0.0f);	// bottom right
  glTexCoord2d (bitmap->s1, bitmap->t2);
  glVertex3f (x1, y2, 0.0f);	// bottom left
  glEnd ();
  glMatrixMode (GL_TEXTURE);
  glPopMatrix ();

  return ret;
}

int
mod_gl_utils_bitmap_update_texture (mod_gl_utils_context_t *
				    utils_context,
				    mod_gl_utils_bitmap_t * bitmap)
{
  int ret = 0;

  // todo...

  return ret;
}
