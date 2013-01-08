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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include "cfg.h"
#include "cfg-internal.h"

static int
must_be_stored (char *key)
{
  int ret = 1;

  /*
   * We exclude some keys, for which it doesn't make sense
   * to be stored:
   * - reset, because it's useless and brings confusion to store it
   * - map-path, because values in it should be added, not replaced
   */
  if ((!strcmp (key, LW6DEF_RESET)) || (!strcmp (key, LW6DEF_MAP_PATH)))
    {
      ret = 0;
    }

  return ret;
}

static int
parse_option (_lw6cfg_context_t * context, const char *option)
{
  int ret = 0;

  if (strlen (option) >= 3)
    {
      char *equal = NULL;
      char *key = NULL;
      char *value = NULL;
      char *value_converted = NULL;

      if (strncmp (option, "--", 2) == 0)
	{
	  key = lw6sys_str_copy (option + 2);
	}
      else if (strncmp (option, "-", 1) == 0)
	{
	  key = lw6sys_str_copy (option + 1);
	}
      else if (strncmp (option, "/", 1) == 0)
	{
	  key = lw6sys_str_copy (option + 1);
	}
      else
	{
	  key = lw6sys_str_copy (option);
	}

      if (key)
	{
	  equal = strchr (key, '=');

	  if (equal)
	    {
	      (*equal) = '\0';
	      value = equal + 1;
	    }
	  else
	    {
	      /*
	       * An option given without any argument is true by
	       * default that is "--option" and "--option=true"
	       * have the same meaning.
	       */
	      value = "true";
	    }

	  if (must_be_stored (key))
	    {
	      value_converted = lw6cfg_format_guess_type (key, value);
	      if (value_converted)
		{
		  lw6sys_log (LW6SYS_LOG_INFO,
			      _x_
			      ("key \"%s\" set to \"%s\" by command-line option \"%s\""),
			      key, value_converted, option);
		  if (lw6sys_spinlock_lock (context->spinlock))
		    {
		      lw6sys_hash_set (context->options, key,
				       value_converted);
		      // no need to free value_converted
		      lw6sys_spinlock_unlock (context->spinlock);
		    }
		}
	    }

	  LW6SYS_FREE (key);

	  ret = 1;
	}
    }

  return ret;
}

int
_lw6cfg_parse_command_line (_lw6cfg_context_t * context)
{
  int i;
  int ret = 1;

  for (i = 1; i < context->argc; ++i)
    {
      ret = ret && parse_option (context, context->argv[i]);
    }

  return ret;
}

/**
 * lw6cfg_parse_command_line
 *
 * @context: opaque pointer on a context
 *
 * Overwrites any existing option with command line args
 *
 * Return value: 1 if success, 0 if error
 */
int
lw6cfg_parse_command_line (void *context)
{
  return _lw6cfg_parse_command_line ((_lw6cfg_context_t *) context);
}
