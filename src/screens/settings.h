void ToggleMute() {
  soundMuted = !soundMuted;
}

void RestartGame() {
  InitGameState();
  ResetGameTimer();
  playerName[0] = '\0';
  nameLength = 0;
  nameEntered = false;
  SavedGame = false;
  currentScreen = MENU;
  playButtonPressed = false;
  beginning = false;
}

void RenderSettings() {
  RenderText("SETTINGS", GRID_LENGTH * 7, 10, YELLOW);

  RenderText(soundMuted ? "SOUND: MUTED" : "SOUND: ON", GRID_LENGTH * 16, 5, soundMuted ? RED : LIME );
 
  RenderText("M - MUTE/UNMUTE", GRID_LENGTH * 19, 3, WHITE);
  RenderText("R - RESTART GAME", GRID_LENGTH * 22, 3, WHITE);
  RenderText("Q - BACK TO MENU", GRID_LENGTH * 25, 3, GetColor(0xDEADCAFE));

  if (IsKeyPressed(KEY_M)) ToggleMute();
  if (IsKeyPressed(KEY_R)) RestartGame();
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
