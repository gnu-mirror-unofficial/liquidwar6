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

#ifndef LIQUIDWAR6SYS_H
#define LIQUIDWAR6SYS_H

#ifdef HAVE_GETTEXT
#include "sys-gettext.h"
#ifndef _
#define _(string) gettext(string)
#endif
#else
#define _(string) string
#endif

/*
 * Because program has so many strings, it's not reasonnable to
 * translate them all (at least for now) as most of them are
 * debugging messages. However it's important not to loose a
 * trace of "potentially translatable" candidates, so we mark
 * them with _x_ instead of _ this way they don't appear in
 * .po files but at the same time a trivial sed command can make
 * them appear back again. Additionnally, not using gettext
 * on never-translated debugging messages does save time.
 */
#define _x_(string) string

#ifndef bindtextdomain
#include <libintl.h>
#endif

#ifndef setlocale
#include <locale.h>
#endif

/*
 * Those are so common it saves time to always include them
 */
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef LW6_MS_WINDOWS
#ifndef LW6_SKIP_WINDOWS_H
#include <windows.h>
#endif
#endif

/*
 * Redefining basic types mostly for platforms like MinGW which do
 * not have a complete nice GNU libc 8-(
 */
#ifdef LW6_MS_WINDOWS
#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef signed short int16_t;
#endif
#ifndef int32_t
typedef signed int int32_t;
#endif
#ifndef int64_t
typedef signed long long int64_t;
#endif
#ifndef u_int8_t
typedef unsigned char u_int8_t;
#endif
#ifndef u_int16_t
typedef unsigned short u_int16_t;
#endif
#ifndef u_int32_t
typedef unsigned int u_int32_t;
#endif
#ifndef u_int64_t
typedef unsigned long long u_int64_t;
#endif
#endif // MS_WINDOWS

#ifndef char_ptr_t
typedef char *char_ptr_t;
#endif

#define LW6SYS_QUOTE(STR) #STR
#define LW6SYS_STR_EMPTY ""
#define LW6SYS_TICKS_PER_SEC 1000L
#define LW6SYS_SLEEP_DELAY 1
#define LW6SYS_SNOOZE_DELAY 100

#define LW6SYS_EXIT_OK 0
#define LW6SYS_EXIT_ERROR 1
#define LW6SYS_EXIT_CRITICAL 2

/*
 * Yet another MS-windows hack, printf %ll doesn't work
 * one needs to use a special "%I64" instead...
 */
#ifdef LW6_MS_WINDOWS
#define LW6SYS_PRINTF_LL "I64"
#else
#define LW6SYS_PRINTF_LL "ll"
#endif

#include "../def/def.h"

#ifdef LW6_PARANOID
#define LW6SYS_BAZOOKA_DEFAULT_SIZE 999983
#else
#define LW6SYS_BAZOOKA_DEFAULT_SIZE 99991
#endif

#define LW6SYS_MAIN_BEGIN { setlocale (LC_ALL, ""); bindtextdomain (lw6sys_build_get_package_tarname (), lw6sys_build_get_localedir ()); textdomain (lw6sys_build_get_package_tarname ()); lw6sys_time_init(); lw6sys_history_init(); lw6sys_default_memory_bazooka(); lw6sys_profiler_check(1); }
#define LW6SYS_MAIN_END { ret = lw6sys_check_thread_count () && ret; ret = lw6sys_memory_bazooka_report() && ret; lw6sys_clear_memory_bazooka(); }

#define LW6SYS_TEST_FUNCTION_BEGIN { lw6sys_log(LW6SYS_LOG_NOTICE,_("running tests in function \"%s\""),__FUNCTION__); }
#define LW6SYS_TEST_FUNCTION_END   if (ret) { lw6sys_log(LW6SYS_LOG_NOTICE,_("tests in \"%s\" OK"),__FUNCTION__); } else { lw6sys_log(LW6SYS_LOG_WARNING,_("tests in \"%s\" failed"),__FUNCTION__); }
#define LW6SYS_BACKEND_FUNCTION_BEGIN { lw6sys_log(LW6SYS_LOG_DEBUG,_("begin backend function \"%s\""),__FUNCTION__); }
#define LW6SYS_BACKEND_FUNCTION_END { lw6sys_log(LW6SYS_LOG_DEBUG,_("end backend function \"%s\""),__FUNCTION__); }

#define LW6SYS_SCRIPT_FUNCTION_BEGIN { lw6sys_log(LW6SYS_LOG_DEBUG,_("begin script function \"%s\""),__FUNCTION__); }
#define LW6SYS_SCRIPT_FUNCTION_END { lw6sys_log(LW6SYS_LOG_DEBUG,_("end script function \"%s\""),__FUNCTION__); }

#define LW6SYS_TEST_OUTPUT { if (ret) { lw6sys_log(LW6SYS_LOG_NOTICE,_("test SUCCESSFULL!")); } else { lw6sys_log(LW6SYS_LOG_WARNING,_("test FAILED...")); } }

#define LW6SYS_BUILD_ENABLE_YES "yes"
#define LW6SYS_BUILD_ENABLE_NO "no"

/**
 * All-in 32 bit 3D position, to save memory.
 *
 * It's a deliberate choice in Liquid War to handle "limited size"
 * levels. In fact 14 bits still allows 8000x8000 maps, which are
 * at least 100 times too slow to play now (2008). Should we follow
 * Moore's law we'd have at least 6 years until those are playable,
 * and well, until then, let's wait. The point is that storing this
 * information (x*y) on 4 bytes might be very important in some cases,
 * since it can reduce memory footprint on structs which are stored
 * in numerous quantities, and therefore maximize chances that we
 * use level 1 & 2 caches and other nice things which happen when
 * memory consumption is not too high.
 *
 * Point is: why use INT32 and then limit it to 14 bits instead of
 * using an INT16 or short in the first place? Answer: it's easier
 * to handle INT32 all the time in the rest of the code. Compiler
 * and CPU might even handle that better than short. Then, and only
 * when data will be read/written in the struct will it be truncated.
 * Typical example is: we want to multiplicate y by w (which is a
 * width). Result is beyond INT16/short scope but we want to handle
 * it! Casting everything to INT32/int is a pain. With this int y:14
 * trick, we use y as a "full-featured" INT32/int and well, when it
 * will be read/written we'll loose values over 8191, but we simply
 * do not care.
 */
typedef struct lw6sys_xyz_s
{
  /// X position, from -8192 to +8191.
  int32_t x:14;
  /// Y position, from -8192 to +8191.
  int32_t y:14;
  /// Z position, from -8 to +7.
  int32_t z:4;
}
lw6sys_xyz_t;

/**
 * Contains the shape of a 3D box. There are 3 differences with its 
 * "XYZ" equivalent. First, sometimes w*h*d reads better than x,y,z.
 * Then, xyz is signed, whd is unsigned. Finally, these are real
 * int32 values, they are not 14-bit limited. 
 * It does not really cost any memory for it's usually used as 
 * a single "shape" attribute for a whole map. At the same time, 
 * it's very often used as a test value in loops, so it's interesting 
 * to have it in a value that's easy to optimize for the compiler
 * (exactly one register...)
 */
