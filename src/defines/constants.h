#define GRID_LENGTH 20

#define GRID_WIDTH  28
#define GRID_HEIGHT 36

#define SPEED(base) ((base) * GRID_LENGTH / 25)
#define PACMAN_SPEED      SPEED(375)
#define GHOST_SPEED       SPEED(275)
#define EATEN_GHOST_SPEED SPEED(500)
#define ANIMATION_SPEED 0.075

#define WIDTH (GRID_WIDTH * GRID_LENGTH)
#define HEIGHT (GRID_HEIGHT * GRID_LENGTH)
#define TITLE "Pac-Man - B2 (091 + 098)"
#define FONT_SIZE (GRID_LENGTH + 3)

#define MAX_LIVES           3
#define MAX_LEVEL          40
#define SCORE_PELLET       10
#define SCORE_POWER_PELLET 50
#define SCORE_GHOST       200
#define TOTAL_PELLETS     244

#define PRESSED_LEFT  (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_H))
#define PRESSED_DOWN  (IsKeyPressed(KEY_DOWN)  || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_J))
#define PRESSED_UP    (IsKeyPressed(KEY_UP)    || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_K))
#define PRESSED_RIGHT (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_L))
#define PRESSED_PAUSE (IsKeyPressed(KEY_SPACE))
#define PRESSED_RESTART (PRESSED_PAUSE || IsKeyPressed(KEY_R))

#define LENGTH(arr) (sizeof((arr)) / sizeof((arr)[0]))

// assets.h
#define AUDIO_LENGTH 8

#define AUDIO_START     0
#define AUDIO_SIREN     1
#define AUDIO_EATDOT    2
#define AUDIO_FRIGHT    3
#define AUDIO_EYES      4
#define AUDIO_EATGHOST  5
#define AUDIO_EATFRUIT  6
#define AUDIO_DEATH     7

#define SPRITE_X 14
#define SPRITE_Y 13
#define UNIT_SPRITE_LENGTH 56

#define PELLET_COLOR 0xffb6adff

#define S_LEFT   0
#define S_DOWN   1
#define S_UP     2
#define S_RIGHT  3

// gridwall.h
#define VOID       0
#define WALL       1
#define ORB        2
#define BLORB      3
#define ORB_EATEN  4

#include "./map.h"

// player.h
#define PACMAN 0xdead
#define PACMAN_STARTING_POSITION ((Vector2) { (float) GRID_LENGTH * 13.5, (float) GRID_LENGTH * 26.0 })

// ghosts.h
// names
#define GHOSTS 4

#define BLINKY  0
#define PINKY   1
#define INKY    2
#define CLYDE   3

#define EYES 0xe4e5

// states
#define SCATTER     0
#define CHASE       1
#define FRIGHTENED  2
#define EATEN       3

// tiles
#define GHOST_GATE ((Vector2) { 13, 14 })
#define GHOST_HOME ((Vector2) { 13, 17 })
