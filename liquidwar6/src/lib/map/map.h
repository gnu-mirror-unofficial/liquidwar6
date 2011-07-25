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

#ifndef LIQUIDWAR6MAP_H
#define LIQUIDWAR6MAP_H

#include "../sys/sys.h"

#define LW6MAP_MAX_FIGHTER_HEALTH 10000
#define LW6MAP_MAX_NB_TEAMS 10
#define LW6MAP_MAX_NB_CURSORS 26
#define LW6MAP_MAX_NB_NODES 26
#define LW6MAP_MAX_NB_DIR_TRIES 7
#define LW6MAP_CURSOR_TEXTURE_SIZE 64

#define LW6MAP_RULES_POSITION_MODE_PREDEFINED 0
#define LW6MAP_RULES_POSITION_MODE_PICK_EXISTING 1
#define LW6MAP_RULES_POSITION_MODE_TOTAL_RANDOM 2

#define LW6MAP_RULES_COLOR_CONFLICT_MODE_ALLOW_SHARE 0
#define LW6MAP_RULES_COLOR_CONFLICT_MODE_ALLOW_LOCAL_SHARE 1
#define LW6MAP_RULES_COLOR_CONFLICT_MODE_PICK_NEW 2

#define LW6MAP_RULES_FRAGS_MODE_ONE_NEGATIVE_POINT 0
#define LW6MAP_RULES_FRAGS_MODE_ONE_FOR_WINNERS_ALL_FOR_LOSER 1
#define LW6MAP_RULES_FRAGS_MODE_BALANCED 2
#define LW6MAP_RULES_FRAGS_MODE_PROPORTIONAL 3

/*
 * All static rules default/min/max
 */
// 15 minutes
#define LW6MAP_RULES_DEFAULT_TOTAL_TIME 900
// 10 seconds
#define LW6MAP_RULES_MIN_TOTAL_TIME 10
// 10 days
#define LW6MAP_RULES_MAX_TOTAL_TIME 864000

#define LW6MAP_RULES_DEFAULT_RESPAWN_TEAM 1
#define LW6MAP_RULES_MIN_RESPAWN_TEAM 0
#define LW6MAP_RULES_MAX_RESPAWN_TEAM 1

#define LW6MAP_RULES_DEFAULT_RESPAWN_POSITION_MODE LW6MAP_RULES_POSITION_MODE_PICK_EXISTING
#define LW6MAP_RULES_MIN_RESPAWN_POSITION_MODE 0
#define LW6MAP_RULES_MAX_RESPAWN_POSITION_MODE 2

#define LW6MAP_RULES_DEFAULT_MOVES_PER_ROUND 2
#define LW6MAP_RULES_MIN_MOVES_PER_ROUND 1
#define LW6MAP_RULES_MAX_MOVES_PER_ROUND 50

#define LW6MAP_RULES_DEFAULT_SPREADS_PER_ROUND 3
#define LW6MAP_RULES_MIN_SPREADS_PER_ROUND 1
#define LW6MAP_RULES_MAX_SPREADS_PER_ROUND 12

#define LW6MAP_RULES_DEFAULT_ROUNDS_PER_SEC 50
#define LW6MAP_RULES_MIN_ROUNDS_PER_SEC 1
#define LW6MAP_RULES_MAX_ROUNDS_PER_SEC 200

#define LW6MAP_RULES_DEFAULT_FIGHTER_ATTACK 500
#define LW6MAP_RULES_MIN_FIGHTER_ATTACK 1
#define LW6MAP_RULES_MAX_FIGHTER_ATTACK LW6MAP_MAX_FIGHTER_HEALTH

#define LW6MAP_RULES_DEFAULT_FIGHTER_DEFENSE 50
#define LW6MAP_RULES_MIN_FIGHTER_DEFENSE 0
#define LW6MAP_RULES_MAX_FIGHTER_DEFENSE LW6MAP_MAX_FIGHTER_HEALTH

#define LW6MAP_RULES_DEFAULT_FIGHTER_NEW_HEALTH 5000
#define LW6MAP_RULES_MIN_FIGHTER_NEW_HEALTH 1
#define LW6MAP_RULES_MAX_FIGHTER_NEW_HEALTH LW6MAP_MAX_FIGHTER_HEALTH

#define LW6MAP_RULES_DEFAULT_FIGHTER_REGENERATE 5
#define LW6MAP_RULES_MIN_FIGHTER_REGENERATE 0
#define LW6MAP_RULES_MAX_FIGHTER_REGENERATE LW6MAP_MAX_FIGHTER_HEALTH

// 20%
#define LW6MAP_RULES_DEFAULT_SIDE_ATTACK_FACTOR 20
#define LW6MAP_RULES_MIN_SIDE_ATTACK_FACTOR 0
#define LW6MAP_RULES_MAX_SIDE_ATTACK_FACTOR 100

