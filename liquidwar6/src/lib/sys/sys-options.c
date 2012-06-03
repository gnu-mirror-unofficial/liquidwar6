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

#include <string.h>

#include "sys.h"

#ifndef LW6_MS_WINDOWS
#include <unistd.h>
#endif

#define CONFIG_FILE "config.xml"
#define LOG_FILE "log.csv"
#define MOD_LIBDIR_MASK "%s/%s-%s"
#define MOD_PREFIX_MASK "%s/lib/%s-%s"
#define SHARE_DATADIR_MASK "%s/%s-%s"
#define SHARE_PREFIX_MASK "%s/share/%s-%s"
#ifdef LW6_MAC_OS_X
#define RUN_REL "../Resources"
#define APPLICATION_SUPPORT "Library/Application Support"
#else
#define RUN_REL "."
#endif
#define DATA_DIR "data"
#define MUSIC_DIR "music"
#define MAP_DIR "map"
#define SCRIPT_FILE "script/liquidwar6.scm"
#ifdef LW6_MS_WINDOWS
#define README_FILE "readme.txt"
#else
#define README_FILE "README"
#endif
#define CWD_SIZE 2048

/**
 * lw6sys_get_default_user_dir
 *
 * Returns the default user directory. Note that this value
 * is not static, it can depend, for instance, of the environment
 * variable @HOME.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_user_dir ()
{
  char *home_dir = NULL;
  char *user_dir = NULL;
  char *relative = NULL;

  home_dir = lw6sys_get_home ();
  if (home_dir)
    {
#ifdef LW6_MS_WINDOWS
      relative = lw6sys_str_copy (lw6sys_build_get_package_name ());
#else
#ifdef LW6_MAC_OS_X
      relative =
	lw6sys_path_concat (APPLICATION_SUPPORT,
			    lw6sys_build_get_package_name ());
#else
      relative = lw6sys_str_concat (".", lw6sys_build_get_package_tarname ());
#endif
#endif
      if (relative)
	{
	  user_dir = lw6sys_path_concat (home_dir, relative);
	  LW6SYS_FREE (relative);
	}
      LW6SYS_FREE (home_dir);
    }

  return user_dir;
}

static char *
get_config_file_with_user_dir (char *user_dir)
{
  char *config_file;

  config_file = lw6sys_path_concat (user_dir, CONFIG_FILE);

  return config_file;
}

/**
 * lw6sys_get_default_config_file
 *
 * Returns the default config file. Note that this value
 * is not static, it can depend, for instance, of the environment
 * variable @HOME.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_config_file ()
{
  char *config_file = NULL;
  char *user_dir = NULL;

  user_dir = lw6sys_get_default_user_dir ();
  if (user_dir)
    {
      config_file = get_config_file_with_user_dir (user_dir);
      LW6SYS_FREE (user_dir);
    }

  return config_file;
}

static char *
get_log_file_with_user_dir (char *user_dir)
{
  char *log_file;

  log_file = lw6sys_path_concat (user_dir, LOG_FILE);

  return log_file;
}

/**
 * lw6sys_get_default_log_file
 *
 * Returns the default log file. Note that this value
 * is not static, it can depend, for instance, of the environment
 * variable @HOME.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_log_file ()
{
  char *log_file = NULL;
  char *user_dir = NULL;

  user_dir = lw6sys_get_default_user_dir ();
  if (user_dir)
    {
      log_file = get_log_file_with_user_dir (user_dir);
      LW6SYS_FREE (user_dir);
    }

  return log_file;
}

/**
 * lw6sys_get_default_prefix
 *
 * Returns the default prefix, could be /usr/local for instance.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_prefix ()
{
  char *prefix = NULL;

  prefix = lw6sys_path_strip_slash (lw6sys_build_get_prefix ());

  return prefix;
}

static char *
get_dir_common (char *mask1, char *prefix1, char *mask2, char *prefix2,
		char *sub, int check_readme)
{
  char *system_dir = NULL;
  char *top_srcdir = NULL;
  char *dir = NULL;
  int dir_exists = 0;

  if (dir == NULL)
    {
      system_dir =
	lw6sys_new_sprintf (mask1, prefix1,
			    lw6sys_build_get_package_tarname (),
			    lw6sys_build_get_version ());
      if (system_dir)
	{
	  dir = lw6sys_path_concat (system_dir, sub);
	  if (dir)
	    {
	      dir_exists =
		check_readme ?
		lw6sys_dir_exists_with_readme_containing_text (dir,
							       lw6sys_build_get_home_url
							       ()) :
		lw6sys_dir_exists (dir);
	      if (!dir_exists)
		{
		  // directory doesn't exist, we ignore it
		  LW6SYS_FREE (dir);
		  dir = NULL;
		}
	    }
	  LW6SYS_FREE (system_dir);
	}
    }

  if (dir == NULL)
    {
      system_dir =
	lw6sys_new_sprintf (mask2, prefix2,
			    lw6sys_build_get_package_tarname (),
			    lw6sys_build_get_version ());
      if (system_dir)
	{
	  dir = lw6sys_path_concat (system_dir, sub);
	  if (dir)
	    {
	      dir_exists =
		check_readme ?
		lw6sys_dir_exists_with_readme_containing_text (dir,
							       lw6sys_build_get_home_url
							       ()) :
		lw6sys_dir_exists (dir);
	      if (!dir_exists)
		{
		  // directory doesn't exist, we ignore it
		  LW6SYS_FREE (dir);
		  dir = NULL;
		}
	    }
	  LW6SYS_FREE (system_dir);
	}
    }

  if (dir == NULL && strlen (sub) > 0)
    {
      top_srcdir = lw6sys_build_get_top_srcdir ();
      dir = lw6sys_path_concat (top_srcdir, sub);
      if (dir)
	{
	  dir_exists =
	    check_readme ? lw6sys_dir_exists_with_readme_containing_text (dir,
									  lw6sys_build_get_home_url
									  ())
	    : lw6sys_dir_exists (dir);
	  if (!dir_exists)
	    {
	      // directory doesn't exist, we ignore it
	      LW6SYS_FREE (dir);
	      dir = NULL;
	    }
	}
    }

  return dir;
}

static void
dir_if_not_found (char **dir, const char *sub, int check_readme)
{
  char *tmp = NULL;
  char *parent1 = NULL;
  char *parent2 = NULL;
  char *parent3 = NULL;
  int dir_exists = 0;

  if (dir && *dir)
    {
      dir_exists =
	check_readme ? lw6sys_dir_exists_with_readme_containing_text (*dir,
								      lw6sys_build_get_home_url
								      ()) :
	lw6sys_dir_exists (*dir);
      if (!dir_exists)
	{
	  parent1 = lw6sys_path_parent (".");
	  if (parent1)
	    {
	      tmp = lw6sys_path_concat (parent1, sub);
	      dir_exists =
		check_readme ?
		lw6sys_dir_exists_with_readme_containing_text (tmp,
							       lw6sys_build_get_home_url
							       ()) :
		lw6sys_dir_exists (tmp);
	      if (dir_exists)
		{
		  LW6SYS_FREE (*dir);
		  (*dir) = tmp;
		}
	      else
		{
		  LW6SYS_FREE (tmp);
		  parent2 = lw6sys_path_parent (parent1);
		  if (parent2)
		    {
		      tmp = lw6sys_path_concat (parent2, sub);
		      dir_exists =
			check_readme ?
			lw6sys_dir_exists_with_readme_containing_text (tmp,
								       lw6sys_build_get_home_url
								       ()) :
			lw6sys_dir_exists (tmp);
		      if (dir_exists)
			{
			  LW6SYS_FREE (*dir);
			  (*dir) = tmp;
			}
		      else
			{
			  LW6SYS_FREE (tmp);
			  parent3 = lw6sys_path_parent (parent2);
			  if (parent3)
			    {
			      tmp = lw6sys_path_concat (parent3, sub);
			      dir_exists =
				check_readme ?
				lw6sys_dir_exists_with_readme_containing_text
				(tmp,
				 lw6sys_build_get_home_url ()) :
				lw6sys_dir_exists (tmp);
			      if (dir_exists)
				{
				  LW6SYS_FREE (*dir);
				  (*dir) = tmp;
				}
			      else
				{
				  LW6SYS_FREE (tmp);
				}
			      LW6SYS_FREE (parent3);
			    }
			}
		      LW6SYS_FREE (parent2);
		    }
		}
	      LW6SYS_FREE (parent1);
	    }
	  if (!lw6sys_dir_exists (*dir))
	    {
	      tmp = lw6sys_path_concat (lw6sys_build_get_package_id (), sub);
	      if (tmp)
		{
		  dir_exists =
		    check_readme ?
		    lw6sys_dir_exists_with_readme_containing_text (tmp,
								   lw6sys_build_get_home_url
								   ()) :
		    lw6sys_dir_exists (tmp);
		  if (dir_exists)
		    {
		      LW6SYS_FREE (*dir);
		      (*dir) = tmp;
		    }
		  else
		    {
		      LW6SYS_FREE (tmp);
		    }
		}
	      tmp =
		lw6sys_path_concat (lw6sys_build_get_package_string (), sub);
	      if (tmp)
		{
		  dir_exists =
		    check_readme ?
		    lw6sys_dir_exists_with_readme_containing_text (tmp,
								   lw6sys_build_get_home_url
								   ()) :
		    lw6sys_dir_exists (tmp);
		  if (dir_exists)
		    {
		      LW6SYS_FREE (*dir);
		      (*dir) = tmp;
		    }
		  else
		    {
		      LW6SYS_FREE (tmp);
		    }
		}
	      tmp =
		lw6sys_path_concat (lw6sys_build_get_package_tarname (), sub);
	      if (tmp)
		{
		  dir_exists =
		    check_readme ?
		    lw6sys_dir_exists_with_readme_containing_text (tmp,
								   lw6sys_build_get_home_url
								   ()) :
		    lw6sys_dir_exists (tmp);
		  if (dir_exists)
		    {
		      LW6SYS_FREE (*dir);
		      (*dir) = tmp;
		    }
		  else
		    {
		      LW6SYS_FREE (tmp);
		    }
		}
	      tmp =
		lw6sys_path_concat (lw6sys_build_get_package_name (), sub);
	      if (tmp)
		{
		  dir_exists =
		    check_readme ?
		    lw6sys_dir_exists_with_readme_containing_text (tmp,
								   lw6sys_build_get_home_url
								   ()) :
		    lw6sys_dir_exists (tmp);
		  if (dir_exists)
		    {
		      LW6SYS_FREE (*dir);
		      (*dir) = tmp;
		    }
		  else
		    {
		      LW6SYS_FREE (tmp);
		    }
		}
	    }
	}
    }
}

static char *
get_dir (char *mask1, char *prefix1, char *mask2, char *prefix2, char *sub,
	 int check_readme)
{
  char *dir = NULL;

  dir = get_dir_common (mask1, prefix1, mask2, prefix2, sub, check_readme);

  if (dir == NULL)
    {
      // if not installed, if no source, then search in local directory
      dir = lw6sys_path_concat (".", sub);
    }

  dir_if_not_found (&dir, sub, check_readme);

  return dir;
}

static char *
get_dir_argc_argv (int argc, const char *argv[], char *mask1, char *prefix1,
		   char *mask2, char *prefix2, char *sub, int check_readme)
{
  char *dir = NULL;
  char *run_dir = NULL;
  char *run_dir_rel = NULL;
  int dir_exists = 0;

  dir = get_dir_common (mask1, prefix1, mask2, prefix2, sub, check_readme);

  if (dir == NULL && strlen (sub) > 0)
    {
      run_dir = lw6sys_get_run_dir (argc, argv);
      if (run_dir)
	{
	  dir = lw6sys_path_concat (run_dir, sub);
	  if (dir)
	    {
	      dir_exists =
		check_readme ?
		lw6sys_dir_exists_with_readme_containing_text (dir,
							       lw6sys_build_get_home_url
							       ()) :
		lw6sys_dir_exists (dir);
	      if (!dir_exists)
		{
		  // directory doesn't exist, we ignore it
		  LW6SYS_FREE (dir);
		  dir = NULL;

		  if (RUN_REL && strlen (RUN_REL))
		    {
		      run_dir_rel = lw6sys_path_concat (run_dir, RUN_REL);
		      if (run_dir_rel)
			{
			  if (lw6sys_dir_exists (run_dir_rel))
			    {
			      dir = lw6sys_path_concat (run_dir_rel, sub);
			      if (dir)
				{
				  dir_exists =
				    check_readme ?
				    lw6sys_dir_exists_with_readme_containing_text
				    (dir,
				     lw6sys_build_get_home_url ()) :
				    lw6sys_dir_exists (dir);
				  if (!dir_exists)
				    {
				      LW6SYS_FREE (dir);
				      dir = NULL;
				      // directory doesn't exist, we ignore it
				    }
				}
			    }
			  LW6SYS_FREE (run_dir_rel);
			}
		    }
		}
	    }
	  LW6SYS_FREE (run_dir);
	}
    }

  if (dir == NULL)
    {
      // if not installed, if no source, then search in local directory
      dir = lw6sys_path_concat (".", sub);
    }

  dir_if_not_found (&dir, sub, check_readme);

  return dir;
}

static char *
get_file_common (char *mask1, char *prefix1, char *mask2, char *prefix2,
		 char *sub)
{
  char *system_dir = NULL;
  char *top_srcdir = NULL;
  char *file = NULL;

  if (file == NULL)
    {
      system_dir =
	lw6sys_new_sprintf (mask1, prefix1,
			    lw6sys_build_get_package_tarname (),
			    lw6sys_build_get_version ());
      if (system_dir)
	{
	  file = lw6sys_path_concat (system_dir, sub);
	  if (file)
	    {
	      if (!lw6sys_file_exists (file))
		{
		  // file doesn't exist, we ignore it
		  LW6SYS_FREE (file);
		  file = NULL;
		}
	    }
	  LW6SYS_FREE (system_dir);
	}
    }

  if (file == NULL)
    {
      system_dir =
	lw6sys_new_sprintf (mask2, prefix2,
			    lw6sys_build_get_package_tarname (),
			    lw6sys_build_get_version ());
      if (system_dir)
	{
	  file = lw6sys_path_concat (system_dir, sub);
	  if (file)
	    {
	      if (!lw6sys_file_exists (file))
		{
		  // file doesn't exist, we ignore it
		  LW6SYS_FREE (file);
		  file = NULL;
		}
	    }
	  LW6SYS_FREE (system_dir);
	}
    }

  if (file == NULL && strlen (sub) > 0)
    {
      top_srcdir = lw6sys_build_get_top_srcdir ();
      file = lw6sys_path_concat (top_srcdir, sub);
      if (file)
	{
	  if (!lw6sys_file_exists (file))
	    {
	      // file doesn't exist, we ignore it
	      LW6SYS_FREE (file);
	      file = NULL;
	    }
	}
    }

  return file;
}

static void
file_if_not_found (char **file, const char *sub)
{
  char *tmp = NULL;
  char *parent1 = NULL;
  char *parent2 = NULL;
  char *parent3 = NULL;

  if (file && *file && !lw6sys_file_exists (*file))
    {
      parent1 = lw6sys_path_parent (".");
      if (parent1)
	{
	  tmp = lw6sys_path_concat (parent1, sub);
	  if (lw6sys_file_exists (tmp))
	    {
	      LW6SYS_FREE (*file);
	      (*file) = tmp;
	    }
	  else
	    {
	      LW6SYS_FREE (tmp);
	      parent2 = lw6sys_path_parent (parent1);
	      if (parent2)
		{
		  tmp = lw6sys_path_concat (parent2, sub);
		  if (lw6sys_file_exists (tmp))
		    {
		      LW6SYS_FREE (*file);
		      (*file) = tmp;
		    }
		  else
		    {
		      LW6SYS_FREE (tmp);
		      parent3 = lw6sys_path_parent (parent2);
		      if (parent3)
			{
			  tmp = lw6sys_path_concat (parent3, sub);
			  if (lw6sys_file_exists (tmp))
			    {
			      LW6SYS_FREE (*file);
			      (*file) = tmp;
			    }
			  else
			    {
			      LW6SYS_FREE (tmp);
			    }
			  LW6SYS_FREE (parent3);
			}
		    }
		  LW6SYS_FREE (parent2);
		}
	    }
	  LW6SYS_FREE (parent1);
	}
      if (!lw6sys_file_exists (*file))
	{
	  tmp = lw6sys_path_concat (lw6sys_build_get_package_id (), sub);
	  if (tmp)
	    {
	      if (lw6sys_file_exists (tmp))
		{
		  LW6SYS_FREE (*file);
		  (*file) = tmp;
		}
	      else
		{
		  LW6SYS_FREE (tmp);
		}
	    }
	  tmp = lw6sys_path_concat (lw6sys_build_get_package_string (), sub);
	  if (tmp)
	    {
	      if (lw6sys_file_exists (tmp))
		{
		  LW6SYS_FREE (*file);
		  (*file) = tmp;
		}
	      else
		{
		  LW6SYS_FREE (tmp);
		}
	    }
	  tmp = lw6sys_path_concat (lw6sys_build_get_package_tarname (), sub);
	  if (tmp)
	    {
	      if (lw6sys_file_exists (tmp))
		{
		  LW6SYS_FREE (*file);
		  (*file) = tmp;
		}
	      else
		{
		  LW6SYS_FREE (tmp);
		}
	    }
	  tmp = lw6sys_path_concat (lw6sys_build_get_package_name (), sub);
	  if (tmp)
	    {
	      if (lw6sys_file_exists (tmp))
		{
		  LW6SYS_FREE (*file);
		  (*file) = tmp;
		}
	      else
		{
		  LW6SYS_FREE (tmp);
		}
	    }
	}
    }
}

static char *
get_file (char *mask1, char *prefix1, char *mask2, char *prefix2, char *sub)
{
  char *file = NULL;

  file = get_file_common (mask1, prefix1, mask2, prefix2, sub);

  if (file == NULL)
    {
      // if not installed, if no source, then search in local directory
      file = lw6sys_path_concat (".", sub);
    }

  file_if_not_found (&file, sub);

  return file;
}

static char *
get_file_argc_argv (int argc, const char *argv[], char *mask1, char *prefix1,
		    char *mask2, char *prefix2, char *sub)
{
  char *file = NULL;
  char *run_dir = NULL;
  char *run_dir_rel = NULL;

  file = get_file_common (mask1, prefix1, mask2, prefix2, sub);

  if (file == NULL && strlen (sub) > 0)
    {
      run_dir = lw6sys_get_run_dir (argc, argv);
      if (run_dir)
	{
	  file = lw6sys_path_concat (run_dir, sub);
	  if (file)
	    {
	      if (!lw6sys_file_exists (file))
		{
		  LW6SYS_FREE (file);
		  file = NULL;
		  // file doesn't exist, we ignore it

		  if (RUN_REL && strlen (RUN_REL))
		    {
		      run_dir_rel = lw6sys_path_concat (run_dir, RUN_REL);
		      if (run_dir_rel)
			{
			  if (lw6sys_dir_exists (run_dir_rel))
			    {
			      file = lw6sys_path_concat (run_dir_rel, sub);
			      if (file)
				{
				  if (!lw6sys_file_exists (file))
				    {
				      LW6SYS_FREE (file);
				      file = NULL;
				      // file doesn't exist, we ignore it
				    }
				}
			    }
			  LW6SYS_FREE (run_dir_rel);
			}
		    }
		}
	    }
	  LW6SYS_FREE (run_dir);
	}
    }

  if (file == NULL)
    {
      // if not installed, if no source, then search in local directory
      file = lw6sys_path_concat (".", sub);
    }

  file_if_not_found (&file, sub);

  return file;
}

static char *
get_mod_dir_with_prefix (char *prefix)
{
  char *mod_dir = NULL;
  char *libdir = NULL;

  libdir = lw6sys_build_get_libdir ();
  mod_dir = get_dir (MOD_PREFIX_MASK, prefix, MOD_LIBDIR_MASK, libdir, "", 0);

  return mod_dir;
}

static char *
get_mod_dir_with_prefix_argc_argc (int argc, const char *argv[], char *prefix)
{
  char *mod_dir = NULL;
  char *libdir = NULL;

  libdir = lw6sys_build_get_libdir ();
  mod_dir =
    get_dir_argc_argv (argc, argv, MOD_PREFIX_MASK, prefix, MOD_LIBDIR_MASK,
		       libdir, "", 0);

  return mod_dir;
}

/**
 * lw6sys_get_default_mod_dir
 *
 * Returns the default module directory (dynamically loaded libraries).
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_mod_dir ()
{
  char *mod_dir = NULL;
  char *prefix = NULL;

  prefix = lw6sys_get_default_prefix ();
  if (prefix)
    {
      mod_dir = get_mod_dir_with_prefix (prefix);
      LW6SYS_FREE (prefix);
    }

  return mod_dir;
}

static char *
get_share_dir_with_prefix (char *prefix, char *sub, int check_readme)
{
  char *share_dir = NULL;
  char *datadir = NULL;

  datadir = lw6sys_build_get_datadir ();
  share_dir =
    get_dir (SHARE_PREFIX_MASK, prefix, SHARE_DATADIR_MASK, datadir, sub,
	     check_readme);

  return share_dir;
}

static char *
get_share_dir_with_prefix_argc_argv (int argc, const char *argv[],
				     char *prefix, char *sub,
				     int check_readme)
{
  char *share_dir = NULL;
  char *datadir = NULL;

  datadir = lw6sys_build_get_datadir ();
  share_dir =
    get_dir_argc_argv (argc, argv, SHARE_PREFIX_MASK, prefix,
		       SHARE_DATADIR_MASK, datadir, sub, check_readme);

  return share_dir;
}

/**
 * lw6sys_get_default_data_dir
 *
 * Returns the default data directory.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_data_dir ()
{
  char *data_dir = NULL;
  char *prefix = NULL;

  prefix = lw6sys_get_default_prefix ();
  if (prefix)
    {
      data_dir = get_share_dir_with_prefix (prefix, DATA_DIR, 1);
      LW6SYS_FREE (prefix);
    }

  return data_dir;
}

static char *
get_path_with_dir_and_user_dir (char *dir, char *user_dir, char *sub,
				int create_dir, char *readme_comment)
{
  char *path = NULL;
  char *user_sub_dir = NULL;
  char *user_sub_dir_readme = NULL;
  char *readme_content = NULL;

  user_sub_dir = lw6sys_path_concat (user_dir, sub);
  if (user_sub_dir)
    {
      if (create_dir)
	{
	  if (!lw6sys_dir_exists (user_sub_dir))
	    {
	      lw6sys_create_dir (user_sub_dir);
	    }
	  user_sub_dir_readme =
	    lw6sys_path_concat (user_sub_dir, README_FILE);
	  if (user_sub_dir_readme)
	    {
	      if (readme_comment)
		{
		  readme_content =
		    lw6sys_str_reformat (readme_comment,
					 LW6SYS_REFORMAT_DEFAULT_PREFIX,
					 LW6SYS_REFORMAT_DEFAULT_NB_COLUMNS);
		  if (readme_content)
		    {
		      lw6sys_write_file_content (user_sub_dir_readme,
						 readme_content);
		      LW6SYS_FREE (readme_content);
		    }
		}
	      LW6SYS_FREE (user_sub_dir_readme);
	    }
	}
      path = lw6sys_env_concat (user_sub_dir, dir);
      LW6SYS_FREE (user_sub_dir);
    }

  return path;
}

/**
 * lw6sys_get_default_music_dir
 *
 * Returns the default music directory.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_music_dir ()
{
  char *music_dir = NULL;
  char *prefix = NULL;

  prefix = lw6sys_get_default_prefix ();
  if (prefix)
    {
      music_dir = get_share_dir_with_prefix (prefix, MUSIC_DIR, 1);
      LW6SYS_FREE (prefix);
    }

  return music_dir;
}

/**
 * lw6sys_get_default_music_path
 *
 * Returns the default music path, which can be composed of several directories.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_music_path ()
{
  char *music_path = NULL;
  char *music_dir = NULL;
  char *user_dir = NULL;

  music_dir = lw6sys_get_default_music_dir ();
  if (music_dir)
    {
      user_dir = lw6sys_get_default_user_dir ();
      if (user_dir)
	{
	  music_path =
	    get_path_with_dir_and_user_dir (music_dir, user_dir, MUSIC_DIR, 0,
					    NULL);
	  LW6SYS_FREE (user_dir);
	}
      LW6SYS_FREE (music_dir);
    }

  return music_path;
}

/**
 * lw6sys_get_default_map_dir
 *
 * Returns the default map directory.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_map_dir ()
{
  char *map_dir = NULL;
  char *prefix = NULL;

  prefix = lw6sys_get_default_prefix ();
  if (prefix)
    {
      map_dir = get_share_dir_with_prefix (prefix, MAP_DIR, 1);
      LW6SYS_FREE (prefix);
    }

  return map_dir;
}

/**
 * lw6sys_get_default_map_path
 *
 * Returns the default map path, which can be composed of several directories.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_map_path ()
{
  char *map_path = NULL;
  char *map_dir = NULL;
  char *user_dir = NULL;

  map_dir = lw6sys_get_default_map_dir ();
  if (map_dir)
    {
      user_dir = lw6sys_get_default_user_dir ();
      if (user_dir)
	{
	  map_path =
	    get_path_with_dir_and_user_dir (map_dir, user_dir, MAP_DIR, 0,
					    NULL);
	  LW6SYS_FREE (user_dir);
	}
      LW6SYS_FREE (map_dir);
    }

  return map_path;
}

static char *
get_share_file_with_prefix (char *prefix, char *sub)
{
  char *share_file = NULL;
  char *datadir;

  datadir = lw6sys_build_get_datadir ();
  share_file =
    get_file (SHARE_PREFIX_MASK, prefix, SHARE_DATADIR_MASK, datadir, sub);

  return share_file;
}

static char *
get_share_file_with_prefix_argc_argv (int argc, const char *argv[],
				      char *prefix, char *sub)
{
  char *share_file = NULL;
  char *datadir;

  datadir = lw6sys_build_get_datadir ();
  share_file =
    get_file_argc_argv (argc, argv, SHARE_PREFIX_MASK, prefix,
			SHARE_DATADIR_MASK, datadir, sub);

  return share_file;
}

/**
 * lw6sys_get_default_script_file
 *
 * Returns the default script file.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_default_script_file ()
{
  char *script_file = NULL;
  char *prefix = NULL;

  prefix = lw6sys_get_default_prefix ();
  if (prefix)
    {
      script_file = get_share_file_with_prefix (prefix, SCRIPT_FILE);
      LW6SYS_FREE (prefix);
    }

  return script_file;
}

/**
 * lw6sys_options_log_defaults
 *
 * Logs all default values to log file. Usefull for debugging, to
 * know where the program is searching for its informations.
 */
