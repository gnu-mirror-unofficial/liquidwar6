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

#ifndef LIQUIDWAR6HLP_H
#define LIQUIDWAR6HLP_H

#include "../sys/sys.h"

#define LW6HLP_MAIN_BEGIN {lw6hlp_reference_init();}
#define LW6HLP_MAIN_END {lw6hlp_reference_quit();}

// used to create hash tables for help & config
#define LW6HLP_APPROX_NB_ENTRIES 421

typedef enum lw6hlp_type_e
{
  LW6HLP_TYPE_VOID = 0,
  LW6HLP_TYPE_STR = 1,
  LW6HLP_TYPE_INT = 2,
  LW6HLP_TYPE_FLOAT = 3,
  LW6HLP_TYPE_BOOL = 4,
  LW6HLP_TYPE_COLOR = 5
}
lw6hlp_type_t;

/* hlp-about.c */
extern int lw6hlp_is_documented (const char *keyword);
extern const char *lw6hlp_about (lw6hlp_type_t * type,
				 const char **default_value, int *min_value,
				 int *max_value, const char *keyword);
extern lw6hlp_type_t lw6hlp_get_type (const char *keyword);
extern const char *lw6hlp_get_default_value (const char *keyword);
extern int lw6hlp_get_min_value (const char *keyword);
extern int lw6hlp_get_max_value (const char *keyword);

/* hlp-credits.c */
extern char *lw6hlp_get_credits (int id);

/* hlp-keyword.c */
extern int lw6hlp_match (const char *keyword1, const char *keyword2);

/* hlp-list.c */
extern lw6sys_list_t *lw6hlp_list_quick ();
extern lw6sys_list_t *lw6hlp_list_doc ();
extern lw6sys_list_t *lw6hlp_list_show ();
extern lw6sys_list_t *lw6hlp_list_path ();
extern lw6sys_list_t *lw6hlp_list_players ();
extern lw6sys_list_t *lw6hlp_list_input ();
extern lw6sys_list_t *lw6hlp_list_graphics ();
extern lw6sys_list_t *lw6hlp_list_sound ();
extern lw6sys_list_t *lw6hlp_list_network ();
extern lw6sys_list_t *lw6hlp_list_map ();
extern lw6sys_list_t *lw6hlp_list_map_rules ();
extern lw6sys_list_t *lw6hlp_list_map_hints ();
extern lw6sys_list_t *lw6hlp_list_map_style ();
extern lw6sys_list_t *lw6hlp_list_map_teams ();
extern lw6sys_list_t *lw6hlp_list_funcs ();
extern lw6sys_list_t *lw6hlp_list_hooks ();
extern lw6sys_list_t *lw6hlp_list_advanced ();
extern lw6sys_list_t *lw6hlp_list_aliases ();
extern lw6sys_list_t *lw6hlp_list_team_colors ();
extern lw6sys_list_t *lw6hlp_list_weapons ();
extern lw6sys_list_t *lw6hlp_list ();

/* hlp-print.c */
extern void lw6hlp_print_keyword (lw6sys_list_t ** list, FILE * f);
extern void lw6hlp_print_content (lw6sys_list_t ** list, FILE * f);
extern void lw6hlp_print_about (const char *keyword, FILE * f);

/* hlp-reference.c */
extern int lw6hlp_reference_init ();
extern void lw6hlp_reference_quit ();

/* hlp-test.c */
extern int lw6hlp_test (int mode);

#endif