// 20%
#define LW6MAP_RULES_DEFAULT_SIDE_DEFENSE_FACTOR 20
#define LW6MAP_RULES_MIN_SIDE_DEFENSE_FACTOR 0
#define LW6MAP_RULES_MAX_SIDE_DEFENSE_FACTOR 100

#define LW6MAP_RULES_DEFAULT_NB_MOVE_TRIES 5
#define LW6MAP_RULES_MIN_NB_MOVE_TRIES 3
#define LW6MAP_RULES_MAX_NB_MOVE_TRIES LW6MAP_MAX_NB_DIR_TRIES

#define LW6MAP_RULES_DEFAULT_NB_ATTACK_TRIES 3
#define LW6MAP_RULES_MIN_NB_ATTACK_TRIES 1
#define LW6MAP_RULES_MAX_NB_ATTACK_TRIES LW6MAP_MAX_NB_DIR_TRIES

#define LW6MAP_RULES_DEFAULT_NB_DEFENSE_TRIES 1
#define LW6MAP_RULES_MIN_NB_DEFENSE_TRIES 1
#define LW6MAP_RULES_MAX_NB_DEFENSE_TRIES LW6MAP_MAX_NB_DIR_TRIES

#define LW6MAP_RULES_DEFAULT_VERTICAL_MOVE 1
#define LW6MAP_RULES_MIN_VERTICAL_MOVE 0
#define LW6MAP_RULES_MAX_VERTICAL_MOVE LW6MAP_MAX_NB_DIR_TRIES

// 9%
#define LW6MAP_RULES_DEFAULT_SINGLE_ARMY_SIZE 30
// 0.01%
#define LW6MAP_RULES_MIN_SINGLE_ARMY_SIZE 1
// 90%
#define LW6MAP_RULES_MAX_SINGLE_ARMY_SIZE 95

// 36%
#define LW6MAP_RULES_DEFAULT_TOTAL_ARMIES_SIZE 60
// 0.01%
#define LW6MAP_RULES_MIN_TOTAL_ARMIES_SIZE 1
// 90%
#define LW6MAP_RULES_MAX_TOTAL_ARMIES_SIZE 95

#define LW6MAP_RULES_DEFAULT_MAX_NB_TEAMS LW6MAP_MAX_NB_TEAMS
#define LW6MAP_RULES_MIN_MAX_NB_TEAMS 2
#define LW6MAP_RULES_MAX_MAX_NB_TEAMS LW6MAP_MAX_NB_TEAMS

#define LW6MAP_RULES_DEFAULT_MAX_NB_CURSORS LW6MAP_MAX_NB_CURSORS
#define LW6MAP_RULES_MIN_MAX_NB_CURSORS 2
#define LW6MAP_RULES_MAX_MAX_NB_CURSORS LW6MAP_MAX_NB_CURSORS

// LW6MAP_MAX_NB_TEAMS+2
#define LW6MAP_RULES_DEFAULT_MAX_NB_NODES 12
#define LW6MAP_RULES_MIN_MAX_NB_NODES 2
#define LW6MAP_RULES_MAX_MAX_NB_NODES LW6MAP_MAX_NB_NODES

#define LW6MAP_RULES_DEFAULT_X_POLARITY 0
#define LW6MAP_RULES_MIN_X_POLARITY -1
#define LW6MAP_RULES_MAX_X_POLARITY 1

#define LW6MAP_RULES_DEFAULT_Y_POLARITY 0
#define LW6MAP_RULES_MIN_Y_POLARITY -1
#define LW6MAP_RULES_MAX_Y_POLARITY 1

#define LW6MAP_RULES_DEFAULT_Z_POLARITY 0
#define LW6MAP_RULES_MIN_Z_POLARITY 0
#define LW6MAP_RULES_MAX_Z_POLARITY 1

#define LW6MAP_RULES_DEFAULT_MAX_ZONE_SIZE 8
#define LW6MAP_RULES_MIN_MAX_ZONE_SIZE 1
#define LW6MAP_RULES_MAX_MAX_ZONE_SIZE 64

#define LW6MAP_RULES_DEFAULT_ROUND_DELTA 1
#define LW6MAP_RULES_MIN_ROUND_DELTA 0
#define LW6MAP_RULES_MAX_ROUND_DELTA 100

#define LW6MAP_RULES_DEFAULT_MAX_ROUND_DELTA 1000
#define LW6MAP_RULES_MIN_MAX_ROUND_DELTA 1
#define LW6MAP_RULES_MAX_MAX_ROUND_DELTA 10000

#define LW6MAP_RULES_DEFAULT_MAX_CURSOR_POT 1000000
#define LW6MAP_RULES_MIN_MAX_CURSOR_POT 50000
#define LW6MAP_RULES_MAX_MAX_CURSOR_POT 5000000

#define LW6MAP_RULES_DEFAULT_CURSOR_POT_INIT 100000
#define LW6MAP_RULES_MIN_CURSOR_POT_INIT 5000
#define LW6MAP_RULES_MAX_CURSOR_POT_INIT 500000

