/*
  Liquid War 6 is a unique multiplayer wargame.
  Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011  Christian Mauduit <ufoot@ufoot.org>

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

#include "ldr-png.h"

#include "ldr.h"
#include "ldr-internal.h"

static int
read_png (lw6map_layer_t * layer, _lw6ldr_image_bw_t * image,
	  lw6ldr_resampler_t * resampler, lw6sys_progress_t * progress)
{
  int ret = 0;

  layer->shape.w = resampler->target_w;
  layer->shape.h = resampler->target_h;
  layer->shape.d = 1;		// allways 1
  layer->data =
    (unsigned char *) LW6SYS_MALLOC (layer->shape.w * layer->shape.h *
				     sizeof (unsigned char *));

  if (layer->data)
    {
      int row, col, row2, col2;
      unsigned int value;

      for (row = 0; row < layer->shape.h; ++row)
	{
	  lw6sys_progress_update (progress, 0, layer->shape.h, row);
	  for (col = 0; col < layer->shape.w; ++col)
	    {
	      lw6ldr_resampler_target2source (resampler, &col2, &row2,
					      col, row);

	      value = image->data[row2][col2 * image->step];
	      /*
	       * For now we do not handle layer the full way. There's
	       * a big TODO here, one could read in another file (say
	       * an XML file) a parameter that would state "maximum layer
	       * is 5" and maybe even the various thresholds for the
	       * different levels. For now using layer 0 or 1 is just like
	       * in Liquid War 5, we have flat levels, will be fine for
	       * a some time anyway.
	       */
	      value = (value > 127) ? 1 : 0;
	      lw6map_layer_set (layer, col, row, value);
	    }
	}

      ret = 1;
    }
  else
    {
      lw6sys_log (LW6SYS_LOG_WARNING,
		  _x_ ("unable to allocate memory for layer"));
    }

  return ret;
}

int
lw6ldr_layer_read_first (lw6map_layer_t * layer, char *filename,
			 lw6map_param_t * param, lw6ldr_hints_t * hints,
			 int display_w, int display_h, float target_ratio,
			 int bench_value, int magic_number,
			 int expected_depth, lw6sys_progress_t * progress)
{
  int ret = 0;
  lw6ldr_resampler_t resampler;
  _lw6ldr_image_bw_t image;
  lw6sys_progress_t progress1;
  lw6sys_progress_t progress2;
  float gray_level;

  lw6sys_progress_split (&progress1, &progress2, progress);

  lw6map_layer_clear (layer);
  memset (&image, 0, sizeof (_lw6ldr_image_bw_t));
  if (_lw6ldr_bw_read (&image, filename, &progress1))
    {
      if (target_ratio <= 0.0f)
	{
	  target_ratio = ((float) image.w) / ((float) image.h);
	}
      gray_level = _lw6ldr_bw_gray_level (&image);
      lw6ldr_resampler_init (&resampler, param, hints, image.w, image.h,
			     display_w, display_h, target_ratio, bench_value,
			     magic_number, expected_depth, gray_level);
      ret = read_png (layer, &image, &resampler, &progress2);

      _lw6ldr_bw_clear (&image);
    }

  if (!ret)
    {
      lw6map_layer_clear (layer);
    }

  return ret;
}

int
lw6ldr_layer_read_next (lw6map_layer_t * layer, char *filename,
			int target_w, int target_h)
{
  int ret = 0;
  lw6ldr_resampler_t resampler;
  _lw6ldr_image_bw_t image;

  lw6map_layer_clear (layer);
  memset (&image, 0, sizeof (_lw6ldr_image_bw_t));
  if (_lw6ldr_bw_read (&image, filename, NULL))
    {
      lw6ldr_resampler_force (&resampler, image.w, image.h, target_w,
			      target_h);
      ret = read_png (layer, &image, &resampler, NULL);

      _lw6ldr_bw_clear (&image);
    }

  if (!ret)
    {
      lw6map_layer_clear (layer);
    }

  return ret;
}
