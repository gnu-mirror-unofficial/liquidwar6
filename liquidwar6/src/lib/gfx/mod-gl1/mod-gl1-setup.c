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

#include <time.h>

#include "../gfx.h"
#include "mod-gl1-internal.h"

int
_mod_gl1_set_backends (_mod_gl1_context_t * gl_context, lw6gui_look_t * look)
{
  int ret = 1;

  ret =
    _mod_gl1_set_background_backend (gl_context, look->style.background_style)
    && ret;
  ret = _mod_gl1_set_hud_backend (gl_context, look->style.hud_style) && ret;
  ret = _mod_gl1_set_menu_backend (gl_context, look->style.menu_style) && ret;
  ret = _mod_gl1_set_view_backend (gl_context, look->style.view_style) && ret;

  return ret;
}

void
_mod_gl1_clear_background_backend (_mod_gl1_context_t * gl_context)
{
  if (gl_context->background_backend)
    {
      mod_gl1_background_quit (&(gl_context->utils_context),
			       gl_context->background_backend);
      mod_gl1_background_destroy_backend (&(gl_context->utils_context),
					  gl_context->background_backend);
      gl_context->background_backend = NULL;
    }

  //mod_gl1_utils_clear_menucache (&(gl_context->utils_context));
}

void
_mod_gl1_clear_hud_backend (_mod_gl1_context_t * gl_context)
{
  if (gl_context->hud_backend)
    {
      mod_gl1_hud_quit (&(gl_context->utils_context),
			gl_context->hud_backend);
      mod_gl1_hud_destroy_backend (&(gl_context->utils_context),
				   gl_context->hud_backend);
      gl_context->hud_backend = NULL;
    }

  //mod_gl1_utils_clear_menucache (&(gl_context->utils_context));
}

void
_mod_gl1_clear_menu_backend (_mod_gl1_context_t * gl_context)
{
  if (gl_context->menu_backend)
    {
      mod_gl1_menu_quit (&(gl_context->utils_context),
			 gl_context->menu_backend);
      mod_gl1_menu_destroy_backend (&(gl_context->utils_context),
				    gl_context->menu_backend);
      gl_context->menu_backend = NULL;
    }

  mod_gl1_utils_clear_menucache (&(gl_context->utils_context));
}

void
_mod_gl1_clear_view_backend (_mod_gl1_context_t * gl_context)
{
  if (gl_context->view_backend)
    {
      mod_gl1_view_quit (&(gl_context->utils_context),
			 gl_context->view_backend);
      mod_gl1_view_destroy_backend (&(gl_context->utils_context),
				    gl_context->view_backend);
      gl_context->view_backend = NULL;
    }

  //mod_gl1_utils_clear_menucache (&(gl_context->utils_context));
}

int
_mod_gl1_set_background_backend (_mod_gl1_context_t * gl_context,
				 char *background_style)
{
  int ret = 0;

  if ((!background_style) || strlen (background_style) == 0)
    {
      background_style = LW6MAP_STYLE_DEFAULT_BACKGROUND_STYLE;
    }

  if ((!gl_context->background_backend)
      || strcmp (gl_context->background_backend->backend_name,
		 background_style))
    {
      _mod_gl1_clear_background_backend (gl_context);

      gl_context->background_backend =
	mod_gl1_background_create_backend (&(gl_context->utils_context),
					   background_style);
      if (gl_context->background_backend)
	{
	  ret =
	    mod_gl1_background_init (&(gl_context->utils_context),
				     gl_context->background_backend);
	}
    }

  return ret;
}