typedef struct lw6sys_whd_s
{
  /// Width.
  u_int32_t w;
  /// Height.
  u_int32_t h;
  /// Depth.
  u_int32_t d;
}
lw6sys_whd_t;

/**
 * Used to store colors when representing them in RGBA mode
 * with floats ranging from 0.0f to 1.0f.
 */
typedef struct lw6sys_color_f_s
{
  /// Red [0 ... 1.0f].
  float r;
  /// Green [0 ... 1.0f].
  float g;
  /// Blue [0 ... 1.0f].
  float b;
  /// Alpha [0 ... 1.0f]. 1.0f is opaque, 0.0f is transparent.
  float a;
}
lw6sys_color_f_t;

/**
 * Used to store colors when representing them in RGBA mode
 * with integers ranging from 0 to 255.
 */
typedef struct lw6sys_color_8_s
{
  /// Red [0 ... 255].
  u_int8_t r;
  /// Green [0 ... 255].
  u_int8_t g;
  /// Blue [0 ... 255].
  u_int8_t b;
  /// Alpha [0 ... 255]. 255 is opaque, 0 is transparent.
  u_int8_t a;
}
lw6sys_color_8_t;

/**
 * Used to store colors when representing them in HSV mode
 * with floats ranging from 0.0f to 1.0f. An alpha channel
 * has been added so this is more HSVA than HSV.
 */
typedef struct lw6sys_color_hsv_s
{
/// Hue [0 ... 360.0f]. 0.0f is red, 120.0f is green, 240.0f is blue.
  float h;
/// Saturation [0 ... 1.0f].
  float s;
  /// Value      [0 ... 1.0f].
  float v;
/// Alpha [0 ... 1.0f]. 1.0f is opaque, 0.0f is transparent.
  float a;
}
lw6sys_color_hsv_t;

/**
 * Structure used to store progress information. The idea
 * is that is that must be usable in polling mode or in
 * multithreaded mode, and we must be able to truncate a
 * progress indicator into several stages. So this structure
 * contains a range start, a range end, and its value between
 * those two, which is meant to be written by the code executing
 * the operation and read by the caller/rendering thread.
 */
typedef struct lw6sys_progress_s
{
  /// Where the progress operation starts.
  float min;
  /// Where the progress operation ends.
  float max;
  /// Somewhere between min and max.
  volatile float *value;
} lw6sys_progress_t;

/**
 * Structure used to store informations about a module.
 * This describes the module, its author license, this is
 * both a legal check and a technical check, to maximize
 * the chances the code we're running is the right one,
 * and to trace it.
 */
typedef struct lw6sys_module_pedigree_s
{
  /// Module id, for instance, could be "gl".
  char *id;
  /// Module category, for instance, could be "gfx".
  char *category;
  /// Module name, readable (displayable) name.
  char *name;
  /// Module readme text.
  char *readme;
  /// Module version.
  char *version;
  /// Module (short) copyright information.
  char *copyright;
  /// Module (short) license.
  char *license;
  /// Date of module compilation.
  char *date;
  /// Time of module compilation.
  char *time;
} lw6sys_module_pedigree_t;

#define LW6SYS_SIZEOF_INT8 1
#define LW6SYS_SIZEOF_INT16 2
#define LW6SYS_SIZEOF_INT32 4
#define LW6SYS_SIZEOF_INT64 8

#define LW6SYS_SIZEOF_XYZ 4

#define LW6SYS_LEN_ID_16 4
#define LW6SYS_LEN_ID_32 8
#define LW6SYS_LEN_ID_64 16

#define LW6SYS_BROADCAST_ID_16 0xffff
#define LW6SYS_BROADCAST_ID_32 0xffffffff
#define LW6SYS_BROADCAST_ID_64 0xffffffffffffffffLL

typedef void (*lw6sys_free_func_t) (void *data);
typedef void (*lw6sys_assoc_callback_func_t) (void *func_data,
					      const char *key, void *value);
typedef void (*lw6sys_list_callback_func_t) (void *func_data, void *data);
typedef int (*lw6sys_list_filter_func_t) (void *func_data, void *data);
typedef void *(*lw6sys_dup_func_t) (void *data);
typedef void (*lw6sys_thread_callback_func_t) (void *callback_data);
typedef int (*lw6sys_dir_list_filter_func_t) (void *func_data, char *file);
typedef void (*lw6sys_fork_func_t) ();

typedef struct lw6sys_assoc_s *lw6sys_assoc_p;

/**
 * Assoc is a basic key/pair structure where key is a string.
 * Use it for basic associations, it's not fast when there are
 * many keys, in that case, prefer a hash.
 */
typedef struct lw6sys_assoc_s
{
  /// The key, a 0 terminated standard C string.
  char *key;
  /// The value, pointer to arbitrary data.
  void *value;
  /**
   * This function will be called whenever the element is
   * deleted. You can set it to NULL in that case no callback
   * will be called on deletion.
   */
  lw6sys_free_func_t free_func;
  /** 
   * Pointer on the next item, will be NULL on last element,
   * there's a difference between a NULL pointer and a valid
   * assoc with only one item being EOL.
   */
  lw6sys_assoc_p next_item;
}
lw6sys_assoc_t;

/**
 * Hash is a basic hash structure, relying on assoc for
 * implementation. Actually, what it does is storing an array
 * of assoc, the number of assoc elements is given at construction.
 * Then when accessing a member, a quick checksum is made from
 * the key, which enables finding out which assoc must be queried.
 * If the hash is properly sized, then once one has found the
 * right assoc, finding the right key is fast, since there are
 * only a few of them in each assoc, and it avoids scanning for
 * for all keys, which is the very purpose of the hash.
 */
typedef struct lw6sys_hash_s
{
  /// Number of assoc used for this hash, passed at construction.
  int size;
  /// Array of assoc holding the actual data.
  lw6sys_assoc_t **entries;
  /**
   * This function will be called whenever the element is
   * deleted. You can set it to NULL in that case no callback
   * will be called on deletion.
   */
  lw6sys_free_func_t free_func;
}
lw6sys_hash_t;

typedef struct lw6sys_list_s *lw6sys_list_p;

/**
 * List is a basic list system, with a void * pointer to
 * hold arbitrary data and a callback function for deletion.
 * Provides basic functions to push, pop, walk, any array-like
 * call will of course be very slow. As of current implementation,
 * front operations are fast, but back operations are slow.
 */
typedef struct lw6sys_list_s
{
  /// Opaque pointer on element data.
  void *data;
  /**
   * This function will be called whenever the element is
   * deleted. You can set it to NULL in that case no callback
   * will be called on deletion.
   */
  lw6sys_free_func_t free_func;
  /** 
   * Pointer on the next item, will be NULL on last element,
   * there's a difference between a NULL pointer and a valid
   * list with only one item being EOL. Other way to state it:
   * NULL and empty list are two different things.
   */
  lw6sys_list_p next_item;
}
lw6sys_list_t;

typedef int (*lw6sys_sort_callback_func_t) (lw6sys_list_t ** list_a,
					    lw6sys_list_t ** list_b);

/**
 * The hexa (for hexadecimal) serializer is a tool used
 * to simplify serialization processes, you can just push/pop
 * basic data types on it, it will concatenate the string,
 * allocate memory, do all this dirty stuff without requiring
 * you to plan the size of the buffer, among other things.
 */
