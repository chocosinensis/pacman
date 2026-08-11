#define WIDTH 800
#define HEIGHT 600
#define TITLE "Pacman - B2 (091 + 098)"

#define LEFT (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
#define DOWN (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
#define UP (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
#define RIGHT (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))

#define SPRITE(path, name, idx) sprintf(path, "./assets/sprites/%s-%d.png", name, idx)