#define LW6MAP_RULES_DEFAULT_MAX_CURSOR_POT_OFFSET 100
#define LW6MAP_RULES_MIN_MAX_CURSOR_POT_OFFSET 1
#define LW6MAP_RULES_MAX_MAX_CURSOR_POT_OFFSET 10000

#define LW6MAP_RULES_DEFAULT_START_RED_X 10
#define LW6MAP_RULES_MIN_START_RED_X 0
#define LW6MAP_RULES_MAX_START_RED_X 100

#define LW6MAP_RULES_DEFAULT_START_RED_Y 10
#define LW6MAP_RULES_MIN_START_RED_Y 0
#define LW6MAP_RULES_MAX_START_RED_Y 100

#define LW6MAP_RULES_DEFAULT_START_GREEN_X 90
#define LW6MAP_RULES_MIN_START_GREEN_X 0
#define LW6MAP_RULES_MAX_START_GREEN_X 100

#define LW6MAP_RULES_DEFAULT_START_GREEN_Y 90
#define LW6MAP_RULES_MIN_START_GREEN_Y 0
#define LW6MAP_RULES_MAX_START_GREEN_Y 100

#define LW6MAP_RULES_DEFAULT_START_BLUE_X 90
#define LW6MAP_RULES_MIN_START_BLUE_X 0
#define LW6MAP_RULES_MAX_START_BLUE_X 100

#define LW6MAP_RULES_DEFAULT_START_BLUE_Y 10
#define LW6MAP_RULES_MIN_START_BLUE_Y 0
#define LW6MAP_RULES_MAX_START_BLUE_Y 100

#define LW6MAP_RULES_DEFAULT_START_YELLOW_X 10
#define LW6MAP_RULES_MIN_START_YELLOW_X 0
#define LW6MAP_RULES_MAX_START_YELLOW_X 100

#define LW6MAP_RULES_DEFAULT_START_YELLOW_Y 90
#define LW6MAP_RULES_MIN_START_YELLOW_Y 0
#define LW6MAP_RULES_MAX_START_YELLOW_Y 100

#define LW6MAP_RULES_DEFAULT_START_CYAN_X 35
#define LW6MAP_RULES_MIN_START_CYAN_X 0
#define LW6MAP_RULES_MAX_START_CYAN_X 100

#define LW6MAP_RULES_DEFAULT_START_CYAN_Y 10
#define LW6MAP_RULES_MIN_START_CYAN_Y 0
#define LW6MAP_RULES_MAX_START_CYAN_Y 100

#define LW6MAP_RULES_DEFAULT_START_MAGENTA_X 65
#define LW6MAP_RULES_MIN_START_MAGENTA_X 0
#define LW6MAP_RULES_MAX_START_MAGENTA_X 100

#define LW6MAP_RULES_DEFAULT_START_MAGENTA_Y 90
#define LW6MAP_RULES_MIN_START_MAGENTA_Y 0
#define LW6MAP_RULES_MAX_START_MAGENTA_Y 100

#define LW6MAP_RULES_DEFAULT_START_ORANGE_X 65
#define LW6MAP_RULES_MIN_START_ORANGE_X 0
#define LW6MAP_RULES_MAX_START_ORANGE_X 100

#define LW6MAP_RULES_DEFAULT_START_ORANGE_Y 10
#define LW6MAP_RULES_MIN_START_ORANGE_Y 0
#define LW6MAP_RULES_MAX_START_ORANGE_Y 100

#define LW6MAP_RULES_DEFAULT_START_LIGHTBLUE_X 35
#define LW6MAP_RULES_MIN_START_LIGHTBLUE_X 0
#define LW6MAP_RULES_MAX_START_LIGHTBLUE_X 100

#define LW6MAP_RULES_DEFAULT_START_LIGHTBLUE_Y 90
#define LW6MAP_RULES_MIN_START_LIGHTBLUE_Y 0
#define LW6MAP_RULES_MAX_START_LIGHTBLUE_Y 100

#define LW6MAP_RULES_DEFAULT_START_PURPLE_X 90
#define LW6MAP_RULES_MIN_START_PURPLE_X 0
#define LW6MAP_RULES_MAX_START_PURPLE_X 100

#define LW6MAP_RULES_DEFAULT_START_PURPLE_Y 50
#define LW6MAP_RULES_MIN_START_PURPLE_Y 0
#define LW6MAP_RULES_MAX_START_PURPLE_Y 100

#define LW6MAP_RULES_DEFAULT_START_PINK_X 10
#define LW6MAP_RULES_MIN_START_PINK_X 0
#define LW6MAP_RULES_MAX_START_PINK_X 100

#define LW6MAP_RULES_DEFAULT_START_PINK_Y 50
#define LW6MAP_RULES_MIN_START_PINK_Y 0
#define LW6MAP_RULES_MAX_START_PINK_Y 100

