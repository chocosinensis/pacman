bool gameStarted = false;
bool beginning = false;

int direction = S_LEFT;

void DrawPacman(int x, int y, int direction, int index) {
  Vector2 pc = getSpriteDirection(pacman, direction);
  printf("%d\n", index);
  DrawTexturePro(
    characters,
    (Rectangle) { pc.x + (index * UNIT_SPRITE_LENGTH), pc.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

