void QueueDirection(int *queued) {
  if (PRESSED_LEFT)  *queued = S_LEFT;
  if (PRESSED_DOWN)  *queued = S_DOWN;
  if (PRESSED_UP)    *queued = S_UP;
  if (PRESSED_RIGHT) *queued = S_RIGHT;
}

void Play(int audioIndex) {
  #if SOUND_ALLOWED
  if (!IsSoundPlaying(audios[audioIndex])) PlaySound(audios[audioIndex]);
  #endif
}

void DrawCredits() {
  // INFO: CREDITS
  // 2505091 : @chocosinensis
  // 2505098 : @DirayatSupro
  float x = GRID_LENGTH * 23;
  float fontSize = FONT_SIZE / 3;
  int color = 0xDEADCAFE;

  DrawText("@chocosinensis", x, GRID_LENGTH * 34.5, fontSize, GetColor(color));
  DrawText("@DirayatSupro", x, GRID_LENGTH * 35, fontSize, GetColor(color));
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

bool Snaps(Vector2 pos, int *snapCount) {
  Vector2 coords = GetCoordinates(pos);
  float offset = 0;
  return fabsf(pos.x - coords.x) <= offset && fabsf(pos.y - coords.y) <= offset && ++(*snapCount) == 1;
}