typedef struct lw6sys_hexa_serializer_s
{
  /// Data buffer.
  char *buf;
  /// Size of data buffer, in bytes.
  int buf_size;
  /**
   * Current position within the buffer, this is, typically,
   * the place where data will be appended at the next push call,
   * or where it will be fetched from at the next pop call.
   */
  int pos;
}
lw6sys_hexa_serializer_t;

/**
 * Describes an URL, with its elements splitted, this is
 * just to be able to use half-parsed URLs and avoid redoing
 * this parsing everytime.
 */
typedef struct lw6sys_url_s
{
  /// 1 if in https, 0 if in http.
  int use_ssl;
  /// Host name.
  char *host;
  /// IP port.
  int port;
  /// URI, that is, everything after the port.
  char *uri;
}
lw6sys_url_t;

extern lw6sys_color_f_t LW6SYS_COLOR_F_WHITE;
extern lw6sys_color_f_t LW6SYS_COLOR_F_BLACK;
extern lw6sys_color_f_t LW6SYS_COLOR_F_RED;
extern lw6sys_color_f_t LW6SYS_COLOR_F_GREEN;
extern lw6sys_color_f_t LW6SYS_COLOR_F_BLUE;
extern lw6sys_color_8_t LW6SYS_COLOR_8_WHITE;
extern lw6sys_color_8_t LW6SYS_COLOR_8_BLACK;
extern lw6sys_color_8_t LW6SYS_COLOR_8_RED;
extern lw6sys_color_8_t LW6SYS_COLOR_8_GREEN;
extern lw6sys_color_8_t LW6SYS_COLOR_8_BLUE;
extern lw6sys_color_hsv_t LW6SYS_COLOR_HSV_WHITE;
extern lw6sys_color_hsv_t LW6SYS_COLOR_HSV_BLACK;
extern lw6sys_color_hsv_t LW6SYS_COLOR_HSV_RED;
extern lw6sys_color_hsv_t LW6SYS_COLOR_HSV_GREEN;
extern lw6sys_color_hsv_t LW6SYS_COLOR_HSV_BLUE;

#define LW6SYS_FILE_README "README"
#define LW6SYS_FILE_README_TXT "readme.txt"

/*
 * Usefull macros for lw6sys_log, please do not use
 * lw6sys_log directly, but use constructs like
 * lw6sys_log(LW6SYS_LOG_<LEVEL>,"%s%d",str,num);
 */
#define LW6SYS_LOG_ERROR_ID 0
#define LW6SYS_LOG_WARNING_ID 1
#define LW6SYS_LOG_NOTICE_ID 2
#define LW6SYS_LOG_INFO_ID 3
#define LW6SYS_LOG_DEBUG_ID 4
#define LW6SYS_LOG_TMP_ID 5
#define LW6SYS_LOG_ERROR LW6SYS_LOG_ERROR_ID, __FILE__, __LINE__
#define LW6SYS_LOG_WARNING LW6SYS_LOG_WARNING_ID, __FILE__, __LINE__
#define LW6SYS_LOG_NOTICE LW6SYS_LOG_NOTICE_ID, __FILE__, __LINE__
#define LW6SYS_LOG_INFO LW6SYS_LOG_INFO_ID, __FILE__, __LINE__
#define LW6SYS_LOG_DEBUG LW6SYS_LOG_DEBUG_ID, __FILE__, __LINE__
#define LW6SYS_LOG_TMP LW6SYS_LOG_TMP_ID, __FILE__, __LINE__

#define LW6SYS_LOG_DEFAULT_ID LW6SYS_LOG_INFO_ID

/*
 * macro TMP defined for quick-debugging / trace
 */
#define TMP(message) lw6sys_log(LW6SYS_LOG_TMP, message)
#define TMP1(message,arg1) lw6sys_log(LW6SYS_LOG_TMP, message, arg1)
#define TMP2(message,arg1,arg2) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2)
#define TMP3(message,arg1,arg2,arg3) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3)
#define TMP4(message,arg1,arg2,arg3,arg4) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4)
#define TMP5(message,arg1,arg2,arg3,arg4,arg5) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4, arg5)
#define TMP6(message,arg1,arg2,arg3,arg4,arg5,arg6) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4, arg5, arg6)
#define TMP7(message,arg1,arg2,arg3,arg4,arg5,arg6,arg7) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#define TMP8(message,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#define TMP9(message,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9) lw6sys_log(LW6SYS_LOG_TMP, message, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)

/*
 * Instant backtrace facility
 */
#define BT { char *bt=lw6sys_backtrace(0); if (bt) { TMP1("bt: \"%s\"",bt); LW6SYS_FREE(bt); } }

/*
 * Common indenting parameters
 */
#define LW6SYS_REFORMAT_DEFAULT_PREFIX ""
#define LW6SYS_REFORMAT_DEFAULT_NB_COLUMNS 78
#define LW6SYS_REFORMAT_INDENT_PREFIX "        "
#define LW6SYS_REFORMAT_INDENT_NB_COLUMNS 70
#define LW6SYS_REFORMAT_XML_PREFIX "    "
#define LW6SYS_REFORMAT_XML_NB_COLUMNS 74

/**
 * Mutex is our own wrapper on the pthread mutex object.
 * Why not use the pthread mutex directly? For debugging,
 * this allows us to place and instrument hooks if needed.
 */
typedef struct lw6sys_mutex_s
{
  /**
   * The id of the object, this is non-zero and unique within one run session,
   * incremented at each object creation.
   */
  u_int32_t id;
} lw6sys_mutex_t;

/**
 * Spinlock is our own wrapper on a spinlock based mutex.
 * Why not use the pthread spinlock directly? For debugging,
 * this allows us to place and instrument hooks if needed.
 * Additionnally, some implementations of pthread do not provide
 * spinlock and in that case we provide our own alternative.
 */
typedef struct lw6sys_spinlock_s
{
  /**
   * The id of the object, this is non-zero and unique within one run session,
   * incremented at each object creation.
   */
  u_int32_t id;
} lw6sys_spinlock_t;

/**
 * Thread handler is our own wrapper on the pthread object.
 * Why not use the pthread handler directly? Basically to
 * store basic flags and context data (void * pointer on
 * our thread data for instance) along with the handler.
 * This is merely for debugging and convenience. Internally
 * this will be casted to _lw6sys_thread_handler_t.
 */
typedef struct lw6sys_thread_handler_s
{
  /**
   * The id of the object, this is non-zero and unique within one run session,
   * incremented at each object creation.
   */
  u_int32_t id;
} lw6sys_thread_handler_t;

/* sys-arg.c */
extern int lw6sys_arg_match (const char *keyword, const char *argv_string);
extern int lw6sys_arg_exists (int argc, const char *argv[],
			      const char *keyword);
extern char *lw6sys_arg_get_value (int argc, const char *argv[],
				   const char *keyword);
extern char *lw6sys_arg_get_value_with_env (int argc, const char *argv[],
					    const char *keyword);
extern int lw6sys_arg_test_mode (int argc, const char *argv[]);

