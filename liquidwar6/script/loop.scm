;; Liquid War 6 is a unique multiplayer wargame.
;; Copyright (C)  2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014  Christian Mauduit <ufoot@ufoot.org>
;;
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;;
;;
;; Liquid War 6 homepage : http://www.gnu.org/software/liquidwar6/
;; Contact author        : ufoot@ufoot.org

(define %lw6-frames-per-sec 0)

(define lw6-game-loop
  (lambda ()
    (begin
      (lw6-log-info (_ "begin main game loop"))
      (let* (
	     (dsp (lw6-get-game-global "dsp"))
	     (uptime-0 (c-lw6sys-get-uptime))
	     (command-count 0)
	     (io-count 0)
	    )
	(while (not (c-lw6sys-signal-poll-quit))
	       (let* (
		     (ticks (- (c-lw6sys-get-uptime) uptime-0))
		     (command-incr (quotient 1000 (lw6-config-get-number lw6def-commands-per-sec)))
		     (io-incr (quotient 1000 (lw6-config-get-number lw6def-io-per-sec)))
		     )
		 (begin
					; First step, process basic I/O
					; this does not happen so often,
					; to avoid wasting events (which
					; can be expensive over the network)
					; and prevent the user interface
					; from being "too fast"
		   (if (< io-count ticks)
		       (begin
			 (lw6-io)
			 (set! io-count (max (+ io-count io-incr)
					     (- ticks io-incr)))
			 )
		       )

					; generate commands
		   (if (< command-count ticks)
		       (begin
			 (lw6-command #t)
					;(lw6-log-notice (format #f "~a/~a" command-count ticks))
			 (set! command-count (max (+ command-count command-incr)
						  (- ticks command-incr)))
			 )
		       (begin
			 (lw6-command #f)
			 )
		       )
					; note : display-update will automatically
					; and go idle if needed, to avoid this
					; main thread to eat up 100% of ressources.
		   (lw6-display-update)
		   )
		 )))
      )))



