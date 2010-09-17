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

#include "sys.h"
#include "sys-internal.h"

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#ifdef LW6_GTK
#include <gtk/gtk.h>
#endif

#define HISTORY_LENGTH 256
#define LEVEL_LENGTH 80
#define MSGBOX_LENGTH 4096
#define MSGBOX_WIDTH 128

#define CRITICAL_FILE "sys-log.c"
#define CRITICAL_LINE __LINE__

#define STATIC_LOG_FILENAME_SIZE 65536
static char static_log_filename[STATIC_LOG_FILENAME_SIZE + 1] = { 0 };

static char *
get_log_file ()
{
  char *log_file;

  if (static_log_filename[0] != 0)
    {
      log_file = static_log_filename;
    }
  else
    {
      log_file = lw6sys_get_default_log_file ();
      if (log_file)
	{
	  lw6sys_buf_sprintf (static_log_filename, STATIC_LOG_FILENAME_SIZE,
			      "%s", log_file);
	  LW6SYS_FREE (log_file);
	  log_file = static_log_filename;
	}
      else
	{
	  lw6sys_log_critical (_("log_file is NULL"));
	}
    }

  return log_file;
}

/*
 * Convenience fonction which returns the "macro" corresponding
 * to an errno code. I find it easier to use this than bothering
 * declaring a buffer for strerror_r... Besides LW6b has its own
 * error messages.
 */