void
lw6sys_options_log_defaults ()
{
  char *path = NULL;

  path = lw6sys_get_default_user_dir ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default user dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_config_file ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default config file is \"%s\""),
		  path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_log_file ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default log file is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_prefix ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default prefix is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_mod_dir ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default mod dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_data_dir ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default data dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_music_dir ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default music dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_music_path ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default music path is \"%s\""),
		  path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_map_dir ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default map dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_map_path ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default map path is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_default_script_file ();
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("default script file is \"%s\""),
		  path);
      LW6SYS_FREE (path);
    }
}

static void *
get_command_arg_with_env (int argc, const char *argv[], char *keyword)
{
  char *arg_value = NULL;
  char *ret = NULL;

  arg_value = lw6sys_arg_get_value_with_env (argc, argv, keyword);
  if (arg_value)
    {
      ret = lw6sys_path_strip_slash (arg_value);
      LW6SYS_FREE (arg_value);
    }

  return ret;
}

/**
 * lw6sys_get_cwd
 *
 * Returns the current working directory (absolute path).
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_cwd ()
{
  char *cwd = NULL;
  char *cwd_tmp = NULL;

  cwd_tmp = (char *) LW6SYS_CALLOC (CWD_SIZE + 1);

  if (cwd_tmp)
    {
#ifdef LW6_MS_WINDOWS
      if (!GetCurrentDirectoryA (CWD_SIZE, cwd_tmp))
#else
      if (!getcwd (cwd_tmp, CWD_SIZE))
#endif
	{
	  LW6SYS_FREE (cwd_tmp);
	  cwd_tmp = NULL;
	}
    }

  if (cwd_tmp)
    {
      cwd = lw6sys_path_strip_slash (cwd_tmp);
      LW6SYS_FREE (cwd_tmp);
    }
  else
    {
      cwd = lw6sys_str_copy (".");
    }

  return cwd;
}

/**
 * lw6sys_get_run_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the binary directory, that is, the directory the binary
 * is stored in. This is calculated dynamically, by interpreting
 * command-line arguments.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_run_dir (int argc, const char *argv[])
{
  char *run_dir = NULL;

  if (argc >= 1)
    {
      run_dir = lw6sys_path_parent (argv[0]);
    }
  else
    {
      run_dir = lw6sys_str_copy (".");
    }

  return run_dir;
}

/**
 * lw6sys_get_user_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the user dir, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_user_dir (int argc, const char *argv[])
{
  char *user_dir = NULL;

  user_dir = get_command_arg_with_env (argc, argv, LW6DEF_USER_DIR);
  if (user_dir == NULL)
    {
      user_dir = lw6sys_get_default_user_dir ();
    }

  if (user_dir)
    {
      if (!lw6sys_dir_exists (user_dir))
	{
	  lw6sys_create_dir_silent (user_dir);
	  if (!lw6sys_dir_exists (user_dir))
	    {
	      lw6sys_log_critical (_x_ ("can't open user dir \"%s\""),
				   user_dir);
	    }
	}
    }

  return user_dir;
}

/**
 * lw6sys_get_config_file
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the config file, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_config_file (int argc, const char *argv[])
{
  char *config_file = NULL;
  char *user_dir = NULL;

  config_file = get_command_arg_with_env (argc, argv, LW6DEF_CONFIG_FILE);
  if (config_file == NULL)
    {
      user_dir = lw6sys_get_user_dir (argc, argv);
      if (user_dir)
	{
	  config_file = get_config_file_with_user_dir (user_dir);
	  LW6SYS_FREE (user_dir);
	}
    }

  return config_file;
}

/**
 * lw6sys_get_log_file
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the log file, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_log_file (int argc, const char *argv[])
{
  char *log_file = NULL;
  char *user_dir = NULL;

  log_file = get_command_arg_with_env (argc, argv, LW6DEF_LOG_FILE);
  if (log_file == NULL)
    {
      user_dir = lw6sys_get_user_dir (argc, argv);
      if (user_dir)
	{
	  log_file = get_log_file_with_user_dir (user_dir);
	  LW6SYS_FREE (user_dir);
	}
    }

  return log_file;
}

/**
 * lw6sys_get_prefix
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the prefix, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_prefix (int argc, const char *argv[])
{
  char *prefix = NULL;

  prefix = get_command_arg_with_env (argc, argv, LW6DEF_PREFIX);
  if (prefix == NULL)
    {
      prefix = lw6sys_get_default_prefix ();
    }

  return prefix;
}

/**
 * lw6sys_get_mod_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the mod dir (modules, shared .so), 
 * taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_mod_dir (int argc, const char *argv[])
{
  char *mod_dir = NULL;
  char *prefix = NULL;

  mod_dir = get_command_arg_with_env (argc, argv, LW6DEF_MOD_DIR);
  if (mod_dir == NULL)
    {
      prefix = lw6sys_get_prefix (argc, argv);
      if (prefix)
	{
	  mod_dir = get_mod_dir_with_prefix_argc_argc (argc, argv, prefix);
	  LW6SYS_FREE (prefix);
	}
    }

  return mod_dir;
}

/**
 * lw6sys_get_data_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the data dir, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_data_dir (int argc, const char *argv[])
{
  char *data_dir = NULL;
  char *prefix = NULL;

  data_dir = get_command_arg_with_env (argc, argv, LW6DEF_DATA_DIR);
  if (data_dir == NULL)
    {
      prefix = lw6sys_get_prefix (argc, argv);
      if (prefix)
	{
	  data_dir =
	    get_share_dir_with_prefix_argc_argv (argc, argv, prefix,
						 DATA_DIR, 1);
	  LW6SYS_FREE (prefix);
	}
    }

  return data_dir;
}

/**
 * lw6sys_get_music_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the music dir, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_music_dir (int argc, const char *argv[])
{
  char *music_dir = NULL;
  char *prefix = NULL;

  music_dir = get_command_arg_with_env (argc, argv, LW6DEF_MUSIC_DIR);
  if (music_dir == NULL)
    {
      prefix = lw6sys_get_prefix (argc, argv);
      if (prefix)
	{
	  music_dir =
	    get_share_dir_with_prefix_argc_argv (argc, argv, prefix,
						 MUSIC_DIR, 1);
	  LW6SYS_FREE (prefix);
	}
    }

  return music_dir;
}

/**
 * lw6sys_get_music_path
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the music path, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result. Music path can contain several directories.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_music_path (int argc, const char *argv[])
{
  char *music_path = NULL;
  char *music_path_cmd = NULL;
  char *music_path_env = NULL;
  char *music_dir = NULL;
  char *user_dir = NULL;
  char *tmp = NULL;

  music_dir = lw6sys_get_music_dir (argc, argv);
  if (music_dir)
    {
      user_dir = lw6sys_get_user_dir (argc, argv);
      if (user_dir)
	{
	  music_path =
	    get_path_with_dir_and_user_dir (music_dir, user_dir, MUSIC_DIR, 1,
					    _x_
					    ("This is your Liquid War 6 user music directory. You can put your own musics here, they will be automatically loaded by the game, and played."));
	  if (music_path)
	    {
	      music_path_env = lw6sys_getenv_prefixed (LW6DEF_MUSIC_PATH);
	      if (music_path && music_path_env)
		{
		  tmp = music_path;
		  music_path = lw6sys_env_concat (music_path_env, music_path);
		  LW6SYS_FREE (tmp);
		  LW6SYS_FREE (music_path_env);
		}
	      music_path_cmd =
		lw6sys_arg_get_value (argc, argv, LW6DEF_MUSIC_PATH);
	      if (music_path && music_path_cmd)
		{
		  tmp = music_path;
		  music_path = lw6sys_env_concat (music_path_cmd, music_path);
		  LW6SYS_FREE (tmp);
		  LW6SYS_FREE (music_path_cmd);
		}
	    }
	  LW6SYS_FREE (user_dir);
	}
      LW6SYS_FREE (music_dir);
    }

  return music_path;
}

/**
 * lw6sys_get_map_dir
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the map dir, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_map_dir (int argc, const char *argv[])
{
  char *map_dir = NULL;
  char *prefix = NULL;

  map_dir = get_command_arg_with_env (argc, argv, LW6DEF_MAP_DIR);
  if (map_dir == NULL)
    {
      prefix = lw6sys_get_prefix (argc, argv);
      if (prefix)
	{
	  map_dir =
	    get_share_dir_with_prefix_argc_argv (argc, argv, prefix, MAP_DIR,
						 1);
	  LW6SYS_FREE (prefix);
	}
    }

  return map_dir;
}

/**
 * lw6sys_get_map_path
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the map path, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result. Map path can contain several directories.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_map_path (int argc, const char *argv[])
{
  char *map_path = NULL;
  char *map_path_cmd = NULL;
  char *map_path_env = NULL;
  char *map_dir = NULL;
  char *user_dir = NULL;
  char *tmp = NULL;

  map_dir = lw6sys_get_map_dir (argc, argv);
  if (map_dir)
    {
      user_dir = lw6sys_get_user_dir (argc, argv);
      if (user_dir)
	{
	  map_path =
	    get_path_with_dir_and_user_dir (map_dir, user_dir, MAP_DIR, 1,
					    _x_
					    ("This is your Liquid War 6 user map directory. You can put your own maps here, they will be automatically loaded by the game, and appear in the menus. To create maps, you need to 1) read the documentation 2) study existing map to see how things work in practice and 3) be creative. FYI the Liquid War 6 map format is rather simple and hopefully well documented, the general idea is that a map is a directory containing files, the most important of them being 'map.png'. Again, read the documentation. I repeat: 'Read the docs!'. http://www.gnu.org/software/liquidwar6/manual/"));
	  if (map_path)
	    {
	      map_path_env = lw6sys_getenv_prefixed (LW6DEF_MAP_PATH);
	      if (map_path && map_path_env)
		{
		  tmp = map_path;
		  map_path = lw6sys_env_concat (map_path_env, map_path);
		  LW6SYS_FREE (tmp);
		  LW6SYS_FREE (map_path_env);
		}
	      map_path_cmd =
		lw6sys_arg_get_value (argc, argv, LW6DEF_MAP_PATH);
	      if (map_path && map_path_cmd)
		{
		  tmp = map_path;
		  map_path = lw6sys_env_concat (map_path_cmd, map_path);
		  LW6SYS_FREE (tmp);
		  LW6SYS_FREE (map_path_cmd);
		}
	    }
	  LW6SYS_FREE (user_dir);
	}
      LW6SYS_FREE (map_dir);
    }

  return map_path;
}

/**
 * lw6sys_get_script_file
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Returns the script file, taking in account command-line and
 * environment variables. However config file content has no impact
 * on the result.
 *
 * Return value: a newly allocated string.
 */