/* sys-assoc.c */
extern lw6sys_assoc_t *lw6sys_assoc_new (lw6sys_free_func_t free_func);
extern void lw6sys_assoc_free (lw6sys_assoc_t * assoc);
extern int lw6sys_assoc_has_key (lw6sys_assoc_t * assoc, const char *key);
extern void *lw6sys_assoc_get (lw6sys_assoc_t * assoc, const char *key);
extern void lw6sys_assoc_set (lw6sys_assoc_t ** assoc, const char *key,
			      void *value);
extern void lw6sys_assoc_unset (lw6sys_assoc_t * assoc, const char *key);
extern lw6sys_list_t *lw6sys_assoc_keys (lw6sys_assoc_t * assoc);
extern void lw6sys_assoc_map (lw6sys_assoc_t * assoc,
			      lw6sys_assoc_callback_func_t func,
			      void *func_data);
extern void lw6sys_assoc_sort_and_map (lw6sys_assoc_t * assoc,
				       lw6sys_assoc_callback_func_t func,
				       void *func_data);
extern lw6sys_assoc_t *lw6sys_assoc_dup (lw6sys_assoc_t * assoc,
					 lw6sys_dup_func_t dup_func);

/* sys-backtrace.c */
extern char *lw6sys_backtrace (int skip);

/* sys-bazooka.c */
extern int lw6sys_default_memory_bazooka ();
extern void lw6sys_clear_memory_bazooka ();
extern int lw6sys_set_memory_bazooka_size (int size);
extern int lw6sys_get_memory_bazooka_size ();
extern int lw6sys_set_memory_bazooka_eraser (int state);
extern int lw6sys_get_memory_bazooka_eraser ();
extern int lw6sys_get_memory_bazooka_malloc_count ();
extern int lw6sys_get_memory_bazooka_free_count ();
extern int lw6sys_get_memory_bazooka_malloc_max ();
extern int lw6sys_get_memory_bazooka_malloc_count ();
extern int lw6sys_get_memory_bazooka_free_count ();
extern int lw6sys_get_memory_bazooka_malloc_current_count ();
extern int lw6sys_get_memory_bazooka_malloc_max_count ();
extern int lw6sys_get_memory_bazooka_malloc_megabytes ();
extern int lw6sys_get_memory_bazooka_free_megabytes ();
extern int lw6sys_get_memory_bazooka_malloc_current_bytes ();
extern int lw6sys_get_memory_bazooka_malloc_max_bytes ();
extern int lw6sys_memory_bazooka_report ();

/* sys-build.c */
extern char *lw6sys_build_get_package_tarname ();
extern char *lw6sys_build_get_package_name ();
extern char *lw6sys_build_get_package_string ();
extern char *lw6sys_build_get_package_id ();
extern char *lw6sys_build_get_version ();
extern char *lw6sys_build_get_codename ();
extern char *lw6sys_build_get_stamp ();
extern char *lw6sys_build_get_md5sum ();
extern char *lw6sys_build_get_copyright ();
extern char *lw6sys_build_get_license ();
extern char *lw6sys_build_get_home_url ();
extern char *lw6sys_build_get_bugs_url ();
extern char *lw6sys_build_get_configure_args ();
extern char *lw6sys_build_get_gcc_version ();
extern char *lw6sys_build_get_cflags ();
extern char *lw6sys_build_get_ldflags ();
extern char *lw6sys_build_get_hostname ();
extern char *lw6sys_build_get_date ();
extern char *lw6sys_build_get_time ();
extern char *lw6sys_build_get_host_cpu ();
extern char *lw6sys_build_get_endianness ();
extern int lw6sys_build_get_pointer_size ();
extern int lw6sys_build_is_x86 ();
extern char *lw6sys_build_get_host_os ();
extern int lw6sys_build_is_gnu ();
extern int lw6sys_build_is_unix ();
extern int lw6sys_build_is_ms_windows ();
extern int lw6sys_build_is_mac_os_x ();
extern int lw6sys_build_is_gp2x ();
extern char *lw6sys_build_get_top_srcdir ();
extern char *lw6sys_build_get_prefix ();
extern char *lw6sys_build_get_datadir ();
extern char *lw6sys_build_get_libdir ();
extern char *lw6sys_build_get_includedir ();
extern char *lw6sys_build_get_localedir ();
extern char *lw6sys_build_get_docdir ();
extern char *lw6sys_build_get_enable_console ();
extern char *lw6sys_build_get_enable_gtk ();
extern char *lw6sys_build_get_enable_mod_gl ();
extern char *lw6sys_build_get_enable_mod_csound ();
extern char *lw6sys_build_get_enable_mod_ogg ();
extern char *lw6sys_build_get_enable_mod_http ();
extern char *lw6sys_build_get_enable_openmp ();
extern char *lw6sys_build_get_enable_optimize ();
extern char *lw6sys_build_get_enable_allinone ();
extern char *lw6sys_build_get_enable_fullstatic ();
extern char *lw6sys_build_get_enable_paranoid ();
extern char *lw6sys_build_get_enable_gprof ();
extern char *lw6sys_build_get_enable_instrument ();
extern char *lw6sys_build_get_enable_profiler ();
extern char *lw6sys_build_get_enable_gcov ();
extern char *lw6sys_build_get_enable_valgrind ();
extern int lw6sys_build_get_bin_id ();
extern void lw6sys_build_log_all ();

/* sys-chr.c */
static inline int
lw6sys_chr_is_digit (char c)
{
  return (c >= '0' && c <= '9');
}

static inline int
lw6sys_chr_is_alnum (char c)
{
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
							      && c <= 'Z');
}

static inline int
lw6sys_chr_is_space (char c)
{
  return (c == ' ' || c == '\t');
}

static inline int
lw6sys_chr_is_eol (char c)
{
  return (c == '\n' || c == '\r');
}

/* sys-checksum.c */
extern u_int32_t lw6sys_checksum (unsigned char *data, int len);
extern u_int32_t lw6sys_checksum_str (const char *value);
extern u_int32_t lw6sys_checksum_int32 (u_int32_t value);
extern u_int32_t lw6sys_checksum_int64 (u_int64_t value);
extern u_int32_t lw6sys_checksum_whd (lw6sys_whd_t * whd);
extern u_int32_t lw6sys_checksum_xyz (lw6sys_xyz_t * xyz);
extern void lw6sys_checksum_update (u_int32_t * checksum,
				    unsigned char *data, int len);
extern void lw6sys_checksum_update_str (u_int32_t * checksum,
					const char *value);
extern void lw6sys_checksum_update_int32 (u_int32_t * checksum,
					  int32_t value);
extern void lw6sys_checksum_update_int64 (u_int32_t * checksum,
					  int64_t value);
extern void lw6sys_checksum_update_whd (u_int32_t * checksum,
					lw6sys_whd_t * whd);
extern void lw6sys_checksum_update_xyz (u_int32_t * checksum,
					lw6sys_xyz_t * xyz);

/* sys-color.c */
extern u_int8_t lw6sys_color_float2char (float f);
extern float lw6sys_color_char2float (u_int8_t i);
extern lw6sys_color_8_t lw6sys_color_f_to_8 (const lw6sys_color_f_t *
					     color_f);