static char *
errno_str (int errno_int)
{
  char *ret = "?";

  switch (errno_int)
    {
#ifdef E2BIG
    case E2BIG:
      ret = "E2BIG";
      break;
#endif
#ifdef EACCES
    case EACCES:
      ret = "EACCES";
      break;
#endif
#ifdef EADDRINUSE
    case EADDRINUSE:
      ret = "EADDRINUSE";
      break;
#endif
#ifdef EADDRNOTAVAIL
    case EADDRNOTAVAIL:
      ret = "EADDRNOTAVAIL";
      break;
#endif
#ifdef EAFNOSUPPORT
    case EAFNOSUPPORT:
      ret = "EAFNOSUPPORT";
      break;
#endif
#ifdef EAGAIN
    case EAGAIN:		// == EWOULDBLOCK
      ret = "EAGAIN";
      break;
#endif
#ifdef EALREADY
    case EALREADY:
      ret = "EALREADY";
      break;
#endif
#ifdef EBADF
    case EBADF:
      ret = "EBADF";
      break;
#endif
#ifdef EBADMSG
    case EBADMSG:
      ret = "EBADMSG";
      break;
#endif
#ifdef EBUSY
    case EBUSY:
      ret = "EBUSY";
      break;
#endif
#ifdef ECANCELED
    case ECANCELED:
      ret = "ECANCELED";
      break;
#endif
#ifdef ECHILD
    case ECHILD:
      ret = "ECHILD";
      break;
#endif
#ifdef ECONNABORTED
    case ECONNABORTED:
      ret = "ECONNABORTED";
      break;
#endif
#ifdef ECONNREFUSED
    case ECONNREFUSED:
      ret = "ECONNREFUSED";
      break;
#endif
#ifdef ECONNRESET
    case ECONNRESET:
      ret = "ECONNRESET";
      break;
#endif
#ifdef EDEADLK
    case EDEADLK:
      ret = "EDEADLK";
      break;
#endif
#ifdef EDESTADDRREQ
    case EDESTADDRREQ:
      ret = "EDESTADDRREQ";
      break;
#endif
#ifdef EDOM
    case EDOM:
      ret = "EDOM";
      break;
#endif
#ifdef EDQUOT
    case EDQUOT:
      ret = "EDQUOT";
      break;
#endif
#ifdef EEXIST
    case EEXIST:
      ret = "EEXIST";
      break;
#endif
#ifdef EFAULT
    case EFAULT:
      ret = "EFAULT";
      break;
#endif
#ifdef EFBIG
    case EFBIG:
      ret = "EFBIG";
      break;
#endif
#ifdef EHOSTUNREACH
    case EHOSTUNREACH:
      ret = "EHOSTUNREACH";
      break;
#endif
#ifdef EIDRM
    case EIDRM:
      ret = "EIDRM";
      break;
#endif
#ifdef EILSEQ
    case EILSEQ:
      ret = "EILSEQ";
      break;
#endif
#ifdef EINPROGRESS
    case EINPROGRESS:
      ret = "EINPROGRESS";
      break;
#endif
#ifdef EINTR
    case EINTR:
      ret = "EINTR";
      break;
#endif
#ifdef EINVAL
    case EINVAL:
      ret = "EINVAL";
      break;
#endif
#ifdef EIO
    case EIO:
      ret = "EIO";
      break;
#endif
#ifdef EISCONN
    case EISCONN:
      ret = "EISCONN";
      break;
#endif
#ifdef EISDIR
    case EISDIR:
      ret = "EISDIR";
      break;
#endif
#ifdef ELOOP
    case ELOOP:
      ret = "ELOOP";
      break;
#endif
#ifdef EMFILE
    case EMFILE:
      ret = "EMFILE";
      break;
#endif
#ifdef EMLINK
    case EMLINK:
      ret = "EMLINK";
      break;
#endif
#ifdef EMSGSIZE
    case EMSGSIZE:
      ret = "EMSGSIZE";
      break;
#endif
#ifdef EMULTIHOP
    case EMULTIHOP:
      ret = "EMULTIHOP";
      break;
#endif
#ifdef ENAMETOOLONG
    case ENAMETOOLONG:
      ret = "ENAMETOOLONG";
      break;
#endif
#ifdef ENETDOWN
    case ENETDOWN:
      ret = "ENETDOWN";
      break;
#endif
#ifdef ENETRESET
    case ENETRESET:
      ret = "ENETRESET";
      break;
#endif
#ifdef ENETUNREACH
    case ENETUNREACH:
      ret = "ENETUNREACH";
      break;
#endif
#ifdef ENFILE
    case ENFILE:
      ret = "ENFILE";
      break;
#endif
#ifdef ENOBUFS
    case ENOBUFS:
      ret = "ENOBUFS";
      break;
#endif
#ifdef ENODATA
    case ENODATA:
      ret = "ENODATA";
      break;
#endif
#ifdef ENODEV
    case ENODEV:
      ret = "ENODEV";
      break;
#endif
#ifdef ENOENT
    case ENOENT:
      ret = "ENOENT";
      break;
#endif
#ifdef ENOEXEC
    case ENOEXEC:
      ret = "ENOEXEC";
      break;
#endif
#ifdef ENOLCK
    case ENOLCK:
      ret = "ENOLCK";
      break;
#endif
#ifdef ENOLINK
    case ENOLINK:
      ret = "ENOLINK";
      break;
#endif
#ifdef ENOMEM
    case ENOMEM:
      ret = "ENOMEM";
      break;
#endif
#ifdef ENOMSG
    case ENOMSG:
      ret = "ENOMSG";
      break;
#endif
#ifdef ENOPROTOOPT
    case ENOPROTOOPT:
      ret = "ENOPROTOOPT";
      break;
#endif
#ifdef ENOSPC
    case ENOSPC:
      ret = "ENOSPC";
      break;
#endif
#ifdef ENOSR
    case ENOSR:
      ret = "ENOSR";
      break;
#endif
#ifdef ENOSTR
    case ENOSTR:
      ret = "ENOSTR";
      break;
#endif
#ifdef ENOSYS
    case ENOSYS:
      ret = "ENOSYS";
      break;
#endif
#ifdef ENOTCONN
    case ENOTCONN:
      ret = "ENOTCONN";
      break;
#endif
#ifdef ENOTDIR
    case ENOTDIR:
      ret = "ENOTDIR";
      break;
#endif
#ifdef ENOTEMPTY
    case ENOTEMPTY:
      ret = "ENOTEMPTY";
      break;
#endif
#ifdef ENOTSOCK
    case ENOTSOCK:
      ret = "ENOTSOCK";
      break;
#endif
#ifdef ENOTSUP
    case ENOTSUP:		// == EOPNOTSUPP
      ret = "ENOTSUP";
      break;
#endif
#ifdef ENOTTY
    case ENOTTY:
      ret = "ENOTTY";
      break;
#endif
#ifdef ENXIO
    case ENXIO:
      ret = "ENXIO";
      break;
#endif
#ifdef EOVERFLOW
    case EOVERFLOW:
      ret = "EOVERFLOW";
      break;
#endif
#ifdef EPERM
    case EPERM:
      ret = "EPERM";
      break;
#endif
#ifdef EPIPE
    case EPIPE:
      ret = "EPIPE";
      break;
#endif
#ifdef EPROTO
    case EPROTO:
      ret = "EPROTO";
      break;
#endif
#ifdef EPROTONOSUPPORT
    case EPROTONOSUPPORT:
      ret = "EPROTONOSUPPORT";
      break;
#endif
#ifdef EPROTOTYPE
    case EPROTOTYPE:
      ret = "EPROTOTYPE";
      break;
#endif
#ifdef ERANGE
    case ERANGE:
      ret = "ERANGE";
      break;
#endif
#ifdef EROFS
    case EROFS:
      ret = "EROFS";
      break;
#endif
#ifdef ESPIPE
    case ESPIPE:
      ret = "ESPIPE";
      break;
#endif
#ifdef ESRCH
    case ESRCH:
      ret = "ESRCH";
      break;
#endif
#ifdef ESTALE
    case ESTALE:
      ret = "ESTALE";
      break;
#endif
#ifdef ETIME
    case ETIME:
      ret = "ETIME";
      break;
#endif
#ifdef ETIMEDOUT
    case ETIMEDOUT:
      ret = "ETIMEDOUT";
      break;
#endif
#ifdef ETXTBSY
    case ETXTBSY:
      ret = "ETXTBSY";
      break;
#endif
#ifdef EXDEV
    case EXDEV:
      ret = "EXDEV";
      break;
#endif
    }

  return ret;
}

