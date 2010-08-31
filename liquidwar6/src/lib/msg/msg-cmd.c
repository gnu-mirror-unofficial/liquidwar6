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

char *
_generate_info (char *cmd, lw6nod_info_t * info)
{
  char *ret = NULL;
  char sep = LW6MSG_TELNET_SEP;
  char *base64_codename;
  char *base64_url;
  char *base64_title;
  char *base64_description;
  int uptime = 0;

  base64_codename = lw6glb_base64_encode_str (info->const_info.codename);
  if (base64_codename)
    {
      base64_url = lw6glb_base64_encode_str (info->const_info.url);
      if (base64_url)
	{
	  base64_title = lw6glb_base64_encode_str (info->const_info.title);
	  if (base64_title)
	    {
	      base64_description =
		lw6glb_base64_encode_str (info->const_info.description);
	      if (base64_description)
		{
		  uptime =
		    (lw6sys_get_timestamp () -
		     info->const_info.creation_timestamp) / 1000;
		  ret =
		    lw6sys_new_sprintf
		    ("%s%c%s%c%s%c%s%c%d%c%s%c%s%c%s%c%s%c%d%c%d", cmd, sep,
		     info->const_info.program, sep,
		     info->const_info.version, sep, base64_codename, sep,
		     info->const_info.stamp, sep, info->const_info.id,
		     sep, base64_url, sep, base64_title, sep,
		     base64_description, sep, info->const_info.bench, sep,
		     uptime);
		  LW6SYS_FREE (base64_description);
		}
	      LW6SYS_FREE (base64_title);
	    }
	  LW6SYS_FREE (base64_url);
	}
      LW6SYS_FREE (base64_codename);
    }

  return ret;
}

/**
 * lw6msg_cmd_generate_hello
 *
 * @info: the node info to use
 *
 * Generate a HELLO command.
 *
 * Return value: newly allocated string.
 */
char *
lw6msg_cmd_generate_hello (lw6nod_info_t * info)
{
  char *ret = NULL;

  ret = _generate_info (LW6MSG_CMD_HELLO, info);

  return ret;
}

/**
 * lw6msg_cmd_generate_ticket
 *
 * @info: the node info to use
 * @ticket: the ticket to send
 *
 * Generate a TICKET command.
 *
 * Return value: newly allocated string.
 */
char *
lw6msg_cmd_generate_ticket (lw6nod_info_t * info, u_int32_t ticket)
{
  char *ret = NULL;
  char sep = LW6MSG_TELNET_SEP;
  char *info_str = NULL;

  info_str = _generate_info (LW6MSG_CMD_TICKET, info);
  if (info_str)
    {
      ret = lw6sys_new_sprintf ("%s%c%08x", info_str, sep, ticket);
      LW6SYS_FREE (info_str);
    }

  return ret;
}

/**
 * lw6msg_cmd_generate_foo
 *
 * @info: the node info to use
 * @key: the key to identify the message
 *
 * Generate a FOO command.
 *
 * Return value: newly allocated string.
 */
char *
lw6msg_cmd_generate_foo (lw6nod_info_t * info, u_int32_t key)
{
  char *ret = NULL;
  char sep = LW6MSG_TELNET_SEP;
  char *info_str = NULL;

  info_str = _generate_info (LW6MSG_CMD_FOO, info);
  if (info_str)
    {
      ret = lw6sys_new_sprintf ("%s%c%08x", info_str, sep, key);
      LW6SYS_FREE (info_str);
    }

  return ret;
}

/**
 * lw6msg_cmd_generate_bar
 *
 * @info: the node info to use
 * @key: the key to identify the message
 *
 * Generate a BAR command.
 *
 * Return value: newly allocated string.
 */
char *
lw6msg_cmd_generate_bar (lw6nod_info_t * info, u_int32_t key)
{
  char *ret = NULL;
  char sep = LW6MSG_TELNET_SEP;
  char *info_str = NULL;

  info_str = _generate_info (LW6MSG_CMD_BAR, info);
  if (info_str)
    {
      ret = lw6sys_new_sprintf ("%s%c%08x", info_str, sep, key);
      LW6SYS_FREE (info_str);
    }

  return ret;
}

/**
 * lw6msg_cmd_generate_goodbye
 *
 * @info: the node info to use
 *
 * Generate a GOODBYE command.
 *
 * Return value: newly allocated string.
 */
char *
lw6msg_cmd_generate_goodbye (lw6nod_info_t * info)
{
  char *ret = NULL;

  ret = _generate_info (LW6MSG_CMD_GOODBYE, info);

  return ret;
}