extern void lw6sys_color_8_to_f (lw6sys_color_f_t * color_f,
				 lw6sys_color_8_t color_8);
extern u_int32_t lw6sys_color_f_to_i (const lw6sys_color_f_t * color_f);
extern u_int32_t lw6sys_color_8_to_i (lw6sys_color_8_t color_8);
extern void lw6sys_color_i_to_f (lw6sys_color_f_t * color_f,
				 u_int32_t color_i);
extern lw6sys_color_8_t lw6sys_color_i_to_8 (u_int32_t color_i);
extern lw6sys_color_8_t lw6sys_color_a_to_8 (const char *ascii);
extern void lw6sys_color_a_to_f (lw6sys_color_f_t * color_f,
				 const char *ascii);
extern char *lw6sys_color_8_to_a (lw6sys_color_8_t color_8);
extern void lw6sys_color_rgb_to_hsv (lw6sys_color_hsv_t * color_hsv,
				     lw6sys_color_8_t color_8);
extern lw6sys_color_8_t lw6sys_color_hsv_to_rgb (const lw6sys_color_hsv_t *
						 color_hsv);
extern void lw6sys_color_hsv_invert (lw6sys_color_hsv_t * color_hsv,
				     int invert_h, int invert_s,
				     int invert_v);
extern int lw6sys_color_is_grey (lw6sys_color_8_t color);
extern lw6sys_color_8_t lw6sys_color_average (int size,
					      const lw6sys_color_8_t *
					      colors);
extern lw6sys_color_8_t lw6sys_color_ponderate (lw6sys_color_8_t color1,
						lw6sys_color_8_t color2,
						float coeff);
extern float lw6sys_color_distance (lw6sys_color_8_t color1,
				    lw6sys_color_8_t color2);
extern int lw6sys_color_is_same (const lw6sys_color_8_t color1,
				 const lw6sys_color_8_t color2);
extern void lw6sys_color_8_solid (lw6sys_color_8_t * color);
extern void lw6sys_color_f_solid (lw6sys_color_f_t * color);

/* sys-convert.c */
extern int lw6sys_atoi (const char *str);
extern int64_t lw6sys_atoll (const char *str);
extern int lw6sys_atob (const char *str);
extern float lw6sys_atof (const char *str);
extern char *lw6sys_itoa (int value);
extern char *lw6sys_lltoa (int64_t value);
extern char *lw6sys_btoa (int value);
extern char *lw6sys_ftoa (float value);

/* sys-daemon.c */
extern char *lw6sys_daemon_pid_file (int argc, const char *argv[]);
extern int lw6sys_daemon_start (char *pid_file);
extern int lw6sys_daemon_stop (char *pid_file);

/* sys-debug.c */
extern int lw6sys_debug_get ();
extern void lw6sys_debug_set (int mode);

/* sys-dump.c */
extern void lw6sys_dump_clear (char *user_dir);
extern int lw6sys_dump (char *user_dir, char *content);

/* sys-env.c */
extern char lw6sys_env_separator_char ();
extern char *lw6sys_env_separator_str ();
extern char *lw6sys_env_concat (const char *value1, const char *value2);
extern int lw6sys_env_exists_prefixed (const char *keyword);
extern char *lw6sys_getenv (const char *key);
extern char *lw6sys_getenv_prefixed (const char *keyword);
extern int lw6sys_setenv (const char *keyword, const char *value);
extern int lw6sys_setenv_prefixed (const char *keyword, const char *value);
extern lw6sys_list_t *lw6sys_env_split (const char *value);
extern char *lw6sys_get_home ();
extern char *lw6sys_get_username ();
extern char *lw6sys_get_hostname ();

/* sys-escape.c */
extern char *lw6sys_escape_http_uri (const char *src);
extern char *lw6sys_escape_html_attribute (const char *src);
extern char *lw6sys_escape_sql_value (const char *src);

/* sys-exec.c */
extern char *lw6sys_exec_find_myself (int argc, const char *argv[]);
extern int lw6sys_is_executed_again (int argc, const char *argv[]);
extern int lw6sys_exec_again (int argc, const char *argv[]);
extern int lw6sys_exec_restart (int argc, const char *argv[]);

/* sys-file.c */
extern int lw6sys_clear_file (const char *filename);
extern char *lw6sys_read_file_content (const char *filename);
extern void *lw6sys_read_file_content_bin (int *filesize,
					   const char *filename);
extern int lw6sys_write_file_content (const char *filename,
				      const char *content);

/* sys-profiler.c */
extern int lw6sys_profiler_check (int verbose);

/* sys-hash.c */
extern lw6sys_hash_t *lw6sys_hash_new (lw6sys_free_func_t free_func,
				       int size);
extern void lw6sys_hash_free (lw6sys_hash_t * hash);
extern int lw6sys_hash_has_key (lw6sys_hash_t * hash, const char *key);
extern void *lw6sys_hash_get (lw6sys_hash_t * hash, const char *key);
extern void lw6sys_hash_set (lw6sys_hash_t * hash, const char *key,
			     void *value);
extern void lw6sys_hash_unset (lw6sys_hash_t * hash, const char *key);
extern lw6sys_list_t *lw6sys_hash_keys (lw6sys_hash_t * hash);
extern void lw6sys_hash_map (lw6sys_hash_t * hash,
			     lw6sys_assoc_callback_func_t func,
			     void *func_data);
extern void lw6sys_hash_sort_and_map (lw6sys_hash_t * hash,
				      lw6sys_assoc_callback_func_t func,
				      void *func_data);
extern lw6sys_hash_t *lw6sys_hash_dup (lw6sys_hash_t * hash,
				       lw6sys_dup_func_t dup_func);

/* sys-hexa.c */
extern lw6sys_hexa_serializer_t *lw6sys_hexa_serializer_new (const char
							     *hexa_string);
extern void lw6sys_hexa_serializer_free (lw6sys_hexa_serializer_t *
					 hexa_serializer);
extern void lw6sys_hexa_serializer_rewind (lw6sys_hexa_serializer_t *
					   hexa_serializer);
extern int lw6sys_hexa_serializer_eof (lw6sys_hexa_serializer_t *
				       hexa_serializer);
extern char *lw6sys_hexa_serializer_as_string (lw6sys_hexa_serializer_t *
					       hexa_serializer);
extern int lw6sys_hexa_serializer_push_int64 (lw6sys_hexa_serializer_t *
					      hexa_serializer, int64_t value);
extern int lw6sys_hexa_serializer_push_int32 (lw6sys_hexa_serializer_t *
					      hexa_serializer, int32_t value);
extern int lw6sys_hexa_serializer_push_int16 (lw6sys_hexa_serializer_t *
					      hexa_serializer, int16_t value);
extern int lw6sys_hexa_serializer_push_int8 (lw6sys_hexa_serializer_t *
					     hexa_serializer, int8_t value);
extern int lw6sys_hexa_serializer_push_float (lw6sys_hexa_serializer_t *
					      hexa_serializer, float value);
extern int lw6sys_hexa_serializer_push_str (lw6sys_hexa_serializer_t *
					    hexa_serializer,
					    const char *value);
extern int lw6sys_hexa_serializer_push_xyz (lw6sys_hexa_serializer_t *
					    hexa_serializer,
					    lw6sys_xyz_t value);
