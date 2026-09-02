#define GRID_LENGTH 20

#define GRID_WIDTH 28
#define GRID_HEIGHT 36

#define SPEED 300

#define WIDTH (GRID_WIDTH * GRID_LENGTH)
#define HEIGHT (GRID_HEIGHT * GRID_LENGTH)
#define TITLE "Pac-Man - B2 (091 + 098)"

#define MAX_LIVES 3
#define SCORE_PELLET 10
#define SCORE_POWER_PELLET 50
#define SCORE_GHOST 200

#define LEFT (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
#define DOWN (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
#define UP (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
#define RIGHT (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
#define PAUSE IsKeyPressed(KEY_SPACE)

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

