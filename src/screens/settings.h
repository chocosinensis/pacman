void ToggleMute() {
  soundMuted = !soundMuted;
}

void ToggleSFX() {
  sfxMuted = !sfxMuted;
}

void ResetCache() {
  playerName[0] = '\0';
  nameLength = 0;
  nameEntered = false;
  savedGame = false;
  InitGameState();
  ResetGameTimer();
  currentScreen = MENU;
  playButtonPressed = false;
  beginning = false;
}

void DeletePlayer() {
  bool rm = RemovePlayer(playerName);
  if (rm) ResetCache();
}

void RenderSettings() {
  RenderText("SETTINGS", GRID_LENGTH * 7, 10, YELLOW);

  bool sfx = sfxMuted || (soundMuted && !sfxMuted);
  RenderText(soundMuted ? "SOUND: MUTED" : "SOUND: ON", GRID_LENGTH * 12, 4, soundMuted ? RED : LIME );
  RenderText(sfx        ? "SFX: MUTED"   : "SFX: ON"  , GRID_LENGTH * 14, 4, sfx        ? RED : LIME );
 
  RenderText("M - MUTE/UNMUTE"  , GRID_LENGTH * 17, 3, WHITE);
  RenderText("S - TOGGLE SFX"   , GRID_LENGTH * 19, 3, WHITE);
  RenderText("Q - BACK TO MENU" , GRID_LENGTH * 26, 3, GetColor(0xDEADCAFE));

  if (IsKeyPressed(KEY_M)) ToggleMute();
  if (IsKeyPressed(KEY_S)) ToggleSFX();
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
  
  if (!savedGame) return;
  if (IsKeyPressed(KEY_R)) ResetCache();
  if (IsKeyPressed(KEY_D)) DeletePlayer();
  RenderText("R - RESET PLAYER" , GRID_LENGTH * 21, 3, WHITE);
  RenderText("D - DELETE PLAYER", GRID_LENGTH * 23, 3, WHITE);
}
