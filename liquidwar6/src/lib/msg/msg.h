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

#ifndef LIQUIDWAR6MSG_H
#define LIQUIDWAR6MSG_H

#include "../sys/sys.h"
#include "../glb/glb.h"
#include "../nod/nod.h"

#define LW6MSG_OOB_INFO "INFO"
#define LW6MSG_OOB_LIST "LIST"
#define LW6MSG_OOB_PING "PING"
#define LW6MSG_OOB_PONG "PONG"

/* msg-oob.c */
extern char *lw6msg_oob_generate_info (lw6nod_info_t * info);
extern char *lw6msg_oob_generate_list (lw6nod_info_t * info);
extern char *lw6msg_oob_generate_pong (lw6nod_info_t * info);
extern int lw6msg_oob_analyse_info_line (lw6nod_info_t * info, char *line);
extern char *lw6msg_oob_analyse_pong (char *text);

/* nod-test.c */
extern int lw6msg_test (int mode);

/* msg-utils.c */
extern int lw6msg_utils_is_space (char c);

#endif
