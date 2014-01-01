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

#include "msg.h"

/**
 * lw6msg_sort_str_by_seq_callback
 * 
 * @list_a: pointer to a list of int item
 * @list_b: pointer to a list of int item
 *
 * Sort callback for a list containing strings which begin by a seq number,
 * will sort with lower seq number first.
 *
 * Return value: -1 if @list_a < @list_b , 0 if @list_a == @list_b, 
 *   1 if @list_a > @list_b
 */
int
lw6msg_sort_str_by_seq_callback (lw6sys_list_t ** list_a,
				 lw6sys_list_t ** list_b)
{
  int ret = 0;
  char *str_a = NULL, *str_b = NULL;
  int64_t seq_a = 00L, seq_b = 00L;
  int parse_error = 0;
  char *next_a = NULL, *next_b = NULL;

  str_a = (char *) ((*list_a)->data);
  str_b = (char *) ((*list_b)->data);

  if (!(str_a && lw6msg_word_first_int_64 (&seq_a, &next_a, str_a)))
    {
      parse_error = 1;
      ret = -1;
    }
  if (!(str_b && lw6msg_word_first_int_64 (&seq_b, &next_b, str_b)))
    {
      parse_error = 1;
      /*
       * Special trick, if ret was -1 (a undef, so a<b) then return
       * 0, consider them equal as they are the same, else increment
       * anyway and put 1, b is undef so a>b
       */
      ret++;
    }
  if (!parse_error)
    {
      if (seq_a < seq_b)
	{
	  ret = -1;
	}
      else if (seq_a > seq_b)
	{
	  ret = +1;
	}
      else
	{
	  if (next_a && next_b)
	    {
	      /*
	       * If seqs are equal, use basic alpha sort on reminder
	       */
	      ret = strcmp (next_a, next_b);
	    }
	}
    }

  return ret;
}