/**
 * lw6sys_log_set_file:
 *
 * @filename: the name of the log file.
 *
 * Sets up the log file. Until you call this function, messages
 * all logged to the default log file, as returned by
 * the @lw6sys_get_default_log_file function.
 *
 * Return value: void
 */
void
lw6sys_log_set_file (char *filename)
{
  memset (static_log_filename, 0, sizeof (static_log_filename));
  memcpy (static_log_filename, filename,
	  lw6sys_min (sizeof (static_log_filename) - 1, strlen (filename)));
}

/**
 * lw6sys_log_clear:
 *
 * @filename: the name of the log file.
 *
 * Clears the log file, this function would typically be called
 * at the beginning of the program. If filename is NULL, then the
 * default log file is cleared.
 *
 * Return value: void
 */
void
lw6sys_log_clear (char *filename)
{
  char *default_log_file = NULL;

  if (filename)
    {
      lw6sys_log_set_file (filename);
    }
  else
    {
      default_log_file = lw6sys_get_default_log_file ();
      filename = default_log_file;
    }

  if (filename)
    {
      lw6sys_clear_file (filename);
      if (!lw6sys_file_exists (filename))
	{
	  lw6sys_log_critical (_("can't open log file \"%s\""), filename);
	}
    }

  if (default_log_file)
    {
      LW6SYS_FREE (default_log_file);
    }
}

static FILE *
open_log_file ()
{
  FILE *ret = NULL;
  char *name;

  name = get_log_file ();
  ret = fopen (name, "ab");

  return ret;
}

