#define GRID_LENGTH 20

#define GRID_WIDTH 28
#define GRID_HEIGHT 36

#define SPEED (300 * GRID_LENGTH / 25)

#define WIDTH (GRID_WIDTH * GRID_LENGTH)
#define HEIGHT (GRID_HEIGHT * GRID_LENGTH)
#define TITLE "Pac-Man - B2 (091 + 098)"
#define FONT_SIZE (GRID_LENGTH + 3)

#define MAX_LIVES 3
#define SCORE_PELLET 10
#define SCORE_POWER_PELLET 50
#define SCORE_GHOST 200

#define LEFT (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_H))
#define DOWN (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_J))
#define UP (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_K))
#define RIGHT (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_L))
#define PAUSE (IsKeyPressed(KEY_SPACE))

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

// assets.h
#define AUDIO_LENGTH 8

#define AUDIO_START 0
#define AUDIO_SIREN 1
#define AUDIO_EATDOT 2
#define AUDIO_FRIGHT 3
#define AUDIO_EYES 4
#define AUDIO_EATGHOST 5
#define AUDIO_EATFRUIT 6
#define AUDIO_DEATH 7

#define SPRITE_X 14
#define SPRITE_Y 13
#define UNIT_SPRITE_LENGTH 56

#define PELLET_COLOR 0xffb6adff

#define S_RIGHT 0
#define S_LEFT 1
#define S_UP 2
#define S_DOWN 3

// gridwall.h
#define VOID 0
#define WALL 1
#define ORB 2
#define BLORB 3
#define ORB_EATEN 4

// player.h
#define PACMAN 0xdead

// ghosts.h
// names
#define GHOSTS 4
#define BLINKY 0
#define PINKY 1
#define INKY 2
#define CLYDE 3

// states
#define SCATTER 0
#define CHASE 1
#define FRIGHTENED 2
#define EATEN 3

