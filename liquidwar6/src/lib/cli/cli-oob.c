/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010  Christian Mauduit <ufoot@ufoot.org>

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

#include "cli.h"

/**
 * lw6cli_oob_new
 *
 * @public_url: the address of the distant server to test
 *
 * Create a new OOB structure, copying required objects.
 * We need to make copies for this is for usage in a 
 * separate thread. The thread member is not set
 * here since the right way to do things is first to
 * set up data then to fire the thread.
 *
 * Return value: new object
 */
lw6cli_oob_t *
lw6cli_oob_new (char *public_url)
{
  lw6cli_oob_t *oob = NULL;

  oob = (lw6cli_oob_t *) LW6SYS_CALLOC (sizeof (lw6cli_oob_t));
  if (oob)
    {
      oob->data.creation_timestamp = lw6sys_get_timestamp ();
      oob->data.do_not_finish = 0;
      oob->data.public_url = lw6sys_str_copy (public_url);
    }

  if (oob)
    {
      if (!oob->data.public_url)
	{
	  lw6cli_oob_free (oob);
	  oob = NULL;
	}
    }

  return oob;
}

/**
 * lw6cli_oob_free
 *
 * @oob: the object to free
 *
 * Frees an OOB structure.
 *
 * Return value: none
 */
void
lw6cli_oob_free (lw6cli_oob_t * oob)
{
  if (oob)
    {
      if (oob->thread)
	{
	  /*
	   * Normally do_not_finish is already set,
	   * or it should, for it's better to set
	   * this flag on all objects then free
	   * them later.
	   */
	  oob->data.do_not_finish = 1;
	  lw6sys_thread_join (oob->thread);
	}

      if (oob->data.public_url)
	{
	  LW6SYS_FREE (oob->data.public_url);
	}
      LW6SYS_FREE (oob);
      lw6sys_log (LW6SYS_LOG_DEBUG, _("oob freed"));
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING, _("trying to free NULL oob"));
    }
}