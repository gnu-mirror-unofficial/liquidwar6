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

#include <string.h>

#include "ldr.h"
#include "ldr-internal.h"

#define EXAMPLE_DIR "example"

#define EXAMPLE_ROUNDS_PER_SEC 45
#define EXAMPLE_MOVES_PER_ROUND 2
#define EXAMPLE_START_RED_X 50
#define EXAMPLE_START_RED_Y 50
#define EXAMPLE_START_GREEN_X 50
#define EXAMPLE_START_GREEN_Y 5
#define EXAMPLE_START_BLUE_X 50
#define EXAMPLE_START_BLUE_Y 95

#define EXAMPLE_FIGHTER_SCALE 2.5f
#define EXAMPLE_SYSTEM_COLOR_AUTO 0

#define EXAMPLE_GUESS_COLOR 0
#define EXAMPLE_COLOR_BASE_BG LW6SYS_COLOR_8_BLUE
#define EXAMPLE_COLOR_BASE_FG LW6SYS_COLOR_8_WHITE
#define EXAMPLE_COLOR_ALTERNATE_BG LW6SYS_COLOR_8_BLACK
#define EXAMPLE_COLOR_ALTERNATE_FG LW6SYS_COLOR_8_RED

#define EXAMPLE_PLAYER_COLOR "red"
#define EXAMPLE_NB_BOTS 3
#define EXAMPLE_BOT1_COLOR "green"
#define EXAMPLE_BOT1_AI "idiot"
#define EXAMPLE_BOT2_COLOR "blue"
#define EXAMPLE_BOT2_AI "random"
#define EXAMPLE_BOT3_COLOR "yellow"
#define EXAMPLE_BOT3_AI "follow"

/**
 * lw6ldr_print_example_rules_xml
 *
 * @f: file to output content to
 *
 * Print to a file a typical map rules.xml file.
 * 
 * Return value: none.
 */
void
lw6ldr_print_example_rules_xml (FILE * f)
{
  lw6map_rules_t rules;

  memset (&rules, 0, sizeof (lw6map_rules_t));
  lw6map_rules_defaults (&rules);

  lw6sys_print_xml_header (f,
			   _x_
			   ("This is an example Liquid War 6 'rules.xml' file. This file can be put along with a 'map.png' file to set up some parameters to your own preferred values. However, it's not required, a map can live without any 'rules.xml' file, defaults will be used, that's all. Note that this example only defines a few parameters, there are many more of them. The idea is to modify just the settings which are important for your map, and let the user choose the best values for other items. Happy hacking!"));
  lw6cfg_write_xml_int (f, LW6DEF_ROUNDS_PER_SEC, EXAMPLE_ROUNDS_PER_SEC);
  lw6cfg_write_xml_int (f, LW6DEF_MOVES_PER_ROUND, EXAMPLE_MOVES_PER_ROUND);
  lw6cfg_write_xml_int (f, LW6DEF_START_RED_X, EXAMPLE_START_RED_X);
  lw6cfg_write_xml_int (f, LW6DEF_START_RED_Y, EXAMPLE_START_RED_Y);
  lw6cfg_write_xml_int (f, LW6DEF_START_GREEN_X, EXAMPLE_START_GREEN_X);
  lw6cfg_write_xml_int (f, LW6DEF_START_GREEN_Y, EXAMPLE_START_GREEN_Y);
  lw6cfg_write_xml_int (f, LW6DEF_START_BLUE_X, EXAMPLE_START_BLUE_X);
  lw6cfg_write_xml_int (f, LW6DEF_START_BLUE_Y, EXAMPLE_START_BLUE_Y);
  lw6sys_print_xml_footer (f);
  lw6map_rules_clear (&rules);
}

/**
 * lw6ldr_print_example_hints_xml
 *
 * @f: file to output content to
 *
 * Print to a file a typical map hints.xml file.
 * 
 * Return value: none.
 */
