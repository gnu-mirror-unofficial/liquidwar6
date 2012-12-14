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
#endif // HAVE_CONFIG_H

#include "liquidwar6.h"

/*
 * In liquidwar6gen
 */

static SCM
_scm_lw6gen_create_from_seed (SCM seed, SCM map_w, SCM map_h)
{
  SCM ret = SCM_BOOL_F;
  lw6map_level_t *c_level = NULL;
  char *c_seed = NULL;
  int c_map_w = 0;
  int c_map_h = 0;

  LW6SYS_SCRIPT_FUNCTION_BEGIN;
  lw6scm_coverage_call (lw6_global.coverage, __FUNCTION__);

  SCM_ASSERT (scm_is_string (seed), seed, SCM_ARG1, __FUNCTION__);
  SCM_ASSERT (scm_is_integer (map_w), map_w, SCM_ARG2, __FUNCTION__);
  SCM_ASSERT (scm_is_integer (map_h), map_h, SCM_ARG3, __FUNCTION__);

  c_seed = lw6scm_utils_to_0str (seed);
  if (c_seed)
    {
      c_map_w = scm_to_int (map_w);
      c_map_h = scm_to_int (map_h);

      c_level = lw6gen_create_from_seed (c_seed, c_map_w, c_map_h);
      if (c_level)
	{
	  ret = lw6_make_scm_map (c_level);
	}

      LW6SYS_FREE (c_seed);
    }

  LW6SYS_SCRIPT_FUNCTION_END;

  return ret;
}

/**
 * lw6_register_funcs_gen
 *
 * Register the functions of the gen module, make them callable from Guile.
 *
 * Return value: 1 on success, 0 if failed.
 */
int
lw6_register_funcs_gen ()
{
  int ret = 1;

  /*
   * In liquidwar6gen
   */
  ret = ret
    && lw6scm_c_define_gsubr (LW6DEF_C_LW6GEN_CREATE_FROM_SEED, 3, 0, 0,
			      (SCM (*)())_scm_lw6gen_create_from_seed);

  return ret;
}