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

#include "dyn.h"

#define TEST_DYN_TOP_LEVEL_LIB "gfx"
#define TEST_DYN_BACKEND_NAME "gl1"

#define TEST_ARGC 2
#define TEST_ARGV0 "program"
#define TEST_ARGV1 "--toto=this-is-a-test"

static void
display_module (void *func_data, const char *key, void *value)
{
  int *found;
  const char *id;
  char *name;

  found = (int *) func_data;
  id = key;
  name = (char *) value;
  (*found) = 1;
  lw6sys_log (LW6SYS_LOG_NOTICE, _x_ ("module \"%s/%s\" \"%s\" found"),
	      TEST_DYN_TOP_LEVEL_LIB, id, name);
}

static int
test_list ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    lw6sys_assoc_t *list = NULL;
    int found = 0;
    const int argc = TEST_ARGC;
    const char *argv[] = { TEST_ARGV0, TEST_ARGV1 };

    list = lw6dyn_list_backends (argc, argv, TEST_DYN_TOP_LEVEL_LIB);
    if (list)
      {
	lw6sys_assoc_map (list, display_module, (void *) &found);
	lw6sys_assoc_free (list);
      }
    if (!found)
      {
	lw6sys_log (LW6SYS_LOG_WARNING, _x_ ("no module found for \"%s\""),
		    TEST_DYN_TOP_LEVEL_LIB);
      }
  }

  LW6SYS_TEST_FUNCTION_END;

  return ret;
}

/*
 * Testing path functions
 */
static int
test_path ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    char *library_path;
    const int argc = TEST_ARGC;
    const char *argv[] = { TEST_ARGV0, TEST_ARGV1 };

    library_path =
      lw6dyn_path_find_backend (argc, argv, TEST_DYN_TOP_LEVEL_LIB,
				TEST_DYN_BACKEND_NAME);
    if (library_path && lw6sys_file_exists (library_path))
      {
	lw6sys_log (LW6SYS_LOG_NOTICE,
		    _x_ ("found library \"%s/mod-%s\" in \"%s\""),
		    TEST_DYN_TOP_LEVEL_LIB, TEST_DYN_BACKEND_NAME,
		    library_path);
	LW6SYS_FREE (library_path);
      }

  }

  LW6SYS_TEST_FUNCTION_END;
  return ret;
}

/**
 * lw6dyn_test
 *
 * @mode: 0 for check only, 1 for full test
 *
 * Runs the @dyn module test suite, testing most (if not all...)
 * functions. Will try to load libraries and query them for
 * standard LW6-expected functions.
 *
 * Return value: 1 if test is successfull, 0 on error.
 */
int
lw6dyn_test (int mode)
{
  int ret = 0;

  if (lw6sys_false ())
    {
      /*
       * Just to make sure most functions are stuffed in the binary
       */
      lw6sys_test (mode);
    }

  ret = test_list () && test_path ();

  return ret;
}
