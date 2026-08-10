#include "./src/imports.h"

int main(void) {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