extern int lw6sys_hexa_serializer_push_whd (lw6sys_hexa_serializer_t *
					    hexa_serializer,
					    lw6sys_whd_t value);
extern int lw6sys_hexa_serializer_push_color (lw6sys_hexa_serializer_t *
					      hexa_serializer,
					      lw6sys_color_8_t value);
extern int lw6sys_hexa_serializer_pop_int64 (lw6sys_hexa_serializer_t *
					     hexa_serializer,
					     int64_t * value);
extern int lw6sys_hexa_serializer_pop_int32 (lw6sys_hexa_serializer_t *
					     hexa_serializer,
					     int32_t * value);
extern int lw6sys_hexa_serializer_pop_int16 (lw6sys_hexa_serializer_t *
					     hexa_serializer,
					     int16_t * value);
extern int lw6sys_hexa_serializer_pop_int8 (lw6sys_hexa_serializer_t *
					    hexa_serializer, int8_t * value);
extern int lw6sys_hexa_serializer_pop_float (lw6sys_hexa_serializer_t *
					     hexa_serializer, float *value);
extern int lw6sys_hexa_serializer_pop_str (lw6sys_hexa_serializer_t *
					   hexa_serializer, char **value);
extern int lw6sys_hexa_serializer_pop_xyz (lw6sys_hexa_serializer_t *
					   hexa_serializer,
					   lw6sys_xyz_t * value);
extern int lw6sys_hexa_serializer_pop_whd (lw6sys_hexa_serializer_t *
					   hexa_serializer,
					   lw6sys_whd_t * value);
extern int lw6sys_hexa_serializer_pop_color (lw6sys_hexa_serializer_t *
					     hexa_serializer,
					     lw6sys_color_8_t * value);
extern int lw6sys_hexa_str_to_buf (void *buf, int size, const char *str);
extern char *lw6sys_hexa_buf_to_str (void *buf, int size);
extern void *lw6sys_hexa_str_to_ptr (const char *str);
extern char *lw6sys_hexa_ptr_to_str (void *ptr);

/* sys-history.c */
extern void lw6sys_history_init ();
extern void lw6sys_history_register (char *msg);
extern char **lw6sys_history_get (int64_t timeout);
extern void lw6sys_history_free (char **history);

/* sys-i18n.c */
extern char *lw6sys_locale_to_utf8 (const char *string);

/* sys-id.c */
extern u_int16_t lw6sys_generate_id_16 ();
extern u_int32_t lw6sys_generate_id_32 ();
extern u_int64_t lw6sys_generate_id_64 ();
extern int lw6sys_check_id_16 (u_int16_t id_16);
extern int lw6sys_check_id_32 (u_int32_t id_32);
extern int lw6sys_check_id_64 (u_int64_t id_64);
extern int lw6sys_check_id (u_int64_t id_64);
extern char *lw6sys_id_ltoa (u_int64_t id);
extern u_int64_t lw6sys_id_atol (char *id);

/* sys-keyword.c */
extern char *lw6sys_keyword_as_key (const char *keyword);
extern char *lw6sys_keyword_as_arg (const char *keyword);
extern char *lw6sys_keyword_as_env (const char *keyword);
extern char *lw6sys_keyword_as_xml (const char *keyword);

/* sys-list.c */
extern lw6sys_list_t *lw6sys_list_new (lw6sys_free_func_t free_func);
extern void lw6sys_list_free (lw6sys_list_t * list);
extern lw6sys_list_t *lw6sys_list_next (lw6sys_list_t * list);
extern int lw6sys_list_is_empty (lw6sys_list_t * list);
extern int lw6sys_list_length (lw6sys_list_t * list);
extern void lw6sys_list_map (lw6sys_list_t * list,
			     lw6sys_list_callback_func_t func,
			     void *func_data);
extern void lw6sys_list_filter (lw6sys_list_t ** list,
				lw6sys_list_filter_func_t func,
				void *func_data);
extern void lw6sys_list_push_front (lw6sys_list_t ** list, void *data);
extern void *lw6sys_list_pop_front (lw6sys_list_t ** list);
extern void lw6sys_list_push_back (lw6sys_list_t ** list, void *data);
extern void *lw6sys_list_pop_back (lw6sys_list_t ** list);
extern void lw6sys_lifo_push (lw6sys_list_t ** list, void *data);
extern void *lw6sys_lifo_pop (lw6sys_list_t ** list);
extern void lw6sys_fifo_push (lw6sys_list_t ** list, void *data);
extern void *lw6sys_fifo_pop (lw6sys_list_t ** list);
extern lw6sys_list_t *lw6sys_list_dup (lw6sys_list_t * list,
				       lw6sys_dup_func_t dup_func);

/* sys-log.c */
extern void lw6sys_log_set_file (const char *filename);
extern void lw6sys_log_clear (const char *filename);
extern void lw6sys_log (int level_id, const char *file, int line,
			const char *fmt, ...)
  __attribute__ ((format (printf, 4, 5)));
extern void lw6sys_log_critical (const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));
extern int lw6sys_log_get_level ();
extern void lw6sys_log_set_level (int level);

/* sys-math.c */
extern void lw6sys_math_poly_wy1y2s1 (float *y, float *s, float x, float w,
				      float y1, float y2, float s1);
extern float lw6sys_math_angle_360 (int x, int y);
extern float lw6sys_math_heartbeat (int64_t x, int period, float y1,
				    float y2);
extern int lw6sys_math_blink (int64_t x, int period);

/* sys-mem.c */
#ifdef LW6_OPTIMIZE
#define LW6SYS_MALLOC(SIZE) malloc((SIZE))
#define LW6SYS_CALLOC(SIZE) calloc((SIZE),1)
#define LW6SYS_REALLOC(PTR,SIZE) realloc((PTR),(SIZE))
#define LW6SYS_FREE(PTR) free((PTR))
#else
#define LW6SYS_MALLOC(SIZE) lw6sys_malloc((SIZE),__FILE__,__LINE__)
#define LW6SYS_CALLOC(SIZE) lw6sys_calloc((SIZE),__FILE__,__LINE__)
#define LW6SYS_REALLOC(PTR,SIZE) lw6sys_realloc((void *) (PTR),(SIZE),__FILE__,__LINE__)
#define LW6SYS_FREE(PTR) lw6sys_free((void *) (PTR),__FILE__,__LINE__)
#endif

extern void *lw6sys_malloc (int size, const char *file, int line);
extern void *lw6sys_calloc (int size, const char *file, int line);
extern void *lw6sys_realloc (void *ptr, int size, const char *file, int line);
extern void lw6sys_free (void *ptr, const char *file, int line);
extern void lw6sys_free_callback (void *ptr);
extern int lw6sys_megabytes_available ();
extern int lw6sys_is_big_endian ();
extern int lw6sys_is_little_endian ();
extern int lw6sys_check_types_size ();

/* sys-mutex.c */
extern lw6sys_mutex_t *lw6sys_mutex_create ();
extern void lw6sys_mutex_destroy (lw6sys_mutex_t * mutex);
extern int lw6sys_mutex_lock (lw6sys_mutex_t * mutex);
extern int lw6sys_mutex_trylock (lw6sys_mutex_t * mutex);
extern int lw6sys_mutex_unlock (lw6sys_mutex_t * mutex);
extern int lw6sys_get_mutex_lock_count ();
extern int lw6sys_get_mutex_unlock_count ();
extern int lw6sys_check_mutex_count ();

