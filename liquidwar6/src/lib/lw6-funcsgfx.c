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
#endif // HAVE_CONFIG_H

#include "liquidwar6.h"

/*
 * In liquidwar6gfx
 */

/*
 * In backend.c
 */
static SCM
_scm_lw6gfx_get_backends ()
{
  SCM ret = SCM_BOOL_F;
  lw6sys_assoc_t *backends;
  lw6sys_list_t *keys;
  lw6sys_list_t *key;
  char *module_id;
  char *module_name;

  LW6SYS_SCRIPT_FUNCTION_BEGIN;
  lw6scm_coverage_call (lw6_global.coverage, __FUNCTION__);

  backends = lw6gfx_get_backends (lw6_global.argc, lw6_global.argv);
  if (backends)
    {
      keys = lw6sys_assoc_keys (backends);
      if (keys)
	{
	  ret = SCM_EOL;
	  key = keys;
	  while (key)
	    {
	      if (key->data)
		{
		  module_id = (char *) key->data;
		  module_name =
		    (char *) lw6sys_assoc_get (backends, module_id);
		  ret =
		    scm_cons (scm_cons
			      (scm_from_locale_string (module_id),
			       scm_from_locale_string (module_name)), ret);
		}
	      key = lw6sys_list_next (key);
	    }
	  lw6sys_list_free (keys);
	  ret = scm_reverse (ret);
	}
      lw6sys_assoc_free (backends);
    }

  LW6SYS_SCRIPT_FUNCTION_END;

  return ret;
}

/**
 * lw6_register_funcs_gfx
 *
 * Register the functions of the gfx module, make them callable from Guile.
 *
 * Return value: 1 on success, 0 if failed.
 */
int
lw6_register_funcs_gfx ()
{
  int ret = 1;

  /*
   * In backend.c
   */
  ret = ret && lw6scm_c_define_gsubr (LW6DEF_C_LW6GFX_GET_BACKENDS, 0, 0, 0,
				      (SCM (*)())_scm_lw6gfx_get_backends);

  return ret;
}