int
_mod_gl1_set_hud_backend (_mod_gl1_context_t * gl_context, char *hud_style)
{
  int ret = 0;

  if ((!hud_style) || strlen (hud_style) == 0)
    {
      hud_style = LW6MAP_STYLE_DEFAULT_HUD_STYLE;
    }

  if ((!gl_context->hud_backend)
      || strcmp (gl_context->hud_backend->backend_name, hud_style))
    {
      _mod_gl1_clear_hud_backend (gl_context);

      gl_context->hud_backend =
	mod_gl1_hud_create_backend (&(gl_context->utils_context), hud_style);
      if (gl_context->hud_backend)
	{
	  ret =
	    mod_gl1_hud_init (&(gl_context->utils_context),
			      gl_context->hud_backend);
	}
    }

  return ret;
}

int
_mod_gl1_set_menu_backend (_mod_gl1_context_t * gl_context, char *menu_style)
{
  int ret = 0;

  if ((!menu_style) || strlen (menu_style) == 0)
    {
      menu_style = LW6MAP_STYLE_DEFAULT_MENU_STYLE;
    }

  if ((!gl_context->menu_backend)
      || strcmp (gl_context->menu_backend->backend_name, menu_style))
    {
      _mod_gl1_clear_menu_backend (gl_context);

      gl_context->menu_backend =
	mod_gl1_menu_create_backend (&(gl_context->utils_context),
				     menu_style);
      if (gl_context->menu_backend)
	{
	  ret =
	    mod_gl1_menu_init (&(gl_context->utils_context),
			       gl_context->menu_backend);
	}
    }

  return ret;
}

int
_mod_gl1_set_view_backend (_mod_gl1_context_t * gl_context, char *view_style)
{
  int ret = 0;

  if ((!view_style) || strlen (view_style) == 0)
    {
      view_style = LW6MAP_STYLE_DEFAULT_VIEW_STYLE;
    }

  if ((!gl_context->view_backend)
      || strcmp (gl_context->view_backend->backend_name, view_style))
    {
      _mod_gl1_clear_view_backend (gl_context);

      gl_context->view_backend =
	mod_gl1_view_create_backend (&(gl_context->utils_context),
				     view_style);
      if (gl_context->view_backend)
	{
	  ret =
	    mod_gl1_view_init (&(gl_context->utils_context),
			       gl_context->view_backend);
	}
    }

  return ret;
}

/*
 * Low-level SDL initialisation.
 */
