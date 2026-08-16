int setDirection(int *p_direction) {
  if (LEFT) *p_direction = S_LEFT;
  if (DOWN) *p_direction = S_DOWN;
  if (UP) *p_direction = S_UP;
  if (RIGHT) *p_direction = S_RIGHT;
  return *p_direction;
}

Vector2 makeSprite(int x, int y) {
  return (Vector2) { x * UNIT_SPRITE_LENGTH, y * UNIT_SPRITE_LENGTH };
}
Vector2 getSpriteDirection(Character ch, int direction) {
  if (direction == S_RIGHT) return ch.right;
  if (direction == S_LEFT) return ch.left;
  if (direction == S_UP) return ch.up;
  if (direction == S_DOWN) return ch.down;
}
Character newCharacter(
  int right_x, int right_y,
  int left_x, int left_y,
  int up_x, int up_y,
  int down_x, int down_y,
  int sprites
) {
  return (Character) {
    makeSprite(right_x, right_y),
    makeSprite(left_x, left_y),
    makeSprite(up_x, up_y),
    makeSprite(down_x, down_y),
    sprites
  };
}

