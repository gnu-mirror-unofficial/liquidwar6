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
#endif

#include <CUnit/CUnit.h>

#include "tsk.h"

#define _TEST_MANAGER_SLEEP 1.0f
#define _TEST_LOOP_SLEEP 0.1f
#define _TEST_LOOP_N 600
#define _TEST_LOAD_MAP "subflower"
#define _TEST_OPTION_KEY1 LW6DEF_TOTAL_TIME
#define _TEST_OPTION_VALUE1 "250"
#define _TEST_OPTION_KEY2 LW6DEF_BACKGROUND_STYLE
#define _TEST_OPTION_VALUE2 "air"
#define _TEST_DISPLAY_WIDTH 640
#define _TEST_DISPLAY_HEIGHT 480
#define _TEST_SEED_1 "1234567890abcdef"
#define _TEST_SEED_2 "abcdef1234567890"

typedef struct _lw6tsk_test_data_s
{
  int ret;
} _lw6tsk_test_data_t;

static _lw6tsk_test_data_t _test_data = { 0 };

/*
 * Testing manager (ldr)
 */
static void
_test_manager_ldr ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    lw6tsk_loader_t *manager = NULL;
    char *repr;
    int i;
    char *map_path;
    lw6sys_assoc_t *default_param;
    lw6sys_assoc_t *forced_param;
    lw6map_level_t *level = NULL;
    lw6ker_game_struct_t *game_struct = NULL;
    lw6ker_game_state_t *game_state = NULL;
    int done = 0;
    float progress = 0.0f;
    char *user_dir;

    user_dir = lw6sys_get_default_user_dir ();
    if (user_dir)
      {
	manager =
	  lw6tsk_loader_new (_TEST_MANAGER_SLEEP, user_dir, &progress);
	if (manager)
	  {
	    map_path = lw6sys_get_default_map_path ();
	    if (map_path)
	      {
		default_param = lw6sys_assoc_new (lw6sys_free_callback);
		forced_param = lw6sys_assoc_new (lw6sys_free_callback);
		lw6sys_assoc_set (&default_param, _TEST_OPTION_KEY1,
				  lw6sys_str_copy (_TEST_OPTION_VALUE1));
		lw6sys_assoc_set (&forced_param, _TEST_OPTION_KEY2,
				  lw6sys_str_copy (_TEST_OPTION_VALUE2));
		if (default_param && forced_param)
		  {
		    lw6tsk_loader_push_ldr (manager, map_path, _TEST_LOAD_MAP,
					    default_param, forced_param,
					    _TEST_DISPLAY_WIDTH,
					    _TEST_DISPLAY_HEIGHT,
					    LW6LDR_DEFAULT_BENCH_VALUE,
					    LW6LDR_DEFAULT_MAGIC_NUMBER);
		    lw6sys_sleep (_TEST_LOOP_SLEEP);
		    lw6tsk_loader_push_ldr (manager, map_path, _TEST_LOAD_MAP,
					    default_param, forced_param,
					    _TEST_DISPLAY_WIDTH,
					    _TEST_DISPLAY_HEIGHT,
					    LW6LDR_DEFAULT_BENCH_VALUE,
					    LW6LDR_DEFAULT_MAGIC_NUMBER);
		    for (i = 0; i < _TEST_LOOP_N && !done; i++)
		      {
			lw6sys_sleep (_TEST_LOOP_SLEEP);
			repr = lw6tsk_loader_repr (manager);
			if (repr)
			  {
			    lw6sys_log (LW6SYS_LOG_NOTICE,
					_x_ ("waiting for manager \"%s\""),
					repr);
			    LW6SYS_FREE (repr);
			  }
			if (lw6tsk_loader_pop
			    (&level, &game_struct, &game_state, manager))
			  {
			    if (level && game_struct && game_state)
			      {
				done = 1;
				repr = lw6ker_game_struct_repr (game_struct);
				if (repr)
				  {
				    lw6sys_log (LW6SYS_LOG_NOTICE,
						_x_
						("loaded game_struct \"%s\""),
						repr);
				    LW6SYS_FREE (repr);
				  }
				repr = lw6ker_game_state_repr (game_state);
				if (repr)
				  {
				    lw6sys_log (LW6SYS_LOG_NOTICE,
						_x_
						("loaded game_state \"%s\""),
						repr);
				    LW6SYS_FREE (repr);
				  }
				lw6ker_game_state_free (game_state);
				game_state = NULL;
				lw6ker_game_struct_free (game_struct);
				game_struct = NULL;
				lw6map_free (level);
				level = NULL;
			      }
			    if (level)
			      {
				repr = lw6map_repr (level);
				if (repr)
				  {
				    lw6sys_log (LW6SYS_LOG_NOTICE,
						_x_ ("loaded map \"%s\""),
						repr);
				    LW6SYS_FREE (repr);
				  }
				lw6map_free (level);
				level = NULL;
			      }
			  }
		      }
		    lw6sys_assoc_free (default_param);
		    lw6sys_assoc_free (forced_param);

		  }
		LW6SYS_FREE (map_path);
	      }
	    lw6tsk_loader_free (manager);
	  }
	else
	  {
	    ret = 0;
	  }
	LW6SYS_FREE (user_dir);
      }
    else
      {
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
}

/*
 * Testing manager (gen)
 */