static void
log_to_file (FILE * f, int level_id, char *level_str, char *file, int line,
	     char *fmt, va_list ap)
{
  time_t t_now;
  struct tm tm_now;
  struct tm *tm_ret = NULL;
  struct timeval timeval_now;

  memset (&t_now, 0, sizeof (time_t));
  memset (&tm_now, 0, sizeof (struct tm));
  memset (&timeval_now, 0, sizeof (struct timeval));
  gettimeofday (&timeval_now, NULL);
  t_now = timeval_now.tv_sec;
  tm_ret = localtime_r (&t_now, &tm_now);
  if (tm_ret == &tm_now)
    {
      fprintf (f, "%04d-%02d-%02d %02d.%02d:%02d,%03d\t%s:%d\t%d\t%s\t",
	       (int) tm_now.tm_year + 1900, (int) tm_now.tm_mon + 1,
	       (int) tm_now.tm_mday, (int) tm_now.tm_hour,
	       (int) tm_now.tm_min, (int) tm_now.tm_sec,
	       (int) timeval_now.tv_usec / (int) (1000000 /
						  LW6SYS_TICKS_PER_SEC),
	       file, line, level_id, level_str);
    }
  vfprintf (f, fmt, ap);
  fprintf (f, "\n");
  fflush (f);
}

static void
log_to_console (FILE * f, char *level_str, char *fmt, va_list ap)
{
  fprintf (f, "%s: %s", lw6sys_build_get_package_tarname (), level_str);
  vfprintf (f, fmt, ap);
  fprintf (f, "\n");
  fflush (f);
}

static void
log_to_history (char *level_str, char *fmt, va_list ap)
{
  char msg[HISTORY_LENGTH + 1];
  char full_msg[HISTORY_LENGTH + 1];

  _lw6sys_buf_vsnprintf (msg, HISTORY_LENGTH, fmt, ap);
  lw6sys_buf_sprintf (full_msg, HISTORY_LENGTH, "%s%s", level_str, msg);
  lw6sys_history_register (full_msg);
}

