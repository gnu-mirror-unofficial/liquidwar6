;Liquid War 6 is a unique multiplayer wargame.
;Copyright (C)  2005, 2006, 2007, 2008, 2009  Christian Mauduit <ufoot@ufoot.org>
;
;This program is free software; you can redistribute it and/or modify
;it under the terms of the GNU General Public License as published by
;the Free Software Foundation, either version 3 of the License, or
;(at your option) any later version.
;
;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;
;You should have received a copy of the GNU General Public License
;along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
;
;Liquid War 6 homepage : http://www.gnu.org/software/liquidwar6/
;Contact author        : ufoot@ufoot.org

;Generated automatically by def-update.py

(define lw6def-about "about")
(define lw6def-ambiance-exclude "ambiance-exclude")
(define lw6def-ambiance-file "ambiance-file")
(define lw6def-ambiance-filter "ambiance-filter")
(define lw6def-animation-density "animation-density")
(define lw6def-animation-speed "animation-speed")
(define lw6def-audit "audit")
(define lw6def-background-color-auto "background-color-auto")
(define lw6def-background-color-root-bg "background-color-root-bg")
(define lw6def-background-color-root-fg "background-color-root-fg")
(define lw6def-background-color-stuff-bg "background-color-stuff-bg")
(define lw6def-background-color-stuff-fg "background-color-stuff-fg")
(define lw6def-background-style "background-style")
(define lw6def-base64-decode "base64-decode")
(define lw6def-base64-encode "base64-encode")
(define lw6def-bench "bench")
(define lw6def-bench-value "bench-value")
(define lw6def-bin-id "bin-id")
(define lw6def-bind-ip "bind-ip")
(define lw6def-bind-port "bind-port")
(define lw6def-blink-cursor "blink-cursor")
(define lw6def-boost-power "boost-power")
(define lw6def-bot-iq "bot-iq")
(define lw6def-bot-speed "bot-speed")
(define lw6def-broadcast "broadcast")
(define lw6def-c-gettext "c-gettext")
(define lw6def-c-lw6-exit "c-lw6-exit")
(define lw6def-c-lw6-release "c-lw6-release")
(define lw6def-c-lw6bot-get-backends "c-lw6bot-get-backends")
(define lw6def-c-lw6bot-new "c-lw6bot-new")
(define lw6def-c-lw6bot-next-move "c-lw6bot-next-move")
(define lw6def-c-lw6cfg-defaults "c-lw6cfg-defaults")
(define lw6def-c-lw6cfg-get-option "c-lw6cfg-get-option")
(define lw6def-c-lw6cfg-init "c-lw6cfg-init")
(define lw6def-c-lw6cfg-load "c-lw6cfg-load")
(define lw6def-c-lw6cfg-option-exists "c-lw6cfg-option-exists")
(define lw6def-c-lw6cfg-quit "c-lw6cfg-quit")
(define lw6def-c-lw6cfg-save "c-lw6cfg-save")
(define lw6def-c-lw6cfg-set-option "c-lw6cfg-set-option")
(define lw6def-c-lw6cfg-unified-get-log-file "c-lw6cfg-unified-get-log-file")
(define lw6def-c-lw6cfg-unified-get-map-path "c-lw6cfg-unified-get-map-path")
(define lw6def-c-lw6cfg-unified-get-music-path "c-lw6cfg-unified-get-music-path")
(define lw6def-c-lw6cfg-unified-get-user-dir "c-lw6cfg-unified-get-user-dir")
(define lw6def-c-lw6cli-get-backends "c-lw6cli-get-backends")
(define lw6def-c-lw6cns-init "c-lw6cns-init")
(define lw6def-c-lw6cns-poll "c-lw6cns-poll")
(define lw6def-c-lw6cns-quit "c-lw6cns-quit")
(define lw6def-c-lw6cns-support "c-lw6cns-support")
(define lw6def-c-lw6dsp-get-average-fps "c-lw6dsp-get-average-fps")
(define lw6def-c-lw6dsp-get-fullscreen-modes "c-lw6dsp-get-fullscreen-modes")
(define lw6def-c-lw6dsp-get-instant-fps "c-lw6dsp-get-instant-fps")
(define lw6def-c-lw6dsp-get-last-frame-rendering-time "c-lw6dsp-get-last-frame-rendering-time")
(define lw6def-c-lw6dsp-get-nb-frames "c-lw6dsp-get-nb-frames")
(define lw6def-c-lw6dsp-get-video-mode "c-lw6dsp-get-video-mode")
(define lw6def-c-lw6dsp-new "c-lw6dsp-new")
(define lw6def-c-lw6dsp-release "c-lw6dsp-release")
(define lw6def-c-lw6dsp-update "c-lw6dsp-update")
(define lw6def-c-lw6gfx-get-backends "c-lw6gfx-get-backends")
(define lw6def-c-lw6gui-default-look "c-lw6gui-default-look")
(define lw6def-c-lw6gui-input-reset "c-lw6gui-input-reset")
(define lw6def-c-lw6gui-joystick1-get-move-pad "c-lw6gui-joystick1-get-move-pad")
(define lw6def-c-lw6gui-joystick1-pop-button-a "c-lw6gui-joystick1-pop-button-a")
(define lw6def-c-lw6gui-joystick1-pop-button-b "c-lw6gui-joystick1-pop-button-b")
(define lw6def-c-lw6gui-joystick1-pop-button-c "c-lw6gui-joystick1-pop-button-c")
(define lw6def-c-lw6gui-joystick1-pop-button-d "c-lw6gui-joystick1-pop-button-d")
(define lw6def-c-lw6gui-joystick1-pop-button-down "c-lw6gui-joystick1-pop-button-down")
(define lw6def-c-lw6gui-joystick1-pop-button-left "c-lw6gui-joystick1-pop-button-left")
(define lw6def-c-lw6gui-joystick1-pop-button-right "c-lw6gui-joystick1-pop-button-right")
(define lw6def-c-lw6gui-joystick1-pop-button-up "c-lw6gui-joystick1-pop-button-up")
(define lw6def-c-lw6gui-joystick2-get-move-pad "c-lw6gui-joystick2-get-move-pad")
(define lw6def-c-lw6gui-joystick2-pop-button-a "c-lw6gui-joystick2-pop-button-a")
(define lw6def-c-lw6gui-joystick2-pop-button-b "c-lw6gui-joystick2-pop-button-b")
(define lw6def-c-lw6gui-joystick2-pop-button-c "c-lw6gui-joystick2-pop-button-c")
(define lw6def-c-lw6gui-joystick2-pop-button-d "c-lw6gui-joystick2-pop-button-d")
(define lw6def-c-lw6gui-joystick2-pop-button-down "c-lw6gui-joystick2-pop-button-down")
(define lw6def-c-lw6gui-joystick2-pop-button-left "c-lw6gui-joystick2-pop-button-left")
(define lw6def-c-lw6gui-joystick2-pop-button-right "c-lw6gui-joystick2-pop-button-right")
(define lw6def-c-lw6gui-joystick2-pop-button-up "c-lw6gui-joystick2-pop-button-up")
(define lw6def-c-lw6gui-keyboard-get-move-pad "c-lw6gui-keyboard-get-move-pad")
(define lw6def-c-lw6gui-keyboard-is-pressed "c-lw6gui-keyboard-is-pressed")
(define lw6def-c-lw6gui-keyboard-pop-key-down "c-lw6gui-keyboard-pop-key-down")
(define lw6def-c-lw6gui-keyboard-pop-key-enter "c-lw6gui-keyboard-pop-key-enter")
(define lw6def-c-lw6gui-keyboard-pop-key-esc "c-lw6gui-keyboard-pop-key-esc")
(define lw6def-c-lw6gui-keyboard-pop-key-left "c-lw6gui-keyboard-pop-key-left")
(define lw6def-c-lw6gui-keyboard-pop-key-pgdown "c-lw6gui-keyboard-pop-key-pgdown")
(define lw6def-c-lw6gui-keyboard-pop-key-pgup "c-lw6gui-keyboard-pop-key-pgup")
(define lw6def-c-lw6gui-keyboard-pop-key-right "c-lw6gui-keyboard-pop-key-right")
(define lw6def-c-lw6gui-keyboard-pop-key-up "c-lw6gui-keyboard-pop-key-up")
(define lw6def-c-lw6gui-look-get "c-lw6gui-look-get")
(define lw6def-c-lw6gui-look-set "c-lw6gui-look-set")
(define lw6def-c-lw6gui-look-zoom-in "c-lw6gui-look-zoom-in")
(define lw6def-c-lw6gui-look-zoom-out "c-lw6gui-look-zoom-out")
(define lw6def-c-lw6gui-menu-append "c-lw6gui-menu-append")
(define lw6def-c-lw6gui-menu-enable-esc "c-lw6gui-menu-enable-esc")
(define lw6def-c-lw6gui-menu-new "c-lw6gui-menu-new")
(define lw6def-c-lw6gui-menu-scroll-down "c-lw6gui-menu-scroll-down")
(define lw6def-c-lw6gui-menu-scroll-up "c-lw6gui-menu-scroll-up")
(define lw6def-c-lw6gui-menu-select "c-lw6gui-menu-select")
(define lw6def-c-lw6gui-menu-select-esc "c-lw6gui-menu-select-esc")
(define lw6def-c-lw6gui-menu-sync "c-lw6gui-menu-sync")
(define lw6def-c-lw6gui-mouse-get-state "c-lw6gui-mouse-get-state")
(define lw6def-c-lw6gui-mouse-poll-move "c-lw6gui-mouse-poll-move")
(define lw6def-c-lw6gui-mouse-pop-button-left "c-lw6gui-mouse-pop-button-left")
(define lw6def-c-lw6gui-mouse-pop-button-right "c-lw6gui-mouse-pop-button-right")
(define lw6def-c-lw6gui-mouse-pop-wheel-down "c-lw6gui-mouse-pop-wheel-down")
(define lw6def-c-lw6gui-mouse-pop-wheel-up "c-lw6gui-mouse-pop-wheel-up")
(define lw6def-c-lw6hlp-get-default-value "c-lw6hlp-get-default-value")
(define lw6def-c-lw6hlp-list "c-lw6hlp-list")
(define lw6def-c-lw6hlp-list-advanced "c-lw6hlp-list-advanced")
(define lw6def-c-lw6hlp-list-aliases "c-lw6hlp-list-aliases")
(define lw6def-c-lw6hlp-list-doc "c-lw6hlp-list-doc")
(define lw6def-c-lw6hlp-list-funcs "c-lw6hlp-list-funcs")
(define lw6def-c-lw6hlp-list-graphics "c-lw6hlp-list-graphics")
(define lw6def-c-lw6hlp-list-hooks "c-lw6hlp-list-hooks")
(define lw6def-c-lw6hlp-list-input "c-lw6hlp-list-input")
(define lw6def-c-lw6hlp-list-map "c-lw6hlp-list-map")
(define lw6def-c-lw6hlp-list-map-hints "c-lw6hlp-list-map-hints")
(define lw6def-c-lw6hlp-list-map-rules "c-lw6hlp-list-map-rules")
(define lw6def-c-lw6hlp-list-map-style "c-lw6hlp-list-map-style")
(define lw6def-c-lw6hlp-list-network "c-lw6hlp-list-network")
(define lw6def-c-lw6hlp-list-path "c-lw6hlp-list-path")
(define lw6def-c-lw6hlp-list-players "c-lw6hlp-list-players")
(define lw6def-c-lw6hlp-list-quick "c-lw6hlp-list-quick")
(define lw6def-c-lw6hlp-list-show "c-lw6hlp-list-show")
(define lw6def-c-lw6hlp-list-sound "c-lw6hlp-list-sound")
(define lw6def-c-lw6ker-add-cursor "c-lw6ker-add-cursor")
(define lw6def-c-lw6ker-build-game-state "c-lw6ker-build-game-state")
(define lw6def-c-lw6ker-build-game-struct "c-lw6ker-build-game-struct")
(define lw6def-c-lw6ker-cursor-exists "c-lw6ker-cursor-exists")
(define lw6def-c-lw6ker-do-round "c-lw6ker-do-round")
(define lw6def-c-lw6ker-dup-game-state "c-lw6ker-dup-game-state")
(define lw6def-c-lw6ker-game-state-checksum "c-lw6ker-game-state-checksum")
(define lw6def-c-lw6ker-game-struct-checksum "c-lw6ker-game-struct-checksum")
(define lw6def-c-lw6ker-get-cursor "c-lw6ker-get-cursor")
(define lw6def-c-lw6ker-get-moves "c-lw6ker-get-moves")
(define lw6def-c-lw6ker-get-rounds "c-lw6ker-get-rounds")
(define lw6def-c-lw6ker-get-spreads "c-lw6ker-get-spreads")
(define lw6def-c-lw6ker-is-over "c-lw6ker-is-over")
(define lw6def-c-lw6ker-node-exists "c-lw6ker-node-exists")
(define lw6def-c-lw6ker-register-node "c-lw6ker-register-node")
(define lw6def-c-lw6ker-remove-cursor "c-lw6ker-remove-cursor")
(define lw6def-c-lw6ker-set-cursor "c-lw6ker-set-cursor")
(define lw6def-c-lw6ker-sync-game-state "c-lw6ker-sync-game-state")
(define lw6def-c-lw6ker-unregister-node "c-lw6ker-unregister-node")
(define lw6def-c-lw6ldr-get-entries "c-lw6ldr-get-entries")
(define lw6def-c-lw6ldr-hints-get-default "c-lw6ldr-hints-get-default")
(define lw6def-c-lw6ldr-print-examples "c-lw6ldr-print-examples")
(define lw6def-c-lw6ldr-read "c-lw6ldr-read")
(define lw6def-c-lw6ldr-read-relative "c-lw6ldr-read-relative")
(define lw6def-c-lw6map-get-look "c-lw6map-get-look")
(define lw6def-c-lw6map-get-music-dir "c-lw6map-get-music-dir")
(define lw6def-c-lw6map-rules-get-default "c-lw6map-rules-get-default")
(define lw6def-c-lw6map-rules-get-int "c-lw6map-rules-get-int")
(define lw6def-c-lw6map-rules-get-max "c-lw6map-rules-get-max")
(define lw6def-c-lw6map-rules-get-min "c-lw6map-rules-get-min")
(define lw6def-c-lw6map-style-get-default "c-lw6map-style-get-default")
(define lw6def-c-lw6map-team-color-index-to-key "c-lw6map-team-color-index-to-key")
(define lw6def-c-lw6map-team-color-key-to-index "c-lw6map-team-color-key-to-index")
(define lw6def-c-lw6net-init "c-lw6net-init")
(define lw6def-c-lw6net-quit "c-lw6net-quit")
(define lw6def-c-lw6p2p-db-default-name "c-lw6p2p-db-default-name")
(define lw6def-c-lw6p2p-db-new "c-lw6p2p-db-new")
(define lw6def-c-lw6p2p-db-reset "c-lw6p2p-db-reset")
(define lw6def-c-lw6p2p-node-close "c-lw6p2p-node-close")
(define lw6def-c-lw6p2p-node-get-id "c-lw6p2p-node-get-id")
(define lw6def-c-lw6p2p-node-new "c-lw6p2p-node-new")
(define lw6def-c-lw6p2p-node-poll "c-lw6p2p-node-poll")
(define lw6def-c-lw6pil-bench "c-lw6pil-bench")
(define lw6def-c-lw6pil-build-pilot "c-lw6pil-build-pilot")
(define lw6def-c-lw6pil-calibrate "c-lw6pil-calibrate")
(define lw6def-c-lw6pil-commit "c-lw6pil-commit")
(define lw6def-c-lw6pil-execute-command "c-lw6pil-execute-command")
(define lw6def-c-lw6pil-fix-coords "c-lw6pil-fix-coords")
(define lw6def-c-lw6pil-get-last-commit-round "c-lw6pil-get-last-commit-round")
(define lw6def-c-lw6pil-get-max-round "c-lw6pil-get-max-round")
(define lw6def-c-lw6pil-get-next-round "c-lw6pil-get-next-round")
(define lw6def-c-lw6pil-get-reference-current-round "c-lw6pil-get-reference-current-round")
(define lw6def-c-lw6pil-get-reference-target-round "c-lw6pil-get-reference-target-round")
(define lw6def-c-lw6pil-is-over "c-lw6pil-is-over")
(define lw6def-c-lw6pil-local-command "c-lw6pil-local-command")
(define lw6def-c-lw6pil-local-cursors-set-main "c-lw6pil-local-cursors-set-main")
(define lw6def-c-lw6pil-local-cursors-set-mouse-controlled "c-lw6pil-local-cursors-set-mouse-controlled")
(define lw6def-c-lw6pil-make-backup "c-lw6pil-make-backup")
(define lw6def-c-lw6pil-send-command "c-lw6pil-send-command")
(define lw6def-c-lw6pil-slow-down "c-lw6pil-slow-down")
(define lw6def-c-lw6pil-speed-up "c-lw6pil-speed-up")
(define lw6def-c-lw6pil-sync-from-backup "c-lw6pil-sync-from-backup")
(define lw6def-c-lw6pil-sync-from-draft "c-lw6pil-sync-from-draft")
(define lw6def-c-lw6pil-sync-from-reference "c-lw6pil-sync-from-reference")
(define lw6def-c-lw6snd-get-backends "c-lw6snd-get-backends")
(define lw6def-c-lw6snd-is-music-file "c-lw6snd-is-music-file")
(define lw6def-c-lw6snd-new "c-lw6snd-new")
(define lw6def-c-lw6snd-play-fx "c-lw6snd-play-fx")
(define lw6def-c-lw6snd-play-music-file "c-lw6snd-play-music-file")
(define lw6def-c-lw6snd-play-music-random "c-lw6snd-play-music-random")
(define lw6def-c-lw6snd-poll "c-lw6snd-poll")
(define lw6def-c-lw6snd-release "c-lw6snd-release")
(define lw6def-c-lw6snd-set-fx-volume "c-lw6snd-set-fx-volume")
(define lw6def-c-lw6snd-set-music-volume "c-lw6snd-set-music-volume")
(define lw6def-c-lw6snd-set-water-volume "c-lw6snd-set-water-volume")
(define lw6def-c-lw6snd-stop-music "c-lw6snd-stop-music")
(define lw6def-c-lw6srv-get-backends "c-lw6srv-get-backends")
(define lw6def-c-lw6sys-build-get-bin-id "c-lw6sys-build-get-bin-id")
(define lw6def-c-lw6sys-build-get-cflags "c-lw6sys-build-get-cflags")
(define lw6def-c-lw6sys-build-get-codename "c-lw6sys-build-get-codename")
(define lw6def-c-lw6sys-build-get-configure-args "c-lw6sys-build-get-configure-args")
(define lw6def-c-lw6sys-build-get-copyright "c-lw6sys-build-get-copyright")
(define lw6def-c-lw6sys-build-get-datadir "c-lw6sys-build-get-datadir")
(define lw6def-c-lw6sys-build-get-date "c-lw6sys-build-get-date")
(define lw6def-c-lw6sys-build-get-enable-allinone "c-lw6sys-build-get-enable-allinone")
(define lw6def-c-lw6sys-build-get-enable-console "c-lw6sys-build-get-enable-console")
(define lw6def-c-lw6sys-build-get-enable-fullstatic "c-lw6sys-build-get-enable-fullstatic")
(define lw6def-c-lw6sys-build-get-enable-gcov "c-lw6sys-build-get-enable-gcov")
(define lw6def-c-lw6sys-build-get-enable-gprof "c-lw6sys-build-get-enable-gprof")
(define lw6def-c-lw6sys-build-get-enable-gtk "c-lw6sys-build-get-enable-gtk")
(define lw6def-c-lw6sys-build-get-enable-instrument "c-lw6sys-build-get-enable-instrument")
(define lw6def-c-lw6sys-build-get-enable-mod-csound "c-lw6sys-build-get-enable-mod-csound")
(define lw6def-c-lw6sys-build-get-enable-mod-gl "c-lw6sys-build-get-enable-mod-gl")
(define lw6def-c-lw6sys-build-get-enable-mod-http "c-lw6sys-build-get-enable-mod-http")
(define lw6def-c-lw6sys-build-get-enable-mod-ogg "c-lw6sys-build-get-enable-mod-ogg")
(define lw6def-c-lw6sys-build-get-enable-optimize "c-lw6sys-build-get-enable-optimize")
(define lw6def-c-lw6sys-build-get-enable-paranoid "c-lw6sys-build-get-enable-paranoid")
(define lw6def-c-lw6sys-build-get-enable-profiler "c-lw6sys-build-get-enable-profiler")
(define lw6def-c-lw6sys-build-get-enable-valgrind "c-lw6sys-build-get-enable-valgrind")
(define lw6def-c-lw6sys-build-get-endianness "c-lw6sys-build-get-endianness")
(define lw6def-c-lw6sys-build-get-gcc-version "c-lw6sys-build-get-gcc-version")
(define lw6def-c-lw6sys-build-get-host-cpu "c-lw6sys-build-get-host-cpu")
(define lw6def-c-lw6sys-build-get-host-os "c-lw6sys-build-get-host-os")
(define lw6def-c-lw6sys-build-get-hostname "c-lw6sys-build-get-hostname")
(define lw6def-c-lw6sys-build-get-includedir "c-lw6sys-build-get-includedir")
(define lw6def-c-lw6sys-build-get-ldflags "c-lw6sys-build-get-ldflags")
(define lw6def-c-lw6sys-build-get-libdir "c-lw6sys-build-get-libdir")
(define lw6def-c-lw6sys-build-get-license "c-lw6sys-build-get-license")
(define lw6def-c-lw6sys-build-get-localedir "c-lw6sys-build-get-localedir")
(define lw6def-c-lw6sys-build-get-md5sum "c-lw6sys-build-get-md5sum")
(define lw6def-c-lw6sys-build-get-package-name "c-lw6sys-build-get-package-name")
(define lw6def-c-lw6sys-build-get-package-string "c-lw6sys-build-get-package-string")
(define lw6def-c-lw6sys-build-get-package-tarname "c-lw6sys-build-get-package-tarname")
(define lw6def-c-lw6sys-build-get-pointer-size "c-lw6sys-build-get-pointer-size")
(define lw6def-c-lw6sys-build-get-prefix "c-lw6sys-build-get-prefix")
(define lw6def-c-lw6sys-build-get-stamp "c-lw6sys-build-get-stamp")
(define lw6def-c-lw6sys-build-get-time "c-lw6sys-build-get-time")
(define lw6def-c-lw6sys-build-get-top-srcdir "c-lw6sys-build-get-top-srcdir")
(define lw6def-c-lw6sys-build-get-url "c-lw6sys-build-get-url")
(define lw6def-c-lw6sys-build-get-version "c-lw6sys-build-get-version")
(define lw6def-c-lw6sys-build-is-gp2x "c-lw6sys-build-is-gp2x")
(define lw6def-c-lw6sys-build-is-mac-os-x "c-lw6sys-build-is-mac-os-x")
(define lw6def-c-lw6sys-build-is-ms-windows "c-lw6sys-build-is-ms-windows")
(define lw6def-c-lw6sys-build-is-x86 "c-lw6sys-build-is-x86")
(define lw6def-c-lw6sys-debug-get "c-lw6sys-debug-get")
(define lw6def-c-lw6sys-debug-set "c-lw6sys-debug-set")
(define lw6def-c-lw6sys-delay "c-lw6sys-delay")
(define lw6def-c-lw6sys-dump "c-lw6sys-dump")
(define lw6def-c-lw6sys-dump-clear "c-lw6sys-dump-clear")
(define lw6def-c-lw6sys-generate-id-16 "c-lw6sys-generate-id-16")
(define lw6def-c-lw6sys-generate-id-32 "c-lw6sys-generate-id-32")
(define lw6def-c-lw6sys-generate-id-64 "c-lw6sys-generate-id-64")
(define lw6def-c-lw6sys-get-config-file "c-lw6sys-get-config-file")
(define lw6def-c-lw6sys-get-cwd "c-lw6sys-get-cwd")
(define lw6def-c-lw6sys-get-cycle "c-lw6sys-get-cycle")
(define lw6def-c-lw6sys-get-data-dir "c-lw6sys-get-data-dir")
(define lw6def-c-lw6sys-get-default-config-file "c-lw6sys-get-default-config-file")
(define lw6def-c-lw6sys-get-default-data-dir "c-lw6sys-get-default-data-dir")
(define lw6def-c-lw6sys-get-default-log-file "c-lw6sys-get-default-log-file")
(define lw6def-c-lw6sys-get-default-map-dir "c-lw6sys-get-default-map-dir")
(define lw6def-c-lw6sys-get-default-map-path "c-lw6sys-get-default-map-path")
(define lw6def-c-lw6sys-get-default-mod-dir "c-lw6sys-get-default-mod-dir")
(define lw6def-c-lw6sys-get-default-music-dir "c-lw6sys-get-default-music-dir")
(define lw6def-c-lw6sys-get-default-music-path "c-lw6sys-get-default-music-path")
(define lw6def-c-lw6sys-get-default-prefix "c-lw6sys-get-default-prefix")
(define lw6def-c-lw6sys-get-default-script-file "c-lw6sys-get-default-script-file")
(define lw6def-c-lw6sys-get-default-user-dir "c-lw6sys-get-default-user-dir")
(define lw6def-c-lw6sys-get-hostname "c-lw6sys-get-hostname")
(define lw6def-c-lw6sys-get-log-file "c-lw6sys-get-log-file")
(define lw6def-c-lw6sys-get-map-dir "c-lw6sys-get-map-dir")
(define lw6def-c-lw6sys-get-map-path "c-lw6sys-get-map-path")
(define lw6def-c-lw6sys-get-mod-dir "c-lw6sys-get-mod-dir")
(define lw6def-c-lw6sys-get-music-dir "c-lw6sys-get-music-dir")
(define lw6def-c-lw6sys-get-music-path "c-lw6sys-get-music-path")
(define lw6def-c-lw6sys-get-prefix "c-lw6sys-get-prefix")
(define lw6def-c-lw6sys-get-run-dir "c-lw6sys-get-run-dir")
(define lw6def-c-lw6sys-get-script-file "c-lw6sys-get-script-file")
(define lw6def-c-lw6sys-get-timestamp "c-lw6sys-get-timestamp")
(define lw6def-c-lw6sys-get-uptime "c-lw6sys-get-uptime")
(define lw6def-c-lw6sys-get-user-dir "c-lw6sys-get-user-dir")
(define lw6def-c-lw6sys-get-username "c-lw6sys-get-username")
(define lw6def-c-lw6sys-getenv "c-lw6sys-getenv")
(define lw6def-c-lw6sys-getenv-prefixed "c-lw6sys-getenv-prefixed")
(define lw6def-c-lw6sys-idle "c-lw6sys-idle")
(define lw6def-c-lw6sys-log "c-lw6sys-log")
(define lw6def-c-lw6sys-log-get-level "c-lw6sys-log-get-level")
(define lw6def-c-lw6sys-log-set-level "c-lw6sys-log-set-level")
(define lw6def-c-lw6sys-path-concat "c-lw6sys-path-concat")
(define lw6def-c-lw6sys-path-parent "c-lw6sys-path-parent")
(define lw6def-c-lw6sys-path-split "c-lw6sys-path-split")
(define lw6def-c-lw6sys-set-memory-bazooka-eraser "c-lw6sys-set-memory-bazooka-eraser")
(define lw6def-c-lw6sys-set-memory-bazooka-size "c-lw6sys-set-memory-bazooka-size")
(define lw6def-c-lw6sys-signal-custom "c-lw6sys-signal-custom")
(define lw6def-c-lw6sys-signal-default "c-lw6sys-signal-default")
(define lw6def-c-lw6sys-signal-poll-quit "c-lw6sys-signal-poll-quit")
(define lw6def-c-lw6sys-signal-send-quit "c-lw6sys-signal-send-quit")
(define lw6def-c-lw6sys-sleep "c-lw6sys-sleep")
(define lw6def-c-lw6sys-snooze "c-lw6sys-snooze")
(define lw6def-c-lw6sys-url-canonize "c-lw6sys-url-canonize")
(define lw6def-c-lw6tsk-loader-get-stage "c-lw6tsk-loader-get-stage")
(define lw6def-c-lw6tsk-loader-new "c-lw6tsk-loader-new")
(define lw6def-c-lw6tsk-loader-pop "c-lw6tsk-loader-pop")
(define lw6def-c-lw6tsk-loader-push "c-lw6tsk-loader-push")
(define lw6def-capture "capture")
(define lw6def-cflags "cflags")
(define lw6def-check "check")
(define lw6def-chosen-map "chosen-map")
(define lw6def-cli-backends "cli-backends")
(define lw6def-click-to-focus "click-to-focus")
(define lw6def-color-alternate-bg "color-alternate-bg")
(define lw6def-color-alternate-fg "color-alternate-fg")
(define lw6def-color-base-bg "color-base-bg")
(define lw6def-color-base-fg "color-base-fg")
(define lw6def-color-conflict-mode "color-conflict-mode")
(define lw6def-colorize "colorize")
(define lw6def-colorize-cursor "colorize-cursor")
(define lw6def-commands-per-sec "commands-per-sec")
(define lw6def-config-file "config-file")
(define lw6def-configure-args "configure-args")
(define lw6def-copy "copy")
(define lw6def-copyleft "copyleft")
(define lw6def-copyright "copyright")
(define lw6def-cursor-pot-init "cursor-pot-init")
(define lw6def-cursor-sensitivity "cursor-sensitivity")
(define lw6def-cursor-size "cursor-size")
(define lw6def-custom-down "custom-down")
(define lw6def-custom-enter "custom-enter")
(define lw6def-custom-esc "custom-esc")
(define lw6def-custom-left "custom-left")
(define lw6def-custom-pgdown "custom-pgdown")
(define lw6def-custom-pgup "custom-pgup")
(define lw6def-custom-right "custom-right")
(define lw6def-custom-up "custom-up")
(define lw6def-daemon "daemon")
(define lw6def-danger-power "danger-power")
(define lw6def-data-dir "data-dir")
(define lw6def-debug "debug")
(define lw6def-debug-layer-id "debug-layer-id")
(define lw6def-debug-team-id "debug-team-id")
(define lw6def-defaults "defaults")
(define lw6def-demo "demo")
(define lw6def-dirty-read "dirty-read")
(define lw6def-display-background "display-background")
(define lw6def-display-console "display-console")
(define lw6def-display-cursors "display-cursors")
(define lw6def-display-debug-gradient "display-debug-gradient")
(define lw6def-display-debug-zones "display-debug-zones")
(define lw6def-display-fighters "display-fighters")
(define lw6def-display-fps "display-fps")
(define lw6def-display-hud "display-hud")
(define lw6def-display-log "display-log")
(define lw6def-display-map "display-map")
(define lw6def-display-menu "display-menu")
(define lw6def-display-mouse "display-mouse")
(define lw6def-display-mps "display-mps")
(define lw6def-display-preview "display-preview")
(define lw6def-display-progress "display-progress")
(define lw6def-display-score "display-score")
(define lw6def-display-splash "display-splash")
(define lw6def-display-url "display-url")
(define lw6def-downsize-using-bench-value "downsize-using-bench-value")
(define lw6def-downsize-using-fighter-scale "downsize-using-fighter-scale")
(define lw6def-example-hints-xml "example-hints-xml")
(define lw6def-example-rules-xml "example-rules-xml")
(define lw6def-example-style-xml "example-style-xml")
(define lw6def-executed-again "executed-again")
(define lw6def-fighter-attack "fighter-attack")
(define lw6def-fighter-defense "fighter-defense")
(define lw6def-fighter-new-health "fighter-new-health")
(define lw6def-fighter-regenerate "fighter-regenerate")
(define lw6def-fighter-scale "fighter-scale")
(define lw6def-force "force")
(define lw6def-frags-fade-out "frags-fade-out")
(define lw6def-frags-mode "frags-mode")
(define lw6def-frags-to-distribute "frags-to-distribute")
(define lw6def-fullscreen "fullscreen")
(define lw6def-fx-volume "fx-volume")
(define lw6def-gfx-backend "gfx-backend")
(define lw6def-gfx-cpu-usage "gfx-cpu-usage")
(define lw6def-gfx-debug "gfx-debug")
(define lw6def-gfx-quality "gfx-quality")
(define lw6def-glue-power "glue-power")
(define lw6def-guess-colors "guess-colors")
(define lw6def-guess-moves-per-sec "guess-moves-per-sec")
(define lw6def-height "height")
(define lw6def-help "help")
(define lw6def-hidden-layer-alpha "hidden-layer-alpha")
(define lw6def-host "host")
(define lw6def-hud-color-auto "hud-color-auto")
(define lw6def-hud-color-frame-bg "hud-color-frame-bg")
(define lw6def-hud-color-frame-fg "hud-color-frame-fg")
(define lw6def-hud-color-text-bg "hud-color-text-bg")
(define lw6def-hud-color-text-fg "hud-color-text-fg")
(define lw6def-hud-style "hud-style")
(define lw6def-io-per-sec "io-per-sec")
(define lw6def-keep-ratio "keep-ratio")
(define lw6def-known-nodes "known-nodes")
(define lw6def-ldflags "ldflags")
(define lw6def-list "list")
(define lw6def-list-advanced "list-advanced")
(define lw6def-list-aliases "list-aliases")
(define lw6def-list-doc "list-doc")
(define lw6def-list-funcs "list-funcs")
(define lw6def-list-graphics "list-graphics")
(define lw6def-list-hooks "list-hooks")
(define lw6def-list-input "list-input")
(define lw6def-list-map "list-map")
(define lw6def-list-map-hints "list-map-hints")
(define lw6def-list-map-rules "list-map-rules")
(define lw6def-list-map-style "list-map-style")
(define lw6def-list-network "list-network")
(define lw6def-list-path "list-path")
(define lw6def-list-players "list-players")
(define lw6def-list-quick "list-quick")
(define lw6def-list-show "list-show")
(define lw6def-list-sound "list-sound")
(define lw6def-loader-sleep "loader-sleep")
(define lw6def-log-file "log-file")
(define lw6def-log-level "log-level")
(define lw6def-log-timeout "log-timeout")
(define lw6def-magic-number "magic-number")
(define lw6def-map-dir "map-dir")
(define lw6def-map-path "map-path")
(define lw6def-max-cursor-pot "max-cursor-pot")
(define lw6def-max-cursor-pot-offset "max-cursor-pot-offset")
(define lw6def-max-cursor-speed "max-cursor-speed")
(define lw6def-max-map-height "max-map-height")
(define lw6def-max-map-surface "max-map-surface")
(define lw6def-max-map-width "max-map-width")
(define lw6def-max-nb-cursors "max-nb-cursors")
(define lw6def-max-nb-nodes "max-nb-nodes")
(define lw6def-max-nb-teams "max-nb-teams")
(define lw6def-max-round-delta "max-round-delta")
(define lw6def-max-zone-size "max-zone-size")
(define lw6def-medicine-power "medicine-power")
(define lw6def-memory-bazooka-eraser "memory-bazooka-eraser")
(define lw6def-memory-bazooka-size "memory-bazooka-size")
(define lw6def-menu-color-auto "menu-color-auto")
(define lw6def-menu-color-default-bg "menu-color-default-bg")
(define lw6def-menu-color-default-fg "menu-color-default-fg")
(define lw6def-menu-color-disabled-bg "menu-color-disabled-bg")
(define lw6def-menu-color-disabled-fg "menu-color-disabled-fg")
(define lw6def-menu-color-selected-bg "menu-color-selected-bg")
(define lw6def-menu-color-selected-fg "menu-color-selected-fg")
(define lw6def-menu-style "menu-style")
(define lw6def-min-map-height "min-map-height")
(define lw6def-min-map-surface "min-map-surface")
(define lw6def-min-map-width "min-map-width")
(define lw6def-mod-dir "mod-dir")
(define lw6def-modules "modules")
(define lw6def-mouse-sensitivity "mouse-sensitivity")
(define lw6def-moves-per-round "moves-per-round")
(define lw6def-music-dir "music-dir")
(define lw6def-music-exclude "music-exclude")
(define lw6def-music-file "music-file")
(define lw6def-music-filter "music-filter")
(define lw6def-music-path "music-path")
(define lw6def-music-volume "music-volume")
(define lw6def-nb-attack-tries "nb-attack-tries")
(define lw6def-nb-defense-tries "nb-defense-tries")
(define lw6def-nb-move-tries "nb-move-tries")
(define lw6def-net-log "net-log")
(define lw6def-network-reliability "network-reliability")
(define lw6def-node-description "node-description")
(define lw6def-node-title "node-title")
(define lw6def-open-relay "open-relay")
(define lw6def-password "password")
(define lw6def-pedigree "pedigree")
(define lw6def-pilot-lag "pilot-lag")
(define lw6def-pixelize "pixelize")
(define lw6def-player1-bot "player1-bot")
(define lw6def-player1-color "player1-color")
(define lw6def-player1-control "player1-control")
(define lw6def-player1-name "player1-name")
(define lw6def-player1-status "player1-status")
(define lw6def-player2-bot "player2-bot")
(define lw6def-player2-color "player2-color")
(define lw6def-player2-control "player2-control")
(define lw6def-player2-name "player2-name")
(define lw6def-player2-status "player2-status")
(define lw6def-player3-bot "player3-bot")
(define lw6def-player3-color "player3-color")
(define lw6def-player3-control "player3-control")
(define lw6def-player3-name "player3-name")
(define lw6def-player3-status "player3-status")
(define lw6def-player4-bot "player4-bot")
(define lw6def-player4-color "player4-color")
(define lw6def-player4-control "player4-control")
(define lw6def-player4-name "player4-name")
(define lw6def-player4-status "player4-status")
(define lw6def-prefix "prefix")
(define lw6def-public-url "public-url")
(define lw6def-quick-start "quick-start")
(define lw6def-repeat-delay "repeat-delay")
(define lw6def-repeat-interval "repeat-interval")
(define lw6def-resample "resample")
(define lw6def-reset "reset")
(define lw6def-reset-config-on-upgrade "reset-config-on-upgrade")
(define lw6def-respawn-position-mode "respawn-position-mode")
(define lw6def-respawn-team "respawn-team")
(define lw6def-round-delta "round-delta")
(define lw6def-rounds-per-sec "rounds-per-sec")
(define lw6def-script-file "script-file")
(define lw6def-server "server")
(define lw6def-show-build-bin-id "show-build-bin-id")
(define lw6def-show-build-cflags "show-build-cflags")
(define lw6def-show-build-codename "show-build-codename")
(define lw6def-show-build-configure-args "show-build-configure-args")
(define lw6def-show-build-copyright "show-build-copyright")
(define lw6def-show-build-datadir "show-build-datadir")
(define lw6def-show-build-date "show-build-date")
(define lw6def-show-build-docdir "show-build-docdir")
(define lw6def-show-build-enable-allinone "show-build-enable-allinone")
(define lw6def-show-build-enable-console "show-build-enable-console")
(define lw6def-show-build-enable-fullstatic "show-build-enable-fullstatic")
(define lw6def-show-build-enable-gcov "show-build-enable-gcov")
(define lw6def-show-build-enable-gprof "show-build-enable-gprof")
(define lw6def-show-build-enable-gtk "show-build-enable-gtk")
(define lw6def-show-build-enable-instrument "show-build-enable-instrument")
(define lw6def-show-build-enable-mod-csound "show-build-enable-mod-csound")
(define lw6def-show-build-enable-mod-gl "show-build-enable-mod-gl")
(define lw6def-show-build-enable-mod-http "show-build-enable-mod-http")
(define lw6def-show-build-enable-mod-ogg "show-build-enable-mod-ogg")
(define lw6def-show-build-enable-optimize "show-build-enable-optimize")
(define lw6def-show-build-enable-paranoid "show-build-enable-paranoid")
(define lw6def-show-build-enable-profiler "show-build-enable-profiler")
(define lw6def-show-build-enable-valgrind "show-build-enable-valgrind")
(define lw6def-show-build-endianness "show-build-endianness")
(define lw6def-show-build-gcc-version "show-build-gcc-version")
(define lw6def-show-build-gp2x "show-build-gp2x")
(define lw6def-show-build-host-cpu "show-build-host-cpu")
(define lw6def-show-build-host-os "show-build-host-os")
(define lw6def-show-build-hostname "show-build-hostname")
(define lw6def-show-build-includedir "show-build-includedir")
(define lw6def-show-build-ldflags "show-build-ldflags")
(define lw6def-show-build-libdir "show-build-libdir")
(define lw6def-show-build-license "show-build-license")
(define lw6def-show-build-localedir "show-build-localedir")
(define lw6def-show-build-mac-os-x "show-build-mac-os-x")
(define lw6def-show-build-md5sum "show-build-md5sum")
(define lw6def-show-build-ms-windows "show-build-ms-windows")
(define lw6def-show-build-package-name "show-build-package-name")
(define lw6def-show-build-package-string "show-build-package-string")
(define lw6def-show-build-package-tarname "show-build-package-tarname")
(define lw6def-show-build-pointer-size "show-build-pointer-size")
(define lw6def-show-build-prefix "show-build-prefix")
(define lw6def-show-build-stamp "show-build-stamp")
(define lw6def-show-build-time "show-build-time")
(define lw6def-show-build-top-srcdir "show-build-top-srcdir")
(define lw6def-show-build-url "show-build-url")
(define lw6def-show-build-version "show-build-version")
(define lw6def-show-build-x86 "show-build-x86")
(define lw6def-show-config-file "show-config-file")
(define lw6def-show-cwd "show-cwd")
(define lw6def-show-data-dir "show-data-dir")
(define lw6def-show-default-config-file "show-default-config-file")
(define lw6def-show-default-data-dir "show-default-data-dir")
(define lw6def-show-default-log-file "show-default-log-file")
(define lw6def-show-default-map-dir "show-default-map-dir")
(define lw6def-show-default-map-path "show-default-map-path")
(define lw6def-show-default-mod-dir "show-default-mod-dir")
(define lw6def-show-default-music-dir "show-default-music-dir")
(define lw6def-show-default-music-path "show-default-music-path")
(define lw6def-show-default-prefix "show-default-prefix")
(define lw6def-show-default-script-file "show-default-script-file")
(define lw6def-show-default-user-dir "show-default-user-dir")
(define lw6def-show-log-file "show-log-file")
(define lw6def-show-map-dir "show-map-dir")
(define lw6def-show-map-path "show-map-path")
(define lw6def-show-mod-dir "show-mod-dir")
(define lw6def-show-music-dir "show-music-dir")
(define lw6def-show-music-path "show-music-path")
(define lw6def-show-prefix "show-prefix")
(define lw6def-show-run-dir "show-run-dir")
(define lw6def-show-script-file "show-script-file")
(define lw6def-show-user-dir "show-user-dir")
(define lw6def-side-attack-factor "side-attack-factor")
(define lw6def-side-defense-factor "side-defense-factor")
(define lw6def-single-army-size "single-army-size")
(define lw6def-skip-network "skip-network")
(define lw6def-snd-backend "snd-backend")
(define lw6def-speed "speed")
(define lw6def-spread-thread "spread-thread")
(define lw6def-spreads-per-round "spreads-per-round")
(define lw6def-srv-backends "srv-backends")
(define lw6def-start-blue-x "start-blue-x")
(define lw6def-start-blue-y "start-blue-y")
(define lw6def-start-cyan-x "start-cyan-x")
(define lw6def-start-cyan-y "start-cyan-y")
(define lw6def-start-green-x "start-green-x")
(define lw6def-start-green-y "start-green-y")
(define lw6def-start-lightblue-x "start-lightblue-x")
(define lw6def-start-lightblue-y "start-lightblue-y")
(define lw6def-start-magenta-x "start-magenta-x")
(define lw6def-start-magenta-y "start-magenta-y")
(define lw6def-start-orange-x "start-orange-x")
(define lw6def-start-orange-y "start-orange-y")
(define lw6def-start-pink-x "start-pink-x")
(define lw6def-start-pink-y "start-pink-y")
(define lw6def-start-position-mode "start-position-mode")
(define lw6def-start-purple-x "start-purple-x")
(define lw6def-start-purple-y "start-purple-y")
(define lw6def-start-red-x "start-red-x")
(define lw6def-start-red-y "start-red-y")
(define lw6def-start-yellow-x "start-yellow-x")
(define lw6def-start-yellow-y "start-yellow-y")
(define lw6def-system-color-auto "system-color-auto")
(define lw6def-system-color-bg "system-color-bg")
(define lw6def-system-color-fg "system-color-fg")
(define lw6def-target-fps "target-fps")
(define lw6def-team-color-blue "team-color-blue")
(define lw6def-team-color-cyan "team-color-cyan")
(define lw6def-team-color-dead "team-color-dead")
(define lw6def-team-color-green "team-color-green")
(define lw6def-team-color-lightblue "team-color-lightblue")
(define lw6def-team-color-magenta "team-color-magenta")
(define lw6def-team-color-orange "team-color-orange")
(define lw6def-team-color-pink "team-color-pink")
(define lw6def-team-color-purple "team-color-purple")
(define lw6def-team-color-red "team-color-red")
(define lw6def-team-color-yellow "team-color-yellow")
(define lw6def-test "test")
(define lw6def-total-armies-size "total-armies-size")
(define lw6def-total-time "total-time")
(define lw6def-trojan "trojan")
(define lw6def-upsize-using-bench-value "upsize-using-bench-value")
(define lw6def-upsize-using-fighter-scale "upsize-using-fighter-scale")
(define lw6def-use-cursor-texture "use-cursor-texture")
(define lw6def-use-esc-button "use-esc-button")
(define lw6def-use-hints-xml "use-hints-xml")
(define lw6def-use-music-file "use-music-file")
(define lw6def-use-rules-xml "use-rules-xml")
(define lw6def-use-style-xml "use-style-xml")
(define lw6def-use-texture "use-texture")
(define lw6def-user-dir "user-dir")
(define lw6def-version "version")
(define lw6def-vertical-move "vertical-move")
(define lw6def-view-color-auto "view-color-auto")
(define lw6def-view-color-cursor-bg "view-color-cursor-bg")
(define lw6def-view-color-cursor-fg "view-color-cursor-fg")
(define lw6def-view-color-map-bg "view-color-map-bg")
(define lw6def-view-color-map-fg "view-color-map-fg")
(define lw6def-view-style "view-style")
(define lw6def-wall-grease "wall-grease")
(define lw6def-water-volume "water-volume")
(define lw6def-width "width")
(define lw6def-windowed-mode-limit "windowed-mode-limit")
(define lw6def-x-polarity "x-polarity")
(define lw6def-x-wrap "x-wrap")
(define lw6def-y-polarity "y-polarity")
(define lw6def-y-wrap "y-wrap")
(define lw6def-z-decode "z-decode")
(define lw6def-z-encode "z-encode")
(define lw6def-z-polarity "z-polarity")
(define lw6def-zoom "zoom")
(define lw6def-zoom-max "zoom-max")
(define lw6def-zoom-min "zoom-min")
(define lw6def-zoom-step "zoom-step")
(define lw6def-zoom-stick-delay "zoom-stick-delay")