static int
_analyse_info (lw6nod_info_t ** info, char **next, char *msg)
{
  int ret = 0;
  char *pos = NULL;
  char *seek = NULL;
  lw6msg_word_t program;
  lw6msg_word_t version;
  lw6msg_word_t codename;
  int stamp = 0;
  u_int64_t id = 0;
  lw6msg_word_t url;
  lw6msg_word_t title;
  lw6msg_word_t description;
  int bench = 0;
  int uptime = 0;

  (*info) = NULL;
  if (next)
    {
      (*next) = NULL;
    }

  pos = msg;
  lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing program \"%s\""), pos);
  if (lw6msg_word_first (&program, &seek, pos))
    {
      pos = seek;
      lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing version \"%s\""), pos);
      if (lw6msg_word_first (&version, &seek, pos))
	{
	  pos = seek;
	  lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing codename \"%s\""), pos);
	  if (lw6msg_word_first_base64 (&codename, &seek, pos))
	    {
	      pos = seek;
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing stamp \"%s\""), pos);
	      if (lw6msg_word_first_int_gt0 (&stamp, &seek, pos))
		{
		  pos = seek;
		  lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing id \"%s\""),
			      pos);
		  if (lw6msg_word_first_id_64 (&id, &seek, pos))
		    {
		      pos = seek;
		      lw6sys_log (LW6SYS_LOG_DEBUG, _("analyzing url \"%s\""),
				  pos);
		      if (lw6msg_word_first_base64 (&url, &seek, pos)
			  && lw6sys_url_is_canonized (url.buf))
			{
			  pos = seek;
			  lw6sys_log (LW6SYS_LOG_DEBUG,
				      _("analyzing title \"%s\""), pos);
			  if (lw6msg_word_first_base64 (&title, &seek, pos))
			    {
			      pos = seek;
			      lw6sys_log (LW6SYS_LOG_DEBUG,
					  _("analyzing description \"%s\""),
					  pos);
			      if (lw6msg_word_first_base64
				  (&description, &seek, pos))
				{
				  pos = seek;
				  lw6sys_log (LW6SYS_LOG_DEBUG,
					      _("analyzing bench \"%s\""),
					      pos);
				  if (lw6msg_word_first_int
				      (&bench, &seek, pos))
				    {
				      pos = seek;
				      lw6sys_log (LW6SYS_LOG_DEBUG,
						  _
						  ("analyzing uptime \"%s\""),
						  pos);
				      if (lw6msg_word_first_int
					  (&uptime, &seek, pos))
					{
					  pos = seek;
					  (*info) =
					    lw6nod_info_new (program.buf,
							     version.buf,
							     codename.buf,
							     stamp, id,
							     url.buf,
							     title.buf,
							     description.buf,
							     bench,
							     uptime, NULL, 0,
							     NULL);
					  if (*info)
					    {
					      if (next)
						{
						  (*next) = pos;
						}
					      ret = 1;
					    }
					  else
					    {
					      lw6sys_log (LW6SYS_LOG_WARNING,
							  _
							  ("unable to create nod info"));
					    }
					}
				      else
					{
					  lw6sys_log (LW6SYS_LOG_DEBUG,
						      _("bad uptime \"%s\""),
						      pos);
					}
				    }
				  else
				    {
				      lw6sys_log (LW6SYS_LOG_DEBUG,
						  _("bad bench \"%s\""), pos);
				    }
				}
			      else
				{
				  lw6sys_log (LW6SYS_LOG_DEBUG,
					      _("bad description \"%s\""),
					      pos);
				}
			    }
			  else
			    {
			      lw6sys_log (LW6SYS_LOG_DEBUG,
					  _("bad title \"%s\""), pos);
			    }
			}
		      else
			{
			  lw6sys_log (LW6SYS_LOG_DEBUG, _("bad url \"%s\""),
				      pos);
			}
		    }
		  else
		    {
		      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad id \"%s\""), pos);
		    }
		}
	      else
		{
		  lw6sys_log (LW6SYS_LOG_DEBUG, _("bad stamp \"%s\""), pos);
		}
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad codename \"%s\""), pos);
	    }
	}
      else
	{
	  lw6sys_log (LW6SYS_LOG_DEBUG, _("bad version \"%s\""), pos);
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad program \"%s\""), pos);
    }

  return ret;
}