void
lw6ldr_print_example_hints_xml (FILE * f)
{
  lw6ldr_hints_t hints;

  lw6ldr_hints_zero (&hints);
  lw6ldr_hints_defaults (&hints);
  lw6sys_print_xml_header (f,
			   _x_
			   ("This is an example Liquid War 6 'hints.xml' file. This file can be put along with a 'map.png' file to change the behavior of the map. It is used by the map loader to decide wether it should, for instance, adapt the map to the screen size, guess colors automatically, and such things. It does not really define any real map parameter, it just give clues to the map loader. Note that this example only defines a few parameters, there are many more of them. The idea is to modify just the settings which are important for your map, and let the user choose the best values for other items. Happy hacking!"));

  lw6cfg_write_xml_float (f, LW6DEF_FIGHTER_SCALE, EXAMPLE_FIGHTER_SCALE);
  lw6cfg_write_xml_bool (f, LW6DEF_SYSTEM_COLOR_AUTO,
			 EXAMPLE_SYSTEM_COLOR_AUTO);

  lw6sys_print_xml_footer (f);
  lw6ldr_hints_clear (&hints);
}

/**
 * lw6ldr_print_example_style_xml
 *
 * @f: file to output content to
 *
 * Print to a file a typical map style.xml file.
 * 
 * Return value: none.
 */
void
lw6ldr_print_example_style_xml (FILE * f)
{
  lw6map_style_t style;
  memset (&style, 0, sizeof (lw6map_style_t));
  lw6map_style_defaults (&style);
  lw6sys_print_xml_header (f,
			   _x_
			   ("This is an example Liquid War 6 'style.xml' file. This file can be put along with a 'map.png' file to change the look of the map. It will not change the gameplay at all, all gameplay related parameters are in 'rules.xml', and, to some extent, 'hints.xml'. This file is not required, a map can live without any 'style.xml' file, defaults will be used, that's all. Note that this example only defines a few parameters, there are many more of them. The idea is to modify just the settings which are important for your map, and let the user choose the best values for other items. Happy hacking!"));

  lw6cfg_write_xml_bool (f, LW6DEF_GUESS_COLORS, EXAMPLE_GUESS_COLOR);
  lw6cfg_write_xml_color (f, LW6DEF_COLOR_BASE_BG, EXAMPLE_COLOR_BASE_BG);
  lw6cfg_write_xml_color (f, LW6DEF_COLOR_BASE_FG, EXAMPLE_COLOR_BASE_FG);
  lw6cfg_write_xml_color (f,
			  LW6DEF_COLOR_ALTERNATE_BG,
			  EXAMPLE_COLOR_ALTERNATE_BG);
  lw6cfg_write_xml_color (f,
			  LW6DEF_COLOR_ALTERNATE_FG,
			  EXAMPLE_COLOR_ALTERNATE_FG);
  lw6sys_print_xml_footer (f);
  lw6map_style_clear (&style);
}

/**
 * lw6ldr_print_example_teams_xml
 *
 * @f: file to output content to
 *
 * Print to a file a typical map teams.xml file.
 * 
 * Return value: none.
 */