/* sys-nop.c */
extern int lw6sys_true ();
extern int lw6sys_false ();

/* sys-openmp.c */
extern int lw6sys_openmp_get_num_procs ();

/* sys-options.c */
extern char *lw6sys_get_cwd ();
extern char *lw6sys_get_default_user_dir ();
extern char *lw6sys_get_default_config_file ();
extern char *lw6sys_get_default_log_file ();
extern char *lw6sys_get_default_prefix ();
extern char *lw6sys_get_default_mod_dir ();
extern char *lw6sys_get_default_data_dir ();
extern char *lw6sys_get_default_music_dir ();
extern char *lw6sys_get_default_music_path ();
extern char *lw6sys_get_default_map_dir ();
extern char *lw6sys_get_default_map_path ();
extern char *lw6sys_get_default_script_file ();
extern void lw6sys_options_log_defaults ();
extern char *lw6sys_get_run_dir (int argc, const char *argv[]);
extern char *lw6sys_get_user_dir (int argc, const char *argv[]);
extern char *lw6sys_get_config_file (int argc, const char *argv[]);
extern char *lw6sys_get_log_file (int argc, const char *argv[]);
extern char *lw6sys_get_prefix (int argc, const char *argv[]);
extern char *lw6sys_get_mod_dir (int argc, const char *argv[]);
extern char *lw6sys_get_data_dir (int argc, const char *argv[]);
extern char *lw6sys_get_music_dir (int argc, const char *argv[]);
extern char *lw6sys_get_music_path (int argc, const char *argv[]);
extern char *lw6sys_get_map_dir (int argc, const char *argv[]);
extern char *lw6sys_get_map_path (int argc, const char *argv[]);
extern char *lw6sys_get_script_file (int argc, const char *argv[]);
extern void lw6sys_options_log (int argc, const char *argv[]);

/* sys-path.c */
extern int lw6sys_file_exists (const char *filename);
extern int lw6sys_dir_exists (const char *dirname);
extern int lw6sys_dir_exists_with_readme (const char *dirname);
extern int lw6sys_dir_exists_with_readme_containing_text (const char *dirname,
							  const char *needle);
extern int lw6sys_create_dir (const char *dirname);
extern int lw6sys_create_dir_silent (const char *dirname);
extern char *lw6sys_path_add_slash (const char *path);
extern char *lw6sys_path_strip_slash (const char *path);
extern char *lw6sys_path_concat (const char *path1, const char *path2);
extern lw6sys_list_t *lw6sys_path_split (const char *path);
extern char *lw6sys_path_file_only (const char *path);
extern int lw6sys_path_is_relative (const char *path);
extern int lw6sys_path_is_cwd (const char *path);
extern char *lw6sys_path_parent (const char *path);
extern char *lw6sys_path_unparent (const char *path);
extern char *lw6sys_path_unparent_no_malloc (char *path);
extern lw6sys_list_t *lw6sys_dir_list (const char *dir,
				       lw6sys_dir_list_filter_func_t
				       filter_func, void *func_data, int *n);
extern lw6sys_list_t *lw6sys_path_list (const char *path,
					lw6sys_dir_list_filter_func_t
					filter_func, void *func_data, int *n);
extern char *lw6sys_find_in_dir_and_path (const char *dir, const char *path,
					  const char *file);

/* sys-print.c */
extern void lw6sys_print_xml_header (FILE * f, char *comment);
extern void lw6sys_print_xml_footer (FILE * f);

/* sys-process.c */
u_int64_t lw6sys_process_fork_and_call (lw6sys_fork_func_t func);
int lw6sys_process_kill_1_9 (u_int64_t pid);

/* sys-progress.c */
extern void lw6sys_progress_default (lw6sys_progress_t * progress,
				     float *value);
extern void lw6sys_progress_update (lw6sys_progress_t * progress, int min,
				    int max, int current);
extern void lw6sys_progress_split (lw6sys_progress_t * progress1,
				   lw6sys_progress_t * progress2,
				   lw6sys_progress_t * progress_src);
extern void lw6sys_progress_split_here (lw6sys_progress_t * progress1,
					lw6sys_progress_t * progress2,
					lw6sys_progress_t * progress_src,
					float here);
extern void lw6sys_progress_split3 (lw6sys_progress_t * progress1,
				    lw6sys_progress_t * progress2,
				    lw6sys_progress_t * progress3,
				    lw6sys_progress_t * progress_src);
extern void lw6sys_progress_split4 (lw6sys_progress_t * progress1,
				    lw6sys_progress_t * progress2,
				    lw6sys_progress_t * progress3,
				    lw6sys_progress_t * progress4,
				    lw6sys_progress_t * progress_src);
extern void lw6sys_progress_split5 (lw6sys_progress_t * progress1,
				    lw6sys_progress_t * progress2,
				    lw6sys_progress_t * progress3,
				    lw6sys_progress_t * progress4,
				    lw6sys_progress_t * progress5,
				    lw6sys_progress_t * progress_src);
extern void lw6sys_progress_begin (lw6sys_progress_t * progress);
extern void lw6sys_progress_half (lw6sys_progress_t * progress);
extern void lw6sys_progress_end (lw6sys_progress_t * progress);

/* sys-random.c */
extern u_int32_t lw6sys_random (u_int32_t range);
extern float lw6sys_random_float (float min, float max);

/* sys-sdl.c */
extern int lw6sys_sdl_register ();
extern int lw6sys_sdl_unregister ();

/* sys-serial.c */
extern void lw6sys_serialize_int64 (unsigned char *data, int64_t value);
extern int64_t lw6sys_unserialize_int64 (unsigned char *data);
extern void lw6sys_serialize_int32 (unsigned char *data, int32_t value);
extern int32_t lw6sys_unserialize_int32 (unsigned char *data);
extern void lw6sys_serialize_int16 (unsigned char *data, int16_t value);
extern int16_t lw6sys_unserialize_int16 (unsigned char *data);

/* sys-shape.c */
extern int lw6sys_shape_check_min_max_whd (lw6sys_whd_t * shape,
					   lw6sys_whd_t * min,
					   lw6sys_whd_t * max);
extern int lw6sys_shape_check_pos (lw6sys_whd_t * shape, lw6sys_xyz_t * pos);
extern int lw6sys_shape_is_same (const lw6sys_whd_t * shape_a,
				 const lw6sys_whd_t * shape_b);
extern int lw6sys_shape_is_same_xy (const lw6sys_whd_t * shape_a,
				    const lw6sys_whd_t * shape_b);
extern int lw6sys_shape_volume_whd (const lw6sys_whd_t * shape);
extern int lw6sys_shape_surface_wh (const lw6sys_whd_t * shape);

/* sys-signal.c */
extern void lw6sys_signal_custom (int trap_errors);
extern void lw6sys_signal_default ();
extern void lw6sys_signal_term_handler (int signum);
extern void lw6sys_signal_int_handler (int signum);
extern void lw6sys_signal_hup_handler (int signum);
extern void lw6sys_signal_segv_handler (int signum);
extern void lw6sys_signal_fpe_handler (int signum);
extern void lw6sys_signal_send_quit ();
extern int lw6sys_signal_poll_quit ();

