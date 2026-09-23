void InitMap(int MAP[GRID_HEIGHT][GRID_WIDTH]) {
  for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
      MAP[i][j] = FIXED_MAP[i][j];
}

bool IsCollidable(float x, float y, int object) {
  int gridX = (int) (x / GRID_LENGTH);
  int gridY = (int) (y / GRID_LENGTH);

  if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
    return false;
  }

  return MAP[gridY][gridX] == object;
}

bool IsWall(float x, float y) {
  return IsCollidable(x, y, WALL);
}

bool WillHitWall(Vector2 pos) {
  float margin = GRID_LENGTH / 10.0f;
  float size = (float) GRID_LENGTH - margin;

  return
    IsWall(pos.x + margin, pos.y + margin) ||
    IsWall(pos.x + size,   pos.y + margin) ||
    IsWall(pos.x + margin, pos.y + size)   ||
    IsWall(pos.x + size,   pos.y + size);
}
bool CanTurn(Vector2 pos, int dir) {
  Vector2 next = MoveInDirection(pos, dir, GRID_LENGTH / 4.0);
  return !WillHitWall(next);
}

bool IsOrb(float x, float y) {
  return IsCollidable(x, y, ORB);
}
bool IsBlorb(float x, float y) {
  return IsCollidable(x, y, BLORB);
}

bool IsEveryPelletEaten(int pelletCount) {
  if (pelletCount != TOTAL_PELLETS) return false;

  for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
      if (MAP[i][j] == ORB || MAP[i][j] == BLORB) return false;

  return true;
}
