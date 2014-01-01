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

(define lw6-local-game
  (lambda ()
    (begin
      (lw6-local-game-prepare)
      (lw6-set-game-global! "logic-func" lw6-logic-game)
      (lw6-set-game-global! "display-func" lw6-display-game)
      )
    )
  )

(define lw6-local-game-reset-t0
  (lambda ()
    (lw6-set-game-global! "t0" (c-lw6sys-get-timestamp))
    )
  )

(define lw6-local-game-prepare
  (lambda ()
    (begin
      (lw6-update-map-source-from-chosen)
      (let* (
	     (map-source (lw6-get-game-global "map-source"))
	     (game-instance (lw6-prepare-map map-source))
	     )
	(begin
	  (lw6-set-game-global! "game-instance" game-instance)
	  (lw6-local-game-reset-t0)
	  )
	)
      (lw6-get-game-global "game-instance")
      )
    )
  )