void
lw6ldr_print_example_teams_xml (FILE * f)
{
  lw6map_teams_t teams;

  lw6map_teams_zero (&teams);
  lw6map_teams_defaults (&teams);
  lw6sys_print_xml_header (f,
			   _x_
			   ("This is an example Liquid War 6 'teams.xml' file. This file can be put along with a 'map.png' file to explicitely say you want this kind of bot, with this color, and so on. This is not a required file, if not present, defaults will be used, however it's a really good way to personnalize a map, this is just how you populate it by default. Another important parameter is the default color for the player, changing this allows the player to try out various colors along its journey in the game."));

  lw6cfg_write_xml_string (f, LW6DEF_PLAYER_COLOR, EXAMPLE_PLAYER_COLOR);
  lw6cfg_write_xml_int (f, LW6DEF_NB_BOTS, EXAMPLE_NB_BOTS);
  lw6cfg_write_xml_string (f, LW6DEF_BOT1_COLOR, EXAMPLE_BOT1_COLOR);
  lw6cfg_write_xml_string (f, LW6DEF_BOT1_AI, EXAMPLE_BOT1_AI);
  lw6cfg_write_xml_string (f, LW6DEF_BOT2_COLOR, EXAMPLE_BOT2_COLOR);
  lw6cfg_write_xml_string (f, LW6DEF_BOT2_AI, EXAMPLE_BOT2_AI);
  lw6cfg_write_xml_string (f, LW6DEF_BOT3_COLOR, EXAMPLE_BOT3_COLOR);
  lw6cfg_write_xml_string (f, LW6DEF_BOT3_AI, EXAMPLE_BOT3_AI);
  lw6sys_print_xml_footer (f);
  lw6map_teams_clear (&teams);
}

/**
 * lw6ldr_print_examples
 *
 * @user_dir: the user directory or at least, a writable one
 *
 * Writes all example XML files in 'user_dir/example/', will
 * create the directory if needed.
 *
 * Return value: 1 if success, 0 if failed.
 */
int
lw6ldr_print_examples (char *user_dir)
{
  int ret = 0;
  char *example_dir = NULL;
  char *filename = NULL;
  FILE *f;
  int rules_ok = 0;
  int hints_ok = 0;
  int style_ok = 0;
  int teams_ok = 0;
  example_dir = lw6sys_path_concat (user_dir, EXAMPLE_DIR);
  if (example_dir)
    {
      if (!lw6sys_dir_exists (example_dir))
	{
	  lw6sys_create_dir (example_dir);
	}
      if (lw6sys_dir_exists (example_dir))
	{
	  filename = lw6sys_path_concat (example_dir, _LW6LDR_FILE_RULES_XML);
	  if (filename)
	    {
	      f = fopen (filename, "wb");
	      if (f)
		{
		  lw6sys_log (LW6SYS_LOG_INFO,
			      _x_
			      ("writing example map rules file in \"%s\""),
			      filename);
		  lw6ldr_print_example_rules_xml (f);
		  rules_ok = 1;
		  fclose (f);
		}
	      LW6SYS_FREE (filename);
	    }
	  filename = lw6sys_path_concat (example_dir, _LW6LDR_FILE_HINTS_XML);
	  if (filename)
	    {
	      f = fopen (filename, "wb");
	      if (f)
		{
		  lw6sys_log (LW6SYS_LOG_INFO,
			      _x_
			      ("writing example map hints file in \"%s\""),
			      filename);
		  lw6ldr_print_example_hints_xml (f);
		  hints_ok = 1;
		  fclose (f);
		}
	      LW6SYS_FREE (filename);
	    }
	  filename = lw6sys_path_concat (example_dir, _LW6LDR_FILE_STYLE_XML);
	  if (filename)
	    {
	      f = fopen (filename, "wb");
	      if (f)
		{
		  lw6sys_log (LW6SYS_LOG_INFO,
			      _x_
			      ("writing example map style file in \"%s\""),
			      filename);
		  lw6ldr_print_example_style_xml (f);
		  style_ok = 1;
		  fclose (f);
		}
	      LW6SYS_FREE (filename);
	    }
	  filename = lw6sys_path_concat (example_dir, _LW6LDR_FILE_TEAMS_XML);
	  if (filename)
	    {
	      f = fopen (filename, "wb");
	      if (f)
		{
		  lw6sys_log (LW6SYS_LOG_INFO,
			      _x_
			      ("writing example map teams file in \"%s\""),
			      filename);
		  lw6ldr_print_example_teams_xml (f);
		  teams_ok = 1;
		  fclose (f);
		}
	      LW6SYS_FREE (filename);
	    }
	}
      LW6SYS_FREE (example_dir);
    }

  ret = (rules_ok && hints_ok && style_ok && teams_ok);
  return ret;
}
