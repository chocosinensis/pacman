void RenderLeaderboard() {
  RenderText("LEADERBOARD", GRID_LENGTH * 5, 10, YELLOW);

  float fontSize = FONT_SIZE * 4 / 5;

  int sernPosition  = GRID_LENGTH * 2;
  int namePosition  = GRID_LENGTH * 4;
  int levelPosition = GRID_LENGTH * 10;
  int scorePosition = GRID_LENGTH * 16;
  int timePosition  = GRID_LENGTH * 22;

  int firstRowPosition = GRID_LENGTH * 10;

  DrawText("NAME" , namePosition , firstRowPosition, fontSize, WHITE);
  DrawText("LEVEL", levelPosition, firstRowPosition, fontSize, WHITE);
  DrawText("SCORE", scorePosition, firstRowPosition, fontSize, WHITE);
  DrawText("TIME" , timePosition , firstRowPosition, fontSize, WHITE);

  char namesList[MAX_NAMES][MAX_NAME_LENGTH];
  for (int i = 0; i < MAX_NAMES; i++) for (int j = 0; j < MAX_NAME_LENGTH; j++) namesList[i][j] = 0;
  GetNames(namesList);

  for (int i = 0; i < 10; i++) {
    if (*namesList[i] == '\0') break;

    bool fileExists = LogFileExists(namesList[i]);
    if (!fileExists) continue;

    int rowPosition = GRID_LENGTH * (12 + 1.5 * i);
    int hex = i == 0 ? 0xD4AF37FF  // GOLDEN
      :       i == 1 ? 0xC0C0C0FF  // SILVER
      :       i == 2 ? 0xC79B56FF  // BRONZE
      :                0xCEBA97CC; // LESSER-BRONZE
    Color color = GetColor(hex);

    Player p;
    ReadPlayerDetails(namesList[i], &p);

    int s = i + 1;
    char n[6];
    strncpy(n, p.name, 5);
    int l = p.level;
    int h = p.highScore;
    char *t = TimeFormat(p.elapsedTime);

    DrawText(TextFormat("%d", s), sernPosition , rowPosition + 5, FONT_SIZE * 1 / 5, color);
    DrawText(TextFormat("%s", n), namePosition , rowPosition, fontSize, color);
    DrawText(TextFormat("%d", l), levelPosition, rowPosition, fontSize, color);
    DrawText(TextFormat("%d", h), scorePosition, rowPosition, fontSize, color);
    DrawText(TextFormat("%s", t), timePosition , rowPosition, fontSize, color);
  }

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 30, 3, GetColor(0xDEADCAFE));
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