_mod_gl1_context_t *
_mod_gl1_init (int argc, const char *argv[], lw6gui_video_mode_t * video_mode,
	       lw6gui_resize_callback_func_t resize_callback)
{
  _mod_gl1_context_t *gl_context = NULL;
  int splash_ok = 0;
  int background_ok = 0;
  int hud_ok = 0;
  int menu_ok = 0;
  int view_ok = 0;
  int sdl_ok = 1;
  int ttf_ok = 1;
  lw6map_style_t map_style;
  SDL_version version;

  gl_context =
    (_mod_gl1_context_t *) LW6SYS_CALLOC (sizeof (_mod_gl1_context_t));
  if (gl_context)
    {
      if (mod_gl1_utils_path_init (&(gl_context->utils_context), argc, argv))
	{
	  memset (&version, 0, sizeof (SDL_version));
	  SDL_VERSION (&version);
	  lw6sys_log (LW6SYS_LOG_INFO,
		      _x_ ("SDL header version when compiled %u.%u.%u"),
		      version.major, version.minor, version.patch);
	  version = *SDL_Linked_Version ();
	  lw6sys_log (LW6SYS_LOG_INFO,
		      _x_ ("SDL linked version now at runtime %u.%u.%u"),
		      version.major, version.minor, version.patch);

	  if (lw6sys_sdl_register ())
	    {
	      sdl_ok = !SDL_Init (SDL_INIT_EVENTTHREAD);
	    }

	  if (!SDL_WasInit (SDL_INIT_EVENTTHREAD))
	    {
	      lw6sys_log (LW6SYS_LOG_INFO,
			  _x_
			  ("unable to start SDL event thread, events treated in main thread with poll() functions"));
	    }

	  /*
	     sdl_ok = sdl_ok && (SDL_WasInit (SDL_INIT_TIMER)
	     || !SDL_InitSubSystem (SDL_INIT_TIMER));
	   */
	  sdl_ok = sdl_ok && (SDL_WasInit (SDL_INIT_VIDEO)
			      || !SDL_InitSubSystem (SDL_INIT_VIDEO));

	  if (sdl_ok)
	    {
	      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("SDL Init"));
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_ERROR, _("SDL init error: \"%s\""),
			  SDL_GetError ());
	      _mod_gl1_quit (gl_context);
	      gl_context = NULL;
	    }

	  if (gl_context)
	    {
	      /*
	       * Icon must be set before video mode is set
	       */
	      gl_context->utils_context.bitmap_hash =
		mod_gl1_utils_bitmap_hash_init ();
	      mod_gl1_utils_icon_set (&(gl_context->utils_context));
	      SDL_EnableUNICODE (1);
	    }

	  if (gl_context)
	    {
	      ttf_ok = (TTF_Init () != -1);
	      if (ttf_ok)
		{
		  lw6sys_log (LW6SYS_LOG_INFO, _x_ ("SDL_ttf Init"));
		}
	      else
		{
		  lw6sys_log (LW6SYS_LOG_ERROR,
			      _("SDL_ttf init error: \"%s\""),
			      TTF_GetError ());
		  _mod_gl1_quit (gl_context);
		  gl_context = NULL;
		}
	    }

	  if (gl_context && sdl_ok && ttf_ok)
	    {
	      lw6gui_input_init (&(gl_context->utils_context.input));
	      mod_gl1_utils_show_mouse (&(gl_context->utils_context), 0, 1);
	      mod_gl1_utils_set_resize_callback (&(gl_context->utils_context),
						 resize_callback);
	      if (mod_gl1_utils_load_consts (&(gl_context->utils_context)))
		{
		  if (mod_gl1_utils_set_video_mode
		      (&(gl_context->utils_context), video_mode))
		    {
		      if (mod_gl1_utils_load_data
			  (&(gl_context->utils_context)))
			{
			  memset (&map_style, 0, sizeof (lw6map_style_t));
			  lw6map_style_defaults (&map_style);
			  gl_context->splash_context =
			    mod_gl1_splash_init (&
						 (gl_context->utils_context));
			  splash_ok = (gl_context->splash_context != NULL);
			  background_ok =
			    _mod_gl1_set_background_backend (gl_context,
							     map_style.
							     background_style);
			  hud_ok =
			    _mod_gl1_set_hud_backend (gl_context,
						      map_style.hud_style);
			  menu_ok =
			    _mod_gl1_set_menu_backend (gl_context,
						       map_style.menu_style);
			  view_ok =
			    _mod_gl1_set_view_backend (gl_context,
						       map_style.view_style);
			  mod_gl1_utils_update_team_color_map (&
							       (gl_context->
								utils_context.
								team_color_map),
							       &map_style);
			  mod_gl1_utils_smoothers_init (&
							(gl_context->
							 utils_context));
			  mod_gl1_utils_timer_set_bitmap_refresh (&
								  (gl_context->
								   utils_context));
			  lw6map_style_clear (&map_style);
			}
		      else
			{
			  lw6sys_log (LW6SYS_LOG_ERROR,
				      _("unable to load data"));
			  _mod_gl1_quit (gl_context);
			  gl_context = NULL;
			}
		    }
		  else
		    {
		      lw6sys_log (LW6SYS_LOG_ERROR,
				  _("unable to set video mode"));
		      _mod_gl1_quit (gl_context);
		      gl_context = NULL;
		    }
		}
	      else
		{
		  lw6sys_log (LW6SYS_LOG_ERROR, _("unable to load consts"));
		  _mod_gl1_quit (gl_context);
		  gl_context = NULL;
		}
	    }

	  if (gl_context)
	    {
	      gl_context->utils_context.joysticks_info.supported =
		SDL_WasInit (SDL_INIT_JOYSTICK)
		|| !SDL_InitSubSystem (SDL_INIT_JOYSTICK);
	      if (gl_context->utils_context.joysticks_info.supported)
		{
		  mod_gl1_utils_joystick_init (&
					       (gl_context->
						utils_context.joysticks_info));
		}
	      else
		{
		  lw6sys_log (LW6SYS_LOG_NOTICE, _x_ ("no joystick support"));
		}
	    }

	  if (gl_context
	      && !(splash_ok && background_ok && hud_ok && menu_ok
		   && view_ok))
	    {
	      _mod_gl1_quit (gl_context);
	      gl_context = NULL;
	    }
	}
      else
	{
	  LW6SYS_FREE (gl_context);
	  gl_context = NULL;
	}
    }

  return gl_context;
}

