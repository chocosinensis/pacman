void RenderCredits() {
  RenderText("CREDITS", GRID_LENGTH * 7, 10, YELLOW);

  Color creditColor = GetColor(PELLET_COLOR);
  RenderText("PIXEL ARTIST"  , GRID_LENGTH * 13, 3, WHITE);
  RenderText("HIROSHI ONO"   , GRID_LENGTH * 15, 5, creditColor);
  RenderText("SOUND DESINGER", GRID_LENGTH * 19, 3, WHITE);
  RenderText("TOSHIO KAI"    , GRID_LENGTH * 21, 5, creditColor);

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 26, 3, GetColor(0xDEADCAFE));
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