#define LW6MAP_RULES_DEFAULT_START_POSITION_MODE LW6MAP_RULES_POSITION_MODE_PREDEFINED
#define LW6MAP_RULES_MIN_START_POSITION_MODE 0
#define LW6MAP_RULES_MAX_START_POSITION_MODE 2

#define LW6MAP_RULES_DEFAULT_COLOR_CONFLICT_MODE LW6MAP_RULES_COLOR_CONFLICT_MODE_ALLOW_LOCAL_SHARE
#define LW6MAP_RULES_MIN_COLOR_CONFLICT_MODE 0
#define LW6MAP_RULES_MAX_COLOR_CONFLICT_MODE 2

#define LW6MAP_RULES_DEFAULT_SPREAD_THREAD 0
#define LW6MAP_RULES_MIN_SPREAD_THREAD 0
#define LW6MAP_RULES_MAX_SPREAD_THREAD 1

#define LW6MAP_RULES_DEFAULT_GLUE_POWER 20
#define LW6MAP_RULES_MIN_GLUE_POWER 0
#define LW6MAP_RULES_MAX_GLUE_POWER 100

#define LW6MAP_RULES_DEFAULT_BOOST_POWER 3
#define LW6MAP_RULES_MIN_BOOST_POWER 0
#define LW6MAP_RULES_MAX_BOOST_POWER 10

#define LW6MAP_RULES_DEFAULT_DANGER_POWER 200
#define LW6MAP_RULES_MIN_DANGER_POWER 0
#define LW6MAP_RULES_MAX_DANGER_POWER LW6MAP_MAX_FIGHTER_HEALTH

#define LW6MAP_RULES_DEFAULT_MEDICINE_POWER 100
#define LW6MAP_RULES_MIN_MEDICINE_POWER 0
#define LW6MAP_RULES_MAX_MEDICINE_POWER LW6MAP_MAX_FIGHTER_HEALTH

#define LW6MAP_RULES_DEFAULT_FRAGS_MODE LW6MAP_RULES_FRAGS_MODE_BALANCED
#define LW6MAP_RULES_MIN_FRAGS_MODE 0
#define LW6MAP_RULES_MAX_FRAGS_MODE 3

#define LW6MAP_RULES_DEFAULT_FRAGS_TO_DISTRIBUTE 100
#define LW6MAP_RULES_MIN_FRAGS_TO_DISTRIBUTE 10
#define LW6MAP_RULES_MAX_FRAGS_TO_DISTRIBUTE 1000

#define LW6MAP_RULES_DEFAULT_FRAGS_FADE_OUT 100
#define LW6MAP_RULES_MIN_FRAGS_FADE_OUT 10
#define LW6MAP_RULES_MAX_FRAGS_FADE_OUT 100

/*
 * Note: it's important that floats are never ever used in map rules.
 * In fact, we need maps to be 100,00 (lots of zeroes) predictable,
 * given some identical user actions. Using floats could lead us
 * to very slight differences (floats are never accurate, especially
 * when you run calculus on different hardwares) which could, with
 * time, become very important. Sort of a "butterfly effect".
 * So well, we use int. Int32 to be exact.
 */
typedef struct lw6map_rules_s
{
  int32_t total_time;
  int32_t respawn_team;
  int32_t respawn_position_mode;
  int32_t moves_per_round;
  int32_t spreads_per_round;
  int32_t rounds_per_sec;
  int32_t fighter_attack;
  int32_t fighter_defense;
  int32_t fighter_new_health;
  int32_t fighter_regenerate;
  int32_t side_attack_factor;
  int32_t side_defense_factor;
  int32_t nb_move_tries;
  int32_t nb_attack_tries;
  int32_t nb_defense_tries;
  int32_t vertical_move;
  int32_t single_army_size;
  int32_t total_armies_size;
  int32_t max_nb_teams;
  int32_t max_nb_cursors;
  int32_t max_nb_nodes;
  int32_t x_polarity;
  int32_t y_polarity;
  int32_t z_polarity;
  int32_t max_zone_size;
  int32_t round_delta;
  int32_t max_round_delta;
  int32_t max_cursor_pot;
  int32_t cursor_pot_init;
  int32_t max_cursor_pot_offset;
  int32_t start_red_x;
  int32_t start_red_y;
  int32_t start_green_x;
  int32_t start_green_y;
  int32_t start_blue_x;
  int32_t start_blue_y;
  int32_t start_yellow_x;
  int32_t start_yellow_y;
  int32_t start_cyan_x;
  int32_t start_cyan_y;
  int32_t start_magenta_x;
  int32_t start_magenta_y;
  int32_t start_orange_x;
  int32_t start_orange_y;
  int32_t start_lightblue_x;
  int32_t start_lightblue_y;
  int32_t start_purple_x;
  int32_t start_purple_y;
  int32_t start_pink_x;
  int32_t start_pink_y;
  int32_t start_position_mode;
  int32_t color_conflict_mode;
  int32_t spread_thread;
  int32_t glue_power;
  int32_t boost_power;
  int32_t danger_power;
  int32_t medicine_power;
  int32_t frags_mode;
  int32_t frags_to_distribute;
  int32_t frags_fade_out;
} lw6map_rules_t;
extern char *LW6MAP_RULES_LIST[];

