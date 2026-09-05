void QueueDirection(int *queued) {
  if (LEFT)  *queued = S_LEFT;
  if (DOWN)  *queued = S_DOWN;
  if (UP)    *queued = S_UP;
  if (RIGHT) *queued = S_RIGHT;
}

Vector2 MakeSprite(int x, int y) {
  return (Vector2) { x * UNIT_SPRITE_LENGTH, y * UNIT_SPRITE_LENGTH };
}
Vector2 GetSpriteDirection(Character ch, int direction) {
  if (direction == S_LEFT)  return ch.left;
  if (direction == S_DOWN)  return ch.down;
  if (direction == S_UP)    return ch.up;
  if (direction == S_RIGHT) return ch.right;
}
Character InitCharacter(
  int right_x, int right_y,
  int left_x, int left_y,
  int up_x, int up_y,
  int down_x, int down_y,
  int sprites, int name
) {
  return (Character) {
    MakeSprite(right_x, right_y),
    MakeSprite(left_x, left_y),
    MakeSprite(up_x, up_y),
    MakeSprite(down_x, down_y),
    sprites, name
  };
}

Vector2 Tileify(Vector2 pos) {
  float tileX = round(pos.x / GRID_LENGTH);
  float tileY = round(pos.y / GRID_LENGTH);
  return (Vector2) { tileX, tileY };
}
Vector2 GetTilePosition(Vector2 tile) {
  return (Vector2) { tile.x * GRID_LENGTH, tile.y * GRID_LENGTH };
}
Vector2 GetCoordinates(Vector2 pos) {
  return GetTilePosition(Tileify(pos));
}

