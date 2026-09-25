void RenderMainMenu(float pos, int pacmanIndex, int ghostIndex) {
  if (!menuOpen && currentScreen == MENU) SetTimer(&menuTimer);

  double t = GetCurrentTime(menuTimer);
  if ((int) t % 4 == 2) movementInMenu = true;
  if (movementInMenu) AnimateMenuElements(savedGame, pacmanIndex, ghostIndex, pos);

  RenderText("PAC-MAN", GRID_LENGTH * 7, 10, YELLOW);

  if (savedGame && nameEntered)
    RenderText(playerName, GRID_LENGTH * 12, 5, GetColor(0xDEADCAFE));

  RenderText("ENTER - NEW GAME OR CONTINUE", GRID_LENGTH * 16, 4, GetColor(0xDEADCAFE));

  if (savedGame) RenderText("SPACE - CONTINUE SAVED GAME", GRID_LENGTH * 18.5, 4, YELLOW);
  else RenderText("NO SAVED GAME - PRESS ENTER TO START NEW GAME", GRID_LENGTH * 18.5, 3, GRAY);

  RenderText("1 - SETTINGS"   , GRID_LENGTH * 21  , 3, WHITE);
  RenderText("2 - HELP"       , GRID_LENGTH * 23.5, 3, WHITE);
  RenderText("3 - LEADERBOARD", GRID_LENGTH * 26  , 3, WHITE);

  if (IsKeyPressed(KEY_ENTER)) {
    currentScreen = NAME_ENTRY;
    InitGameState();
    playerName[0] = '\0';
    nameLength = 0;
    nameEntered = false;
    savedGame = false;
    beginning = true;
    playButtonPressed = true;
  }

  if (IsKeyPressed(KEY_SPACE) && nameEntered) {
    currentScreen = PLAYING;
    ResumeGameTimer();
    beginning = true;
    playButtonPressed = true;
  }

  if (IsKeyPressed(KEY_ONE)) currentScreen = SETTINGS;
  if (IsKeyPressed(KEY_TWO)) currentScreen = HELP;
  if (IsKeyPressed(KEY_THREE)) currentScreen = LEADERBOARD;
}

void RenderNameEntry() {
  NameInput();

  RenderText("PAC-MAN", GRID_LENGTH * 7, 10, YELLOW);
  RenderText("ENTER YOUR NAME", GRID_LENGTH * 14, 5, WHITE);

  char display[MAX_NAME + 2];
  sprintf(display, "%s_", playerName);
  RenderText(display, GRID_LENGTH * 17, 7, GetColor(0xDEADCAFE));

  RenderText("BLOCK LETTERS ONLY (A-Z)", GRID_LENGTH * 22, 3, WHITE);
  RenderText("PRESS ENTER TO CONFIRM", GRID_LENGTH * 26, 3, YELLOW);
  RenderText("SHIFT + Q - BACK TO MENU", GRID_LENGTH * 28, 3, GetColor(0xDEADCAFE));

  if (IsKeyPressed(KEY_ENTER) && nameLength > 0) {
    nameEntered = true;
    currentScreen = PLAYING;
    player = InitPlayer(playerName);
    UpdateLocalDetails();
    StartGameTimer();
  }
}

