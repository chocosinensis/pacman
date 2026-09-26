void RenderHelp() {
  RenderText("HELP", GRID_LENGTH * 6, 10, YELLOW);

  RenderText("ARROWS / WASD - MOVE"       , GRID_LENGTH * 11  , 3, WHITE);
  RenderText("SPACE - PAUSE (IN GAME)"    , GRID_LENGTH * 13.5, 3, WHITE);
  RenderText("R - RESTART AFTER GAME OVER", GRID_LENGTH * 16  , 3, WHITE);

  RenderText("ON THE MAIN MENU:", GRID_LENGTH * 20, 3, YELLOW);
  RenderText("ENTER - NEW GAME   SPACE - CONTINUE", GRID_LENGTH * 22.5, 3, WHITE);
  RenderText("1 - SETTINGS   2 - HELP   3 - LEADERBOARD   4 - CREDITS", GRID_LENGTH * 25, 3, WHITE);

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 29, 3, GetColor(0xDEADCAFE));
  RenderText("ESC - EXIT GAME" , GRID_LENGTH * 31, 3, GetColor(0xDEADCAFE));
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
