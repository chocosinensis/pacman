void DrawPacman(int x, int y, int direction, int index) {
  Vector2 pc = GetSpriteDirection(pacman, direction);
  DrawTexturePro(
    characters,
    (Rectangle) { pc.x + (index * UNIT_SPRITE_LENGTH), pc.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

Vector2 MoveInDirection(Vector2 pos, int dir, float distance) {
  if (dir == S_LEFT)  pos.x -= distance;
  if (dir == S_RIGHT) pos.x += distance;
  if (dir == S_UP)    pos.y -= distance;
  if (dir == S_DOWN)  pos.y += distance;
  return pos;
}

void EatPellet(float x, float y) {
  bool orb = IsOrb(x, y);
  bool blorb = IsBlorb(x, y);

  int gridX = (int) (x / GRID_LENGTH);
  int gridY = (int) (y / GRID_LENGTH);

  if (!orb && !blorb) return;

  MAP[gridY][gridX] = ORB_EATEN;
  AddScore(orb ? SCORE_PELLET : blorb ? SCORE_POWER_PELLET : 0);

  #if SOUND_ALLOWED
  if (orb && !IsSoundPlaying(audios[AUDIO_EATDOT]))
    PlaySound(audios[AUDIO_EATDOT]);

  if (blorb) PlaySound(audios[AUDIO_FRIGHT]);
  #endif
}

