void QueueDirection(int *queued) {
  if (!playButtonPressed || !nameEntered) return;
  if (PRESSED_LEFT)  *queued = S_LEFT;
  if (PRESSED_DOWN)  *queued = S_DOWN;
  if (PRESSED_UP)    *queued = S_UP;
  if (PRESSED_RIGHT) *queued = S_RIGHT;
}

void Play(int audioIndex) {
  #if SOUND_ALLOWED
  if (soundMuted) return;
  if (!IsSoundPlaying(audios[audioIndex])) PlaySound(audios[audioIndex]);
  #endif
}

void RenderText(char *text, float verticalPosition, float fontLevel, Color color) {
  float fontSize = FONT_SIZE * fontLevel / 5;
  int textWidth = MeasureText(text, fontSize);
  DrawText(text, (WIDTH - textWidth) / 2, verticalPosition, fontSize, color);
}

void RenderTextInGame(char *text) {
  RenderText(text, GRID_LENGTH * 20, 5, YELLOW);
}

void NameInput() {
  int key = GetCharPressed();
  while (key > 0) {
    bool isLetter = (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z');
    if (isLetter && nameLength < MAX_NAME) {
      playerName[nameLength++] = (char) toupper(key);
      playerName[nameLength] = '\0';
    }
    key = GetCharPressed();
  }
  if (IsKeyPressed(KEY_BACKSPACE) && nameLength > 0) {
    playerName[--nameLength] = '\0'; // INFO: Nooo had to use pre-increment :')
  }
}

void GameStopwatch() {
  RenderText(TimeFormat(GetGameElapsed()), GRID_LENGTH * 2, 3, WHITE);
}

void RenderNameInGame() {
  RenderText(playerName, GRID_LENGTH * 34.75, 3, GetColor(0xDEADCAFE));
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

void DrawBaseElements(int blorbColor) {
  DrawMap();

  // Credits
  DrawCredits();

  // Score at top
  DrawText(TextFormat("%dUP  %04d", level, currentScore), GRID_LENGTH * 3, GRID_LENGTH * 1, FONT_SIZE - 3, WHITE);
  DrawText(TextFormat("HIGH %04d", highScore), GRID_LENGTH * 19.5, GRID_LENGTH * 1, FONT_SIZE - 3, WHITE);

  // Draw orbs and blorbs
  DrawOrbs();
  DrawBlorbs(blorbColor);

  GameStopwatch();
  RenderNameInGame();
}

void UpdateLocalDetails() {
  level = player.level;
  lives = player.lives;
  currentScore = player.lastLevelScore;
  highScore = player.highScore;
}

void UpdatePlayerDetails() {
  if (!IsNameInList(playerName)) return;
  player.level = level;
  player.lives = lives;
  player.highScore = highScore;
  WritePlayerDetails(player);
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
  float offset = 10;
  return fabsf(pos.x - coords.x) <= offset && fabsf(pos.y - coords.y) <= offset && ++(*snapCount) == 1;
}
