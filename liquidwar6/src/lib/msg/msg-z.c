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

#include "msg.h"

#include <zlib.h>

/*
 *  http://www.zlib.net/zlib_how.html
 */
static int
_encode_buffer_len (int in_len)
{
  int out_len = 0;
  /*
   * "the destination buffer, which must be at least 0.1% larger 
   * than sourceLen plus 12 bytes"
   *
   * By security, we use 1% and 24 bytes...
   */
  out_len = in_len + (in_len / 100) + 24;

  return out_len;
}

static int
_z_encode (char *out_buf, int *out_buf_len, char *msg, int msg_len)
{
  int ret = 0;
  uLongf _out_buf_len = (*out_buf_len);

  ret = compress ((Bytef *) out_buf, &_out_buf_len, (Bytef *) msg, msg_len);
  (*out_buf_len) = _out_buf_len;

  return ret;
}

/**
 * lw6msg_z_encode
 *
 * @msg: message to encode
 *
 * Z-encode a message, by "Z-encoding" we mean pass the string through
 * 1) zlib then 2) base64 encoding, this way we get a string without any
 * blank and/or special character, and of reasonnable length.
 *
 * Return value: newly allocated string, 0 terminated, NULL on error.
 */
char *
lw6msg_z_encode (char *msg)
{
  char *ret = NULL;
  int in_len = 0;
  int out_len = 0;
  int z_ret = Z_BUF_ERROR;
  char *out_buf;

  in_len = strlen (msg);
  out_len = _encode_buffer_len (in_len);
  out_buf = (char *) LW6SYS_MALLOC (out_len);
  if (out_buf)
    {
      z_ret = _z_encode (out_buf, &out_len, msg, in_len);
      if (z_ret == Z_OK)
	{
	  ret = lw6glb_base64_encode_bin (out_buf, out_len);
	}
      else
	{
	  switch (z_ret)
	    {
	    case Z_BUF_ERROR:
	      lw6sys_log (LW6SYS_LOG_WARNING,
			  _
			  ("zlib error, buffer is too small (in_len=%d out_len=%d)"),
			  in_len, out_len);
	      break;
	    case Z_MEM_ERROR:
	      lw6sys_log (LW6SYS_LOG_WARNING,
			  _
			  ("zlib error, not enough memory (in_len=%d out_len=%d)"),
			  in_len, out_len);
	      break;
	    default:
	      lw6sys_log (LW6SYS_LOG_WARNING, _("zlib error, ret=%d"), z_ret);
	      break;
	    }
	}
      LW6SYS_FREE (out_buf);
    }

  return ret;
}

/**
 * lw6msg_z_decode
 *
 * @msg: message to decode
 *
 * Z-decode a message, by "Z-encoding" we mean pass the string through
 * 1) zlib then 2) base64 encoding, this way we get a string without any
 * blank and/or special character, and of reasonnable length. This decode
 * string does it the reverse way, un64-encode the string then uncompress
 * it back to a readable string.
 *
 * Return value: newly allocated string, 0 terminated, NULL on error.
 */
char *
lw6msg_z_decode (char *msg)
{
  char *ret = NULL;


  return ret;
}