#define LW6MAP_MIN_SIDE 3
// serious limit here, must be < 8191
#define LW6MAP_MAX_SIDE 8000
#define LW6MAP_MIN_SURFACE 12
#define LW6MAP_MAX_SURFACE 48000000

// can't be too high for perf issues
#define LW6MAP_MAX_DEPTH 7

#define LW6MAP_STYLE_DEFAULT_KEEP_RATIO 1
#define LW6MAP_STYLE_DEFAULT_ZOOM 1.0f
#define LW6MAP_STYLE_DEFAULT_ZOOM_MIN 0.3f
#define LW6MAP_STYLE_DEFAULT_ZOOM_MAX 30.0f
#define LW6MAP_STYLE_DEFAULT_X_WRAP 1
#define LW6MAP_STYLE_DEFAULT_Y_WRAP 1
#define LW6MAP_STYLE_DEFAULT_BACKGROUND_STYLE "bubbles"
#define LW6MAP_STYLE_DEFAULT_HUD_STYLE "floating"
#define LW6MAP_STYLE_DEFAULT_MENU_STYLE "cylinder"
#define LW6MAP_STYLE_DEFAULT_VIEW_STYLE "flat"
#define LW6MAP_STYLE_DEFAULT_ANIMATION_DENSITY 1.0f
#define LW6MAP_STYLE_DEFAULT_ANIMATION_SPEED 1.0f
#define LW6MAP_STYLE_DEFAULT_CURSOR_SIZE 1.0f
#define LW6MAP_STYLE_DEFAULT_COLORIZE_CURSOR 1
#define LW6MAP_STYLE_DEFAULT_BLINK_CURSOR 0
#define LW6MAP_STYLE_DEFAULT_HIDDEN_LAYER_ALPHA 0.1f
#define LW6MAP_STYLE_DEFAULT_COLORIZE 1
#define LW6MAP_STYLE_DEFAULT_PIXELIZE 0
#define LW6MAP_STYLE_DEFAULT_COLOR_BASE_BG "#000"
#define LW6MAP_STYLE_DEFAULT_COLOR_BASE_FG "#ccc"
#define LW6MAP_STYLE_DEFAULT_COLOR_ALTERNATE_BG "#333"
#define LW6MAP_STYLE_DEFAULT_COLOR_ALTERNATE_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_BACKGROUND_COLOR_ROOT_BG "#000"
#define LW6MAP_STYLE_DEFAULT_BACKGROUND_COLOR_ROOT_FG "#ccc"
#define LW6MAP_STYLE_DEFAULT_BACKGROUND_COLOR_STUFF_BG "#333"
#define LW6MAP_STYLE_DEFAULT_BACKGROUND_COLOR_STUFF_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_HUD_COLOR_FRAME_BG "#000"
#define LW6MAP_STYLE_DEFAULT_HUD_COLOR_FRAME_FG "#ccc"
#define LW6MAP_STYLE_DEFAULT_HUD_COLOR_TEXT_BG "#333"
#define LW6MAP_STYLE_DEFAULT_HUD_COLOR_TEXT_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_DEFAULT_BG "#333"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_DEFAULT_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_SELECTED_BG "#fff"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_SELECTED_FG "#333"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_DISABLED_BG "#000"
#define LW6MAP_STYLE_DEFAULT_MENU_COLOR_DISABLED_FG "#ccc"
#define LW6MAP_STYLE_DEFAULT_VIEW_COLOR_CURSOR_BG "#333"
#define LW6MAP_STYLE_DEFAULT_VIEW_COLOR_CURSOR_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_VIEW_COLOR_MAP_BG "#000"
#define LW6MAP_STYLE_DEFAULT_VIEW_COLOR_MAP_FG "#ccc"
#define LW6MAP_STYLE_DEFAULT_SYSTEM_COLOR_BG "#333"
#define LW6MAP_STYLE_DEFAULT_SYSTEM_COLOR_FG "#fff"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_DEAD "#000"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_RED "#f00"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_GREEN "#0f0"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_BLUE "#00f"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_YELLOW "#ff0"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_CYAN "#0ff"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_MAGENTA "#f0f"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_ORANGE "#f80"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_LIGHTBLUE "#8bf"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_PURPLE "#b8f"
#define LW6MAP_STYLE_DEFAULT_TEAM_COLOR_PINK "#f8b"
#define LW6MAP_STYLE_DEFAULT_MUSIC_FILE ""
#define LW6MAP_STYLE_DEFAULT_MUSIC_FILTER ""
/*
 * Hi Tim, this is not to blacklist you, no way! Only this
 * is needed so that your tunes don't get played *in game*
 * but only while navigating in the menus.
 */
