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

#include "../cli.h"
#include "mod-http-internal.h"

/*
 * Inspired from example getinmemory.c from libcurl documentation
 */

typedef struct _memory_struct_s
{
  char *memory;
  size_t size;
} _memory_struct_t;

static void *
_my_realloc (void *ptr, size_t size)
{
  /* There might be a realloc() out there that doesn't like reallocing
     NULL pointers, so we take care of it here */
  if (ptr)
    return LW6SYS_REALLOC (ptr, size);
  else
    return LW6SYS_MALLOC (size);
}

static size_t
_write_memory_callback (void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  _memory_struct_t *mem = (_memory_struct_t *) data;

  mem->memory = _my_realloc (mem->memory, mem->size + realsize + 1);
  if (mem->memory)
    {
      memcpy (&(mem->memory[mem->size]), ptr, realsize);
      mem->size += realsize;
      mem->memory[mem->size] = 0;
    }
  return realsize;
}

static void
_print_error (char *function, CURLcode res)
{
  lw6sys_log (LW6SYS_LOG_INFO,
	      _("call to curl function \"%s\" failed with code %d \"%s\""),
	      function, res, curl_easy_strerror (res));
}

char *
_mod_http_get (_http_context_t * http_context, char *url, char *password)
{
  char *ret = NULL;
  CURL *curl_handle;
  CURLcode res;
  _memory_struct_t chunk;
  char *authorization = NULL;
  int64_t origin = lw6sys_get_timestamp ();

  chunk.memory = NULL;		/* we expect realloc(NULL, size) to work */
  chunk.size = 0;		/* no data at this point */

  lw6sys_log (LW6SYS_LOG_DEBUG, _("GET \"%s\""), url);
  /*
   * We use this lock because CURL might use gethostbyname internally.
   * Not locking gives segfault error, typically:
   * "0x0077502f in Curl_getaddrinfo_ex () from /usr/lib/libcurl.so.4"
   * Note that we could lock *only* the curl_easy_perform function,
   * but in practice we would barely gain any time, and the safety
   * of being sure all CURL functions are serialized has some value.
   */
  if (lw6net_dns_lock ())
    {
      /*
       * Check if timeout is OK for if we had many locks, we can have
       * a timeout between now and the end of the call
       */
      if (_mod_http_timeout_ok (http_context, origin))
	{
	  /* init the curl session */
	  curl_handle = curl_easy_init ();
	  if (curl_handle)
	    {
	      /*
	       * Complicated, not sure this is 100% mandatory, but
	       * reading http://horstr.blogspot.com/2008/04/on-libcurl-openssl-and-thread-safety.html
	       * I came to the conclusion it might not harm
	       */
	      res = curl_easy_setopt (curl_handle, CURLOPT_NOSIGNAL, 1);
	      if (res == CURLE_OK)
		{
		  /* specify URL to get */
		  res = curl_easy_setopt (curl_handle, CURLOPT_URL, url);
		  if (res == CURLE_OK)
		    {
		      res =
			curl_easy_setopt (curl_handle, CURLOPT_WRITEFUNCTION,
					  _write_memory_callback);
		      if (res == CURLE_OK)
			{
			  /* we pass our 'chunk' struct to the callback function */
			  res =
			    curl_easy_setopt (curl_handle, CURLOPT_WRITEDATA,
					      (void *) &chunk);
			  if (res == CURLE_OK)
			    {
			      /*
			       * Don't waist a full minute when
			       * firewall is in DROP mode
			       */
			      res =
				curl_easy_setopt (curl_handle,
						  CURLOPT_CONNECTTIMEOUT,
						  http_context->data.
						  consts.connect_timeout);
			      if (res == CURLE_OK)
				{
				  /* some servers don't like requests that are made without a user-agent
				     field, so we provide one */
				  res =
				    curl_easy_setopt (curl_handle,
						      CURLOPT_USERAGENT,
						      lw6sys_build_get_package_tarname
						      ());
				  if (res == CURLE_OK)
				    {
				      if (password)
					{
					  authorization =
					    lw6sys_new_sprintf ("%s:%s",
								lw6sys_build_get_package_tarname
								(), password);
					  if (authorization)
					    {
					      lw6sys_log (LW6SYS_LOG_DEBUG,
							  _
							  ("using authorization \"%s\""),
							  authorization);
					      /* tell libcurl we can use "any" auth, which lets the lib pick one, but it
					         also costs one extra round-trip and possibly sending of all the PUT
					         data twice!!! */
					      res =
						curl_easy_setopt (curl_handle,
								  CURLOPT_HTTPAUTH,
								  (long)
								  CURLAUTH_ANY);
					      if (res != CURLE_OK)
						{
						  _print_error
						    ("curl_easy_setopt(CURLOPT_HTTPAUTH)",
						     res);
						}
					      /* set user name and password for the authentication */
					      res =
						curl_easy_setopt (curl_handle,
								  CURLOPT_USERPWD,
								  authorization);
					      if (res != CURLE_OK)
						{
						  _print_error
						    ("curl_easy_setopt(CURLOPT_USERPWD)",
						     res);
						}
					      LW6SYS_FREE (authorization);
					    }
					}
				      /* get it! */
				      res = curl_easy_perform (curl_handle);
				      if (res == CURLE_OK)
					{
					  /* should be OK */
					}
				      else
					{
					  _print_error ("curl_easy_perform",
							res);
					}
				    }
				  else
				    {
				      _print_error
					("curl_easy_setopt(CURLOPT_USERAGENT)",
					 res);
				    }
				}
			      else
				{
				  _print_error
				    ("curl_easy_setopt(CURLOPT_CONNECTTIMEOUT)",
				     res);
				}
			    }
			  else
			    {
			      _print_error
				("curl_easy_setopt(CURLOPT_WRITEDATA)", res);
			    }
			}
		      else
			{
			  _print_error
			    ("curl_easy_setopt(CURLOPT_WRITEFUNCTION)", res);
			}
		    }
		  else
		    {
		      _print_error ("curl_easy_setopt(CURLOPT_URL)", res);
		    }
		}
	      else
		{
		  _print_error ("curl_easy_setopt(CURLOPT_NOSIGNAL)", res);
		}
	      /* cleanup curl stuff */
	      curl_easy_cleanup (curl_handle);
	    }
	  else
	    {
	      lw6sys_log (LW6SYS_LOG_WARNING,
			  _("unable to initialize CURL handle"));
	    }

	  if (chunk.memory)
	    {
	      ret = chunk.memory;
	      lw6sys_log (LW6SYS_LOG_DEBUG, _("response=\"%s\""), ret);
	    }
	}
      lw6net_dns_unlock ();
    }

  return ret;
}