/*
 * Ends-up all SDL stuff.
 */
void
_mod_gl1_quit (_mod_gl1_context_t * gl_context)
{
  float quit_sleep = 0.0f;

  lw6gui_input_quit (&(gl_context->utils_context.input));

  /*
   * Keep this value locally since it can disappear
   * when freeing stuff.
   */
  quit_sleep = gl_context->utils_context.const_data.quit_sleep;

  if (gl_context->utils_context.joysticks_info.supported)
    {
      mod_gl1_utils_joystick_quit (&
				   (gl_context->
				    utils_context.joysticks_info));
    }

  if (gl_context->splash_context)
    {
      mod_gl1_splash_quit (&(gl_context->utils_context),
			   gl_context->splash_context);
    }
  _mod_gl1_clear_background_backend (gl_context);
  _mod_gl1_clear_hud_backend (gl_context);
  _mod_gl1_clear_menu_backend (gl_context);
  _mod_gl1_clear_view_backend (gl_context);

  mod_gl1_utils_icon_unset (&(gl_context->utils_context));
  mod_gl1_utils_unload_data (&(gl_context->utils_context));
  mod_gl1_utils_unload_consts (&(gl_context->utils_context));

  mod_gl1_utils_path_quit (&(gl_context->utils_context));

  glFinish ();
  lw6sys_log (LW6SYS_LOG_INFO, _x_ ("SDL_ttf Quit"));
  TTF_Quit ();

  SDL_QuitSubSystem (SDL_INIT_JOYSTICK);
  /*
     SDL_QuitSubSystem (SDL_INIT_TIMER);
   */
  SDL_QuitSubSystem (SDL_INIT_VIDEO);

  if (lw6sys_sdl_unregister ())
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("SDL Quit"));
      SDL_Quit ();
    }

  if (gl_context->utils_context.bitmap_hash)
    {
      mod_gl1_utils_bitmap_hash_quit (gl_context->utils_context.bitmap_hash);
      gl_context->utils_context.bitmap_hash = NULL;
    }

  if (gl_context->utils_context.surface_counter.new_counter !=
      gl_context->utils_context.surface_counter.delete_counter)
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_
		  ("possible memory leak, %d calls to SDL_CreateSurface, IMG_Load or TTF_RenderUTF8, and %d calls to SDL_FreeSurface"),
		  gl_context->utils_context.surface_counter.new_counter,
		  gl_context->utils_context.surface_counter.delete_counter);
    }

  if (gl_context->utils_context.texture_counter.new_counter !=
      gl_context->utils_context.texture_counter.delete_counter)
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_
		  ("possible memory leak, %d calls to glGenTexture and %d calls to glDeleteTextures"),
		  gl_context->utils_context.texture_counter.new_counter,
		  gl_context->utils_context.texture_counter.delete_counter);
    }

  LW6SYS_FREE (gl_context);

  /*
   * For some reason, I suspect some segfaults occur when
   * "dlclosing" mod-gl1 just after SDL_Quit. Might be a handler
   * or callback called afterwards, whatever. So I prefer
   * "wasting" a little time when closing, one never knows,
   * it might better things.
   */
  lw6sys_sleep (quit_sleep);
}