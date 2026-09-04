void DrawGhost(int x, int y, int direction, int name, int index) {
  Vector2 g = getSpriteDirection(ghosts[name], direction);
  DrawTexturePro(
    characters,
    (Rectangle) { g.x + (index * UNIT_SPRITE_LENGTH), g.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}
void InitGhosts(int index) {
  for (int i = 0; i < GHOSTS; i++)
    DrawGhost(
      (12 + i) * GRID_LENGTH,
      17 * GRID_LENGTH,
      S_RIGHT, i, index
    );
}
