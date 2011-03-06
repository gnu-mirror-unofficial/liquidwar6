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

#include "cfg.h"
#include "cfg-internal.h"
#include "../hlp/hlp.h"

int
lw6cfg_must_be_saved (char *key)
{
  int ret = 1;

  if (lw6hlp_match (key, LW6DEF_CONFIG_FILE) ||
      lw6hlp_match (key, LW6DEF_PREFIX) ||
      lw6hlp_match (key, LW6DEF_MOD_DIR) ||
      lw6hlp_match (key, LW6DEF_DATA_DIR) ||
      lw6hlp_match (key, LW6DEF_MUSIC_DIR) ||
      lw6hlp_match (key, LW6DEF_MAP_DIR)
      || lw6hlp_match (key, LW6DEF_SCRIPT_FILE))
    {
      /*
       * These options must not be save in the config file, doing so
       * would mess things up when upgrading the game (version change ==
       * change of paths to access data & the rest).
       */
      ret = 0;
    }

  return ret;
}

int
_lw6cfg_save (_lw6cfg_context_t * cfg_context, char *filename)
{
  int ret = 0;
  FILE *f;

  lw6sys_log (LW6SYS_LOG_INFO, _x_ ("saving config to \"%s\""), filename);

  _lw6cfg_parse_command_line (cfg_context);

  f = fopen (filename, "wb");
  if (f)
    {
      lw6sys_print_xml_header (f,
			       _x_
			       ("This is the main Liquid War 6 config file. Here you'll be able to tweak many, if not all, parameters in the game. Some of these values simply reflect changes you can make through the interface, some are not even present in the menus. What is sure is that if you can modify it by clicking somewhere in the game interface, it can surely be done here too. Note that this file is overwritten every time you run the game, your own comments and personnal touch in it will simply be squashed and disappear. But of course the values you set will be kept. All entries should be documented in the file. If in doubt, documentation is online on http://www.gnu.org/software/liquidwar6/manual/"));
      lw6sys_hash_sort_and_map (cfg_context->options,
				(lw6sys_assoc_callback_func_t)
				lw6cfg_write_xml_guess_type, (void *) f);
      lw6sys_print_xml_footer (f);
      fclose (f);
      ret = 1;
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_ ("could not open file \"%s\" in write mode"), filename);
    }

  return ret;
}

/**
 * lw6cfg_save
 *
 * @cfg_context: a context returned by @lw6cfg_init
 * @filename: a file path, absolute or relative
 *
 * Save current options into the given config file. Before saving
 * the file, all command line arguments will be read and will
 * override current values. This means the saved file will contain
 * values given as command line arguments.
 *
 * Return value: 1 if successfull, 0 if error.
 */
int
lw6cfg_save (void *cfg_context, char *filename)
{
  return _lw6cfg_save ((_lw6cfg_context_t *) cfg_context, filename);
}
