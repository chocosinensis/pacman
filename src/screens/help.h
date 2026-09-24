void RenderHelp() {
  RenderText("HELP", GRID_LENGTH * 5, 10, YELLOW);

  RenderText("ARROWS / WASD - MOVE"       , GRID_LENGTH * 10  , 3, WHITE);
  RenderText("SPACE - PAUSE (IN GAME)"    , GRID_LENGTH * 12.5, 3, WHITE);
  RenderText("R - RESTART AFTER GAME OVER", GRID_LENGTH * 15  , 3, WHITE);
  RenderText("Q - QUIT TO MAIN MENU"      , GRID_LENGTH * 17.5, 3, WHITE);

  RenderText("ON THE MAIN MENU:", GRID_LENGTH * 21, 3, YELLOW);
  RenderText("ENTER - NEW GAME   SPACE - CONTINUE"      , GRID_LENGTH * 23.5, 3, WHITE);
  RenderText("1 - SETTINGS   2 - HELP   3 - LEADERBOARD", GRID_LENGTH * 26  , 3, WHITE);

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 30, 3, GetColor(0xDEADCAFE));
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