static void
msgbox_alert (char *level_str, char *file, int line, char *fmt, va_list ap)
{
  char message_raw[MSGBOX_LENGTH + 1];
  char message_full[MSGBOX_LENGTH + 1];

  lw6sys_buf_sprintf (message_raw, MSGBOX_LENGTH, fmt, ap);
  lw6sys_str_reformat_this (message_raw, MSGBOX_WIDTH);
  lw6sys_buf_sprintf (message_full, MSGBOX_LENGTH, "%s (%s:%d)\n\n%s",
		      level_str, file, line, message_raw);
#ifdef LW6_MS_WINDOWS
  if (message_full)
    {
      MessageBox (NULL,
		  message_full,
		  lw6sys_build_get_package_name (),
		  MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
#else
#ifdef LW6_MAC_OS_X
  _lw6sys_macosx_alert (lw6sys_build_get_package_name (), message_full);
#else
/*
 * Not implemented yet, below sample code, which would require to
 * link against gtk2, with:
 * CFLAGS=`pkg-config --cflags gtk+-2.0`
 * LDFLAGS=`pkg-config --libs gtk+-2.0`
 */
#ifdef LW6_GTK
  static int gtk_init_done = 0;
  /*
   * We fake argc & argv, OK this way GTK won't
   * be aware of *real* argc & argv values, but
   * passing them everywhere just for this is a pain.
   * calloc 2 pointers, last will be NULL, not
   * sure this is mandatory, but just in case.
   * Additionnally, argv must be mutable, this
   * justifies the argv_data hack. And... content is
   * static, never know if gtk needs them to stay
   * here, it might do as argc & argv usually
   * do not disappear within a program.
   */
  static char empty_str[1];
  static char *argv_data[2];
  int argc = 1;
  char **argv = NULL;
  GtkWidget *dlg = NULL;

  empty_str[0] = '\0';
  argv_data[0] = empty_str;
  argv_data[1] = NULL;
  argv = argv_data;
  if (!gtk_init_done)
    {
      gtk_init (&argc, &argv);
      gtk_init_done = 1;
    }
  dlg = gtk_message_dialog_new (NULL,
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_ERROR,
				GTK_BUTTONS_NONE, "%s", message_full);
  if (dlg)
    {
      gtk_window_set_title (GTK_WINDOW (dlg),
			    lw6sys_build_get_package_name ());
      gtk_dialog_add_button (GTK_DIALOG (dlg), GTK_STOCK_OK, GTK_RESPONSE_OK);
      gtk_dialog_run (GTK_DIALOG (dlg));
      gtk_widget_hide_all (dlg);
      gtk_main_iteration ();
      gtk_widget_destroy (dlg);
      gtk_main_iteration ();
    }
#endif
#endif
#endif
}

/**
 * lw6sys_log:
 *
 * @level_id: the log level to use. Possible values are, by order, 
 *   LW6SYS_LOG_ERROR_ID (0), 
 *   LW6SYS_LOG_WARNING_ID (1), 
 *   LW6SYS_LOG_NOTICE_ID (2), 
 *   LW6SYS_LOG_INFO_ID (3),
 *   LW6SYS_LOG_DEBUG_ID (4) and
 *   LW6SYS_LOG_TMP_ID (5).
 * @file: the name of the source file where the function is called,
 *   one can use __FILE__
 * @line: the line in the source file where the function is called,
 *   one can use __LINE__
 * @fmt: a printf-like format string
 * @...: printf-like arguments, corresponding to @fmt.
 *
 * This function is usually called with the first three arguments
 * packed into a single macro. For instance the
 * @LW6SYS_LOG_WARNING macro expands and fills the first 3
 * args, so there's no need to type __FILE__ and __LINE__ again
 * and again. Note that this function will reset errno. The
 * idea is to call it whenever there's something to do with errno
 * (if you deal with errno, it's a good habit to log it) then
 * errno is cleared so that it won't interfere with next log messages.
 *
 * @Return value: void
 */
void
lw6sys_log (int level_id, char *file, int line, char *fmt, ...)
{
#ifdef LW6_OPTIMIZE
  if ((level_id <= LW6SYS_LOG_NOTICE_ID
       && level_id <= lw6sys_log_get_level ())
      || level_id == LW6SYS_LOG_TMP_ID || lw6sys_debug_get ())
#else
  if (level_id <= lw6sys_log_get_level () || level_id == LW6SYS_LOG_TMP_ID
      || lw6sys_debug_get ())
#endif
    {
      char level_str[LEVEL_LENGTH + 1];
#ifdef HAVE_SYSLOG_H
      int syslog_priority = 0;
#endif
      FILE *f;
      int errno_int;
      va_list ap;
      va_list ap2;
      char *file_only = NULL;

      errno_int = errno;

      file_only = strrchr (file, '/');
      if (file_only && *file_only)
	{
	  file_only++;
	}
      else
	{
	  file_only = file;
	}

      va_start (ap, fmt);

      switch (level_id)
	{
	case LW6SYS_LOG_ERROR_ID:
	  if (errno_int)
	    {
	      lw6sys_buf_sprintf (level_str, LEVEL_LENGTH,
				  _("ERROR! (errno=%d:%s) "), errno_int,
				  errno_str (errno_int));
	    }
	  else
	    {
	      lw6sys_buf_sprintf (level_str, LEVEL_LENGTH, _("ERROR! "));
	    }
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_ERR;
#endif
	  break;
	case LW6SYS_LOG_WARNING_ID:
	  if (errno_int)
	    {
	      lw6sys_buf_sprintf (level_str, LEVEL_LENGTH,
				  _("WARNING! (errno=%d:%s) "), errno_int,
				  errno_str (errno_int));
	    }
	  else
	    {
	      lw6sys_buf_sprintf (level_str, LEVEL_LENGTH, _("WARNING! "));
	    }
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_WARNING;
#endif
	  break;
	case LW6SYS_LOG_NOTICE_ID:
	  level_str[0] = '\0';
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_NOTICE;
#endif
	  break;
	case LW6SYS_LOG_INFO_ID:
	  level_str[0] = '\0';
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_INFO;
#endif
	  break;
	case LW6SYS_LOG_TMP_ID:
	  lw6sys_buf_sprintf (level_str, LEVEL_LENGTH, _("[tmp] "));
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_DEBUG;
#endif
	  break;
	default:		// LW6SYS_LOG_DEBUG_ID
	  lw6sys_buf_sprintf (level_str, LEVEL_LENGTH, _("[debug] "));
#ifdef HAVE_SYSLOG_H
	  syslog_priority = LOG_DEBUG;
#endif
	  break;
	}

      if (fmt != NULL)
	{
	  // exclude INFO & DEBUG from console in non-debug mode
	  if (level_id <= LW6SYS_LOG_NOTICE_ID
	      || level_id == LW6SYS_LOG_TMP_ID || lw6sys_debug_get ())
	    {
	      va_copy (ap2, ap);
	      log_to_console (stderr, level_str, fmt, ap2);
	      va_end (ap2);
	    }
	  if (level_id <= LW6SYS_LOG_WARNING_ID
	      || level_id == LW6SYS_LOG_TMP_ID)
	    {
	      va_copy (ap2, ap);
	      log_to_history (level_str, fmt, ap2);
	      va_end (ap2);
	    }
#ifdef HAVE_SYSLOG_H
	  if (level_id <= LW6SYS_LOG_WARNING_ID
	      || level_id == LW6SYS_LOG_TMP_ID)
	    {
	      va_copy (ap2, ap);
	      vsyslog (syslog_priority, fmt, ap2);
	      va_end (ap2);
	    }
#endif
	  f = open_log_file ();
	  if (f)
	    {
	      va_copy (ap2, ap);
	      log_to_file (f, level_id, level_str, file_only, line, fmt, ap2);
	      va_end (ap2);
	      fclose (f);
	    }
	  if (level_id <= LW6SYS_LOG_ERROR_ID)
	    {
	      va_copy (ap2, ap);
	      msgbox_alert (level_str, file_only, line, fmt, ap2);
	      va_end (ap2);
	    }
	}

      va_end (ap);
    }

  /*
   * We reset errno to avoid getting pointless errno in logs,
   * the idea is to print errno when needed...
   */
  errno = 0;
}

/**
 * lw6sys_log_critical:
 *
 * @fmt: a printf-like format string
 * @...: printf-like arguments, corresponding to @fmt.
 *
 * This function is a special log function which will dump informations
 * on the console only, without opening any log file whatsoever. The idea
 * is that it's a "never fail" function. Additionnally, it will never
 * return but quit the program. This can be used as an ultimate emergency
 * function, use it when the program won't run for sure, and displaying
 * an immediate error message is the only issue.
 *
 * @Return value: void
 */
void
lw6sys_log_critical (char *fmt, ...)
{
  va_list ap;
  va_list ap2;

  va_start (ap, fmt);

  va_copy (ap2, ap);
  log_to_console (stderr, _("CRITICAL! "), fmt, ap2);
  va_end (ap2);

  va_copy (ap2, ap);
  msgbox_alert (_("CRITICAL!"), CRITICAL_FILE, CRITICAL_LINE, fmt, ap2);
  va_end (ap2);

  exit (_LW6SYS_EXIT_CRITICAL);

  va_end (ap);
}

/**
 * lw6sys_log_get_level
 *
 * @Return value: the log level, integer between 0 & 4. 4 is very verbose
 * (debug), 0 displays errors only.
 */
int
lw6sys_log_get_level ()
{
  return _lw6sys_global.log_level;
}

/**
 * lw6sys_log_set_level
 *
 * @level: the log level, integer between 0 & 4. 4 is very verbose (debug),
 * 0 displays errors only.
 */
void
lw6sys_log_set_level (int level)
{
  level = lw6sys_min (level, LW6SYS_LOG_DEBUG_ID);
  level = lw6sys_max (level, LW6SYS_LOG_ERROR_ID);

  _lw6sys_global.log_level = level;
}
