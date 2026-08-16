#define GRID_LENGTH 28

#define GRID_WIDTH 28
#define GRID_HEIGHT 36

#define WIDTH (GRID_WIDTH * GRID_LENGTH)
#define HEIGHT (GRID_HEIGHT * GRID_LENGTH)
#define TITLE "Pac-Man - B2 (091 + 098)"

#define LEFT (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
#define DOWN (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
#define UP (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
#define RIGHT (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