/* sys-sort.c */
extern int lw6sys_sort_int_callback (lw6sys_list_t ** list_a,
				     lw6sys_list_t ** list_b);
extern int lw6sys_sort_int_desc_callback (lw6sys_list_t ** list_a,
					  lw6sys_list_t ** list_b);
extern int lw6sys_sort_float_callback (lw6sys_list_t ** list_a,
				       lw6sys_list_t ** list_b);
extern int lw6sys_sort_float_desc_callback (lw6sys_list_t ** list_a,
					    lw6sys_list_t ** list_b);
extern int lw6sys_sort_str_callback (lw6sys_list_t ** list_a,
				     lw6sys_list_t ** list_b);
extern int lw6sys_sort_str_desc_callback (lw6sys_list_t ** list_a,
					  lw6sys_list_t ** list_b);
extern void lw6sys_sort (lw6sys_list_t ** list,
			 lw6sys_sort_callback_func_t sort_func);

/* sys-spinlock.c */
extern lw6sys_spinlock_t *lw6sys_spinlock_create ();
extern void lw6sys_spinlock_destroy (lw6sys_spinlock_t * spinlock);
extern int lw6sys_spinlock_lock (lw6sys_spinlock_t * spinlock);
extern int lw6sys_spinlock_trylock (lw6sys_spinlock_t * spinlock);
extern int lw6sys_spinlock_unlock (lw6sys_spinlock_t * spinlock);

/* sys-str.c */
extern char *lw6sys_str_copy (const char *src);
extern char *lw6sys_str_concat (const char *str1, const char *str2);
extern char *lw6sys_new_sprintf (const char *fmt, ...)
  __attribute__ ((format (printf, 1, 2)));
extern int lw6sys_buf_sprintf (char *buf, int len, const char *fmt, ...)
  __attribute__ ((format (printf, 3, 4)));
extern int lw6sys_str_is_blank (const char *str);
extern int lw6sys_str_is_null_or_empty (const char *str);
extern const char *lw6sys_str_empty_if_null (const char *str);
extern int lw6sys_str_is_same (const char *str_a, const char *str_b);
extern int lw6sys_str_is_same_no_case (const char *str_a, const char *str_b);
extern int lw6sys_str_starts_with (const char *str, const char *beginning);
extern int lw6sys_str_starts_with_no_case (const char *str,
					   const char *beginning);
extern int lw6sys_skip_blanks (char **str_ptr);
extern void lw6sys_str_cleanup (char *str);
extern void lw6sys_str_cleanup_ascii7 (char *str);
extern char *lw6sys_str_reformat (const char *str, const char *prefix,
				  int nb_columns);
extern void lw6sys_str_reformat_this (char *str, int nb_columns);
extern char *lw6sys_eol ();
extern lw6sys_list_t *lw6sys_str_split (const char *str, char c);
extern lw6sys_list_t *lw6sys_str_split_no_0 (const char *str, char c);
extern lw6sys_list_t *lw6sys_str_split_config_item (const char *str);
extern char *lw6sys_str_join (lw6sys_list_t * list, const char *glue);
extern void lw6sys_str_toupper (char *str);
extern void lw6sys_str_tolower (char *str);
extern void lw6sys_str_truncate (char *str, int len);
extern char *lw6sys_str_random (int len);
extern char *lw6sys_str_random_words (int len);
extern char *lw6sys_str_random_word (int len);
extern int lw6sys_str_is_bin (const char *buf, int len);

/* sys-stream.c */
extern char *lw6sys_stream_file_to_str (FILE * f);
extern void lw6sys_stream_str_to_file (FILE * f, char *str);

/* sys-test.c */
extern int lw6sys_test_exec (int argc, const char *argv[], int mode);
extern int lw6sys_test (int mode);

/* sys-testandset.s */
extern int lw6sys_test_and_set (int *spinlock);

/* sys-thread.c */
extern lw6sys_thread_handler_t
  * lw6sys_thread_create (lw6sys_thread_callback_func_t callback_func,
			  lw6sys_thread_callback_func_t callback_join,
			  void *callback_data);
extern int lw6sys_thread_is_callback_done (lw6sys_thread_handler_t *
					   thread_handler);
extern int lw6sys_thread_get_id (lw6sys_thread_handler_t * thread_handler);
extern void *lw6sys_thread_get_data (lw6sys_thread_handler_t *
				     thread_handler);
extern void lw6sys_thread_join (lw6sys_thread_handler_t * thread_handler);
extern int lw6sys_get_thread_create_count ();
extern int lw6sys_get_thread_join_count ();
extern int lw6sys_check_thread_count ();

/* sys-time.c */
extern int64_t lw6sys_get_timestamp ();
extern int64_t lw6sys_get_uptime ();
extern int32_t lw6sys_get_cycle ();
extern void lw6sys_timer_update (int64_t * timestamp, int64_t * uptime,
				 int32_t * cycle);
extern void lw6sys_sleep (float seconds);
extern void lw6sys_delay (int msec);
extern void lw6sys_idle ();
extern void lw6sys_snooze ();
extern void lw6sys_time_init ();
extern char *lw6sys_date_rfc1123 (int seconds_from_now);
extern char *lw6sys_date_clf ();
extern char *lw6sys_readable_uptime (int64_t timestamp_delta);

/* sys-url.c */
extern char *lw6sys_url_http_from_ip_port (const char *ip, int port);
extern lw6sys_url_t *lw6sys_url_parse (const char *url);
extern void lw6sys_url_free (lw6sys_url_t * url);
extern char *lw6sys_url_canonize (const char *url);
extern int lw6sys_url_is_canonized (const char *url);

/* sys-vthread.c */
extern int lw6sys_vthread_run (lw6sys_thread_callback_func_t callback_func,
			       lw6sys_thread_callback_func_t callback_join,
			       void *callback_data);
extern int lw6sys_vthread_is_running ();
extern int lw6sys_vthread_create (lw6sys_thread_callback_func_t callback_func,
				  lw6sys_thread_callback_func_t callback_join,
				  void *callback_data);
extern void lw6sys_vthread_join ();


/* inline utils */
static inline int32_t
lw6sys_imin (int32_t a, int32_t b)
{
  return (a < b) ? a : b;
}

static inline int32_t
lw6sys_imax (int32_t a, int32_t b)
{
  return (a > b) ? a : b;
}

static inline float
lw6sys_fmin (float a, float b)
{
  return (a < b) ? a : b;
}

static inline float
lw6sys_fmax (float a, float b)
{
  return (a > b) ? a : b;
}

static inline int64_t
lw6sys_llmin (int64_t a, int64_t b)
{
  return (a < b) ? a : b;
}

static inline int64_t
lw6sys_llmax (int64_t a, int64_t b)
{
  return (a > b) ? a : b;
}

static inline double
lw6sys_dmin (double a, double b)
{
  return (a < b) ? a : b;
}

static inline double
lw6sys_dmax (double a, double b)
{
  return (a > b) ? a : b;
}

#endif