/**
 * lw6msg_cmd_analyse_hello
 *
 * @info: if not NULL, will contain (remote) node info on success
 * @msg: the message to anaylse
 *
 * Analyzes a HELLO message.
 *
 * Return value: 1 on success, 0 on failure
 */
int
lw6msg_cmd_analyse_hello (lw6nod_info_t ** info, char *msg)
{
  int ret = 0;

  if (lw6sys_str_starts_with_no_case (msg, LW6MSG_CMD_HELLO))
    {
      if (_analyse_info (info, NULL, msg + strlen (LW6MSG_CMD_HELLO)))
	{
	  ret = 1;
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _("parsing HELLO but couldn't find it in \"%s\""), msg);
    }

  return ret;
}

/**
 * lw6msg_cmd_analyse_ticket
 *
 * @info: if not NULL, will contain (remote) node info on success
 * @ticket: if not NULL, will contain the ticket value on success
 * @msg: the message to anaylse
 *
 * Analyzes a TICKET message.
 *
 * Return value: 1 on success, 0 on failure
 */
int
lw6msg_cmd_analyse_ticket (lw6nod_info_t ** info, u_int32_t * ticket,
			   char *msg)
{
  int ret = 0;
  char *pos = NULL;
  char *seek = NULL;

  if (lw6sys_str_starts_with_no_case (msg, LW6MSG_CMD_TICKET))
    {
      pos = msg + strlen (LW6MSG_CMD_TICKET);
      if (_analyse_info (info, &seek, pos))
	{
	  pos = seek;
	  if (lw6msg_word_first_id_32 (ticket, &seek, pos))
	    {
	      ret = 1;
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad ticket \"%s\""), pos);
	    }
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _("parsing TICKET but couldn't find it in \"%s\""), msg);
    }

  return ret;
}


/**
 * lw6msg_cmd_analyse_foo
 *
 * @info: if not NULL, will contain (remote) node info on success
 * @key: if not NULL, will contain the foo/bar key on success
 * @msg: the message to anaylse
 *
 * Analyzes a FOO message.
 *
 * Return value: 1 on success, 0 on failure
 */
int
lw6msg_cmd_analyse_foo (lw6nod_info_t ** info, u_int32_t * key, char *msg)
{
  int ret = 0;
  char *pos = NULL;
  char *seek = NULL;

  if (lw6sys_str_starts_with_no_case (msg, LW6MSG_CMD_FOO))
    {
      pos = msg + strlen (LW6MSG_CMD_FOO);
      if (_analyse_info (info, &seek, pos))
	{
	  pos = seek;
	  if (lw6msg_word_first_id_32 (key, &seek, pos))
	    {
	      ret = 1;
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad key \"%s\""), pos);
	    }
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _("parsing FOO but couldn't find it in \"%s\""), msg);
    }

  return ret;
}

/**
 * lw6msg_cmd_analyse_bar
 *
 * @info: if not NULL, will contain (remote) node info on success
 * @key: if not NULL, will contain the foo/bar key on success
 * @msg: the message to anaylse
 *
 * Analyzes a BAR message.
 *
 * Return value: 1 on success, 0 on failure
 */
int
lw6msg_cmd_analyse_bar (lw6nod_info_t ** info, u_int32_t * key, char *msg)
{
  int ret = 0;
  char *pos = NULL;
  char *seek = NULL;

  if (lw6sys_str_starts_with_no_case (msg, LW6MSG_CMD_BAR))
    {
      pos = msg + strlen (LW6MSG_CMD_BAR);
      if (_analyse_info (info, &seek, pos))
	{
	  pos = seek;
	  if (lw6msg_word_first_id_32 (key, &seek, pos))
	    {
	      ret = 1;
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("bad key \"%s\""), pos);
	    }
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _("parsing BAR but couldn't find it in \"%s\""), msg);
    }

  return ret;
}

/**
 * lw6msg_cmd_analyse_goodbye
 *
 * @info: if not NULL, will contain (remote) node info on success
 * @msg: the message to anaylse
 *
 * Analyzes a GOODBYE message.
 *
 * Return value: 1 on success, 0 on failure
 */
int
lw6msg_cmd_analyse_goodbye (lw6nod_info_t ** info, char *msg)
{
  int ret = 0;

  if (lw6sys_str_starts_with_no_case (msg, LW6MSG_CMD_GOODBYE))
    {
      if (_analyse_info (info, NULL, msg + strlen (LW6MSG_CMD_GOODBYE)))
	{
	  ret = 1;
	}
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_DEBUG,
		  _("parsing GOODBYE but couldn't find it in \"%s\""), msg);
    }

  return ret;
}