#define LW6MAP_STYLE_DEFAULT_MUSIC_EXCLUDE "Chadburn"

#define LW6MAP_TEAM_COLOR_KEY_RED "red"
#define LW6MAP_TEAM_COLOR_KEY_GREEN "green"
#define LW6MAP_TEAM_COLOR_KEY_BLUE "blue"
#define LW6MAP_TEAM_COLOR_KEY_YELLOW "yellow"
#define LW6MAP_TEAM_COLOR_KEY_CYAN "cyan"
#define LW6MAP_TEAM_COLOR_KEY_MAGENTA "magenta"
#define LW6MAP_TEAM_COLOR_KEY_ORANGE "orange"
#define LW6MAP_TEAM_COLOR_KEY_LIGHTBLUE "lightblue"
#define LW6MAP_TEAM_COLOR_KEY_PURPLE "purple"
#define LW6MAP_TEAM_COLOR_KEY_PINK "pink"

#define LW6MAP_NB_TEAM_COLORS LW6MAP_MAX_NB_TEAMS

#define LW6MAP_BUILTIN_DEFAULT_WIDTH 256
#define LW6MAP_BUILTIN_DEFAULT_HEIGHT 128
#define LW6MAP_BUILTIN_DEFAULT_DEPTH 1
#define LW6MAP_BUILTIN_DEFAULT_NOISE_PERCENT 10

typedef enum lw6map_team_color_e
{ LW6MAP_TEAM_COLOR_INVALID = -1, LW6MAP_TEAM_COLOR_RED =
    0, LW6MAP_TEAM_COLOR_GREEN = 1, LW6MAP_TEAM_COLOR_BLUE =
    2, LW6MAP_TEAM_COLOR_YELLOW = 3, LW6MAP_TEAM_COLOR_CYAN =
    4, LW6MAP_TEAM_COLOR_MAGENTA = 5, LW6MAP_TEAM_COLOR_ORANGE =
    6, LW6MAP_TEAM_COLOR_LIGHTBLUE = 7, LW6MAP_TEAM_COLOR_PURPLE =
    8, LW6MAP_TEAM_COLOR_PINK = 9
} lw6map_team_color_t;

typedef struct lw6map_metadata_s
{
  char *title;
  char *readme;
} lw6map_metadata_t;

/*
 * Local info is for fields which can be exploited locally,
 * but make no sense if transfered to another computer, over
 * the network for instance. This is typically something
 * which will be updated by the ldr module or some other external
 * code, but it's not directly linked to the content of the
 * map itself.
 */
typedef struct lw6map_local_info_s
{
  char *music_dir;
} lw6map_local_info_t;

typedef struct lw6map_layer_s
{
  lw6sys_whd_t shape;
  u_int8_t *data;
} lw6map_layer_t;

typedef struct lw6map_meta_layer_s
{
  lw6sys_whd_t shape;
  u_int8_t *data;
} lw6map_meta_layer_t;

typedef struct lw6map_body_s
{
  int checksum;
  lw6sys_whd_t shape;
  lw6map_layer_t layers[LW6MAP_MAX_DEPTH];
  lw6map_meta_layer_t glue;
  lw6map_meta_layer_t boost;
  lw6map_meta_layer_t danger;
  lw6map_meta_layer_t medicine;
  lw6map_meta_layer_t one_way_north;
  lw6map_meta_layer_t one_way_east;
  lw6map_meta_layer_t one_way_south;
  lw6map_meta_layer_t one_way_west;
} lw6map_body_t;

typedef struct lw6map_color_couple_s
{
  lw6sys_color_8_t fg;
  lw6sys_color_8_t bg;
} lw6map_color_couple_t;

typedef struct lw6map_texture_s
{
  int w;
  int h;
  int has_alpha;
  lw6sys_color_8_t *data;
  lw6map_color_couple_t guessed_color_base;
  lw6map_color_couple_t guessed_color_alternate;
} lw6map_texture_t;

typedef struct lw6map_cursor_texture_layer_s
{
  lw6sys_color_8_t
    data[LW6MAP_CURSOR_TEXTURE_SIZE][LW6MAP_CURSOR_TEXTURE_SIZE];
} lw6map_cursor_texture_layer_t;

typedef struct lw6map_cursor_texture_s
{
  lw6map_cursor_texture_layer_t fg_bg_layer;
  lw6map_cursor_texture_layer_t color_layer;
} lw6map_cursor_texture_t;

typedef struct lw6map_color_set_s
{
  lw6map_color_couple_t color_base;
  lw6map_color_couple_t color_alternate;
  lw6map_color_couple_t background_color_root;
  lw6map_color_couple_t background_color_stuff;
  lw6map_color_couple_t hud_color_frame;
  lw6map_color_couple_t hud_color_text;
  lw6map_color_couple_t menu_color_default;
  lw6map_color_couple_t menu_color_selected;
  lw6map_color_couple_t menu_color_disabled;
  lw6map_color_couple_t view_color_cursor;
  lw6map_color_couple_t view_color_map;
  lw6map_color_couple_t system_color;
  lw6sys_color_8_t team_color_dead;
  lw6sys_color_8_t team_colors[LW6MAP_NB_TEAM_COLORS];
} lw6map_color_set_t;

typedef struct lw6map_style_s
{
  int keep_ratio;		// boolean
  float zoom;
  float zoom_min;
  float zoom_max;
  int x_wrap;
  int y_wrap;
  char *background_style;
  char *hud_style;
  char *menu_style;
  char *view_style;
  float animation_density;
  float animation_speed;
  float cursor_size;
  int colorize_cursor;
  int blink_cursor;
  float hidden_layer_alpha;
  int colorize;
  int pixelize;
  lw6map_color_set_t color_set;
  char *music_file;
  char *music_filter;
  char *music_exclude;
} lw6map_style_t;

typedef struct lw6map_param_s
{
  lw6map_rules_t rules;
  lw6map_style_t style;
} lw6map_param_t;

typedef struct lw6map_level_s
{
  u_int32_t id;
  lw6map_metadata_t metadata;
  lw6map_local_info_t local_info;
  lw6map_body_t body;
  lw6map_texture_t texture;
  lw6map_cursor_texture_t cursor_texture;
  lw6map_param_t param;
} lw6map_level_t;

/*
 * Commodity inline setters/getters
 */

static inline void
lw6map_body_set (lw6map_body_t * body, int x, int y, int z, u_int8_t value)
{
  body->layers[z].data[y * body->shape.w + x] = value;
}

static inline u_int8_t
lw6map_body_get (lw6map_body_t * body, int x, int y, int z)
{
  return body->layers[z].data[y * body->shape.w + x];
}

static inline void
lw6map_layer_set (lw6map_layer_t * layer, int x, int y, u_int8_t value)
{
  layer->data[y * layer->shape.w + x] = value;
}

static inline u_int8_t
lw6map_layer_get (lw6map_layer_t * layer, int x, int y)
{
  return layer->data[y * layer->shape.w + x];
}

static inline void
lw6map_texture_set (lw6map_texture_t * texture, int x, int y,
		    lw6sys_color_8_t value)
{
  texture->data[y * texture->w + x] = value;
}

static inline lw6sys_color_8_t
lw6map_texture_get (lw6map_texture_t * texture, int x, int y)
{
  return texture->data[y * texture->w + x];
}

/* map-body.c */
extern void lw6map_body_builtin_custom (lw6map_body_t * body, int w, int h,
					int d, int noise_percent,
					lw6map_rules_t * rules);
extern void lw6map_body_clear (lw6map_body_t * body);
extern void lw6map_body_fix_checksum (lw6map_body_t * body);
extern int lw6map_body_check_and_fix_holes (lw6map_body_t * body,
					    lw6map_rules_t * rules);
extern int lw6map_body_coord_from_texture (lw6map_level_t * level,
					   int *depth_x, int *depth_y,
					   int texture_x, int texture_y);
extern u_int8_t lw6map_body_get_with_texture_coord (lw6map_level_t *
						    level,
						    int texture_x,
						    int texture_y, int z);

/* map-color.c */
extern void lw6map_color_invert (lw6map_color_couple_t * color);
extern int lw6map_color_is_same (lw6map_color_couple_t * color1,
				 lw6map_color_couple_t * color2);
extern char *lw6map_team_color_index_to_key (int index);
extern int lw6map_team_color_key_to_index (char *key);


/* map-coords.c */
extern void lw6map_coords_fix_xy (lw6map_rules_t * rules,
				  lw6sys_whd_t * shape, int *x, int *y);
extern void lw6map_coords_fix_z (lw6map_rules_t * rules,
				 lw6sys_whd_t * shape, int *z);

/* map-cursortexture.c */
extern void lw6map_cursor_texture_layer_set (lw6map_cursor_texture_layer_t *
					     cursor_texture, int x, int y,
					     lw6sys_color_8_t color);
extern lw6sys_color_8_t
lw6map_cursor_texture_layer_get (lw6map_cursor_texture_layer_t *
				 cursor_texture, int x, int y);
extern void lw6map_cursor_texture_clear (lw6map_cursor_texture_t *
					 cursor_texture);
extern void lw6map_cursor_texture_builtin (lw6map_cursor_texture_t *
					   cursor_texture);

/* map-dup.c */
extern lw6map_level_t *lw6map_dup (lw6map_level_t * source,
				   lw6sys_progress_t * progress);

/* map-hexa.c */
extern char *lw6map_to_hexa (lw6map_level_t * level);
extern lw6map_level_t *lw6map_from_hexa (char *hexa);