static void
_test_manager_gen ()
{
  int ret = 1;
  LW6SYS_TEST_FUNCTION_BEGIN;

  {
    lw6tsk_loader_t *manager = NULL;
    char *repr;
    int i;
    lw6map_level_t *level = NULL;
    lw6ker_game_struct_t *game_struct = NULL;
    lw6ker_game_state_t *game_state = NULL;
    int done = 0;
    float progress = 0.0f;
    char *user_dir;

    user_dir = lw6sys_get_default_user_dir ();
    if (user_dir)
      {
	manager =
	  lw6tsk_loader_new (_TEST_MANAGER_SLEEP, user_dir, &progress);
	if (manager)
	  {
	    lw6tsk_loader_push_gen (manager, _TEST_SEED_1,
				    _TEST_DISPLAY_WIDTH,
				    _TEST_DISPLAY_HEIGHT,
				    LW6LDR_DEFAULT_BENCH_VALUE,
				    LW6LDR_DEFAULT_MAGIC_NUMBER);
	    lw6sys_sleep (_TEST_LOOP_SLEEP);
	    lw6tsk_loader_push_gen (manager, _TEST_SEED_2,
				    _TEST_DISPLAY_WIDTH,
				    _TEST_DISPLAY_HEIGHT,
				    LW6LDR_DEFAULT_BENCH_VALUE,
				    LW6LDR_DEFAULT_MAGIC_NUMBER);
	    for (i = 0; i < _TEST_LOOP_N && !done; i++)
	      {
		lw6sys_sleep (_TEST_LOOP_SLEEP);
		repr = lw6tsk_loader_repr (manager);
		if (repr)
		  {
		    lw6sys_log (LW6SYS_LOG_NOTICE,
				_x_ ("waiting for manager \"%s\""), repr);
		    LW6SYS_FREE (repr);
		  }
		if (lw6tsk_loader_pop
		    (&level, &game_struct, &game_state, manager))
		  {
		    if (level && game_struct && game_state)
		      {
			done = 1;
			repr = lw6ker_game_struct_repr (game_struct);
			if (repr)
			  {
			    lw6sys_log (LW6SYS_LOG_NOTICE,
					_x_
					("generated game_struct \"%s\""),
					repr);
			    LW6SYS_FREE (repr);
			  }
			repr = lw6ker_game_state_repr (game_state);
			if (repr)
			  {
			    lw6sys_log (LW6SYS_LOG_NOTICE,
					_x_
					("generated game_state \"%s\""),
					repr);
			    LW6SYS_FREE (repr);
			  }
			lw6ker_game_state_free (game_state);
			game_state = NULL;
			lw6ker_game_struct_free (game_struct);
			game_struct = NULL;
			lw6map_free (level);
			level = NULL;
		      }
		    if (level)
		      {
			repr = lw6map_repr (level);
			if (repr)
			  {
			    lw6sys_log (LW6SYS_LOG_NOTICE,
					_x_ ("generated map \"%s\""), repr);
			    LW6SYS_FREE (repr);
			  }
			lw6map_free (level);
			level = NULL;
		      }
		  }
	      }
	    lw6tsk_loader_free (manager);
	  }
	else
	  {
	    ret = 0;
	  }
	LW6SYS_FREE (user_dir);
      }
    else
      {
	ret = 0;
      }
  }

  LW6SYS_TEST_FUNCTION_END;
}

static int
_setup_init ()
{
  lw6sys_log (LW6SYS_LOG_NOTICE, _x_ ("init libtsk CUnit test suite"));
  return CUE_SUCCESS;
}

static int
_setup_quit ()
{
  lw6sys_log (LW6SYS_LOG_NOTICE, _x_ ("quit libtsk CUnit test suite"));
  return CUE_SUCCESS;
}

/**
 * lw6tsk_test_register
 *
 * @mode: test mode (bitmask)
 *
 * Registers all tests for the libtsk module.
 *
 * Return value: 1 if test is successfull, 0 on error.
 */
int
lw6tsk_test_register (int mode)
{
  int ret = 1;
  CU_Suite *suite;

  if (lw6sys_false ())
    {
      /*
       * Just to make sure most functions are stuffed in the binary
       */
      lw6sys_test_register (mode);
      lw6cfg_test_register (mode);
      lw6hlp_test_register (mode);
      lw6map_test_register (mode);
      lw6ker_test_register (mode);
      lw6ldr_test_register (mode);
      lw6gen_test_register (mode);
    }

  suite = CU_add_suite ("lw6tsk", _setup_init, _setup_quit);
  if (suite)
    {
      LW6SYS_CUNIT_ADD_TEST (suite, _test_manager_ldr);
      LW6SYS_CUNIT_ADD_TEST (suite, _test_manager_gen);
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_ ("unable to add CUnit test suite, error msg is \"%s\""),
		  CU_get_error_msg ());
      ret = 0;
    }

  return ret;
}

/**
 * lw6tsk_test_run
 *
 * @mode: test mode (bitmask)
 *
 * Runs the @tsk module test suite, testing most (if not all...)
 * functions.
 *
 * Return value: 1 if test is successfull, 0 on error.
 */
int
lw6tsk_test_run (int mode)
{
  int ret = 0;

  _test_data.ret = 1;
  if (lw6sys_cunit_run_tests (mode))
    {
      ret = _test_data.ret;
    }

  return ret;
}