char *
lw6sys_get_script_file (int argc, const char *argv[])
{
  char *script_file = NULL;
  char *prefix = NULL;

  script_file = get_command_arg_with_env (argc, argv, LW6DEF_SCRIPT_FILE);
  if (script_file == NULL)
    {
      prefix = lw6sys_get_prefix (argc, argv);
      if (prefix)
	{
	  script_file =
	    get_share_file_with_prefix_argc_argv (argc, argv, prefix,
						  SCRIPT_FILE);
	  LW6SYS_FREE (prefix);
	}
    }

  return script_file;
}

/**
 * lw6sys_options_log
 *
 * @argc: argc, number of arguments, as given to @main
 * @argv: argv, pointer to arguments, as given to @main
 *
 * Logs all the main options values which are not config-file
 * dependant but depend on built-in defaults, command-line arguments
 * and environment variables. Usefull to debug and know where the
 * program is searching for things.
 */
void
lw6sys_options_log (int argc, const char *argv[])
{
  char *path = NULL;

  path = lw6sys_get_cwd (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("cwd is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_run_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("run dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_user_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("user dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_config_file (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("config file is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_log_file (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("log file is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_prefix (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("prefix is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_mod_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("mod dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_data_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("data dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_music_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("music dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_music_path (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("music path is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_map_dir (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("map dir is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_map_path (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("map path is \"%s\""), path);
      LW6SYS_FREE (path);
    }
  path = lw6sys_get_script_file (argc, argv);
  if (path)
    {
      lw6sys_log (LW6SYS_LOG_INFO, _x_ ("script file is \"%s\""), path);
      LW6SYS_FREE (path);
    }
}