/* map-layer.c */
extern void lw6map_layer_builtin_custom (lw6map_layer_t * layer, int w,
					 int h);
extern void lw6map_layer_clear (lw6map_layer_t * layer);

/* map-level.c */
extern lw6map_level_t *lw6map_new ();
extern lw6map_level_t *lw6map_builtin_defaults ();
extern lw6map_level_t *lw6map_builtin_custom (int w, int h, int d,
					      int noise_percent);
extern void lw6map_free (lw6map_level_t * level);
extern int lw6map_memory_footprint (lw6map_level_t * level);
extern char *lw6map_repr (lw6map_level_t * level);
extern int lw6map_is_same (lw6map_level_t * level_a,
			   lw6map_level_t * level_b);

/* map-localinfo.c */
extern int lw6map_local_info_set_music_dir (lw6map_local_info_t *
					    local_info, char *music_dir);
extern void lw6map_local_info_clear (lw6map_local_info_t * local_info);

/*
 * In metadata.c
 */
extern void lw6map_metadata_defaults (lw6map_metadata_t * metadata);
extern void lw6map_metadata_clear (lw6map_metadata_t * metadata);
extern int lw6map_metadata_is_same (lw6map_metadata_t * metadata_a,
				    lw6map_metadata_t * metadata_b);

/* map-metalayer.c */
extern void lw6map_meta_layer_set (lw6map_meta_layer_t * meta_layer, int x,
				   int y, u_int8_t value);
extern u_int8_t lw6map_meta_layer_get (lw6map_meta_layer_t * meta_layer,
				       int x, int y);
extern void lw6map_meta_layer_clear (lw6map_meta_layer_t * meta_layer);
extern int lw6map_meta_layer_builtin_custom (lw6map_meta_layer_t * meta_layer,
					     int w, int h, int analog,
					     int noise_percent, int seed);

/*
 * In rules.c
 */
extern void lw6map_rules_defaults (lw6map_rules_t * rules);
extern void lw6map_rules_copy (lw6map_rules_t * dst, lw6map_rules_t * src);
extern void lw6map_rules_update_checksum (lw6map_rules_t * rules,
					  u_int32_t * checksum);
extern int32_t lw6map_rules_get_default (char *key);
extern int32_t lw6map_rules_get_min (char *key);
extern int32_t lw6map_rules_get_max (char *key);
extern int32_t lw6map_rules_get_int (lw6map_rules_t * rules, char *key);
extern int lw6map_rules_set_int (lw6map_rules_t * rules, char *key,
				 int32_t value);
extern int lw6map_rules_get_bool (lw6map_rules_t * rules, char *key);
extern int lw6map_rules_set_bool (lw6map_rules_t * rules, char *key,
				  int value);
extern void lw6map_rules_clear (lw6map_rules_t * rules);
extern int lw6map_rules_is_same (lw6map_rules_t * rules_a,
				 lw6map_rules_t * rules_b);

// map-param.c
extern void lw6map_param_defaults (lw6map_param_t * param);
extern void lw6map_param_clear (lw6map_param_t * param);
extern void lw6map_param_copy (lw6map_param_t * dst, lw6map_param_t * src);
extern int lw6map_param_set (lw6map_param_t * param, char *key, char *value);
extern int lw6map_param_is_same (lw6map_param_t * param_a,
				 lw6map_param_t * param_b);

/*
 * In style.c
 */
extern void lw6map_style_zero (lw6map_style_t * style);
extern void lw6map_style_defaults (lw6map_style_t * style);
extern void lw6map_style_clear (lw6map_style_t * style);
extern void lw6map_style_copy (lw6map_style_t * dst, lw6map_style_t * src);
extern int lw6map_style_set (lw6map_style_t * style, char *key, char *value);
extern char *lw6map_style_get (lw6map_style_t * style, char *key);
extern char *lw6map_style_get_default (char *key);
extern int lw6map_color_set_is_same (lw6map_color_set_t * color_set_a,
				     lw6map_color_set_t * color_set_b);
extern int lw6map_style_is_same (lw6map_style_t * style_a,
				 lw6map_style_t * style_b);

/* map-test.c */
extern int lw6map_test (int mode);

/*
 * In texture.c
 */
extern void lw6map_texture_clear (lw6map_texture_t * texture);
extern int lw6map_texture_coord_from_body (lw6map_level_t * level,
					   int *texture_x, int *texture_y,
					   int body_x, int body_y);
extern lw6sys_color_8_t lw6map_texture_get_with_body_coord (lw6map_level_t *
							    level,
							    int body_x,
							    int body_y);
extern int lw6map_texture_from_body (lw6map_texture_t * texture,
				     lw6map_body_t * body,
				     lw6map_color_couple_t * color);
extern int lw6map_texture_has_alpha (lw6map_texture_t * texture);

#endif /*  */
