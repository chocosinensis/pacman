void RenderHelp() {
  RenderText("HELP", GRID_LENGTH * 7, 10, YELLOW);

  RenderText("ARROWS / WASD - MOVE", GRID_LENGTH * 12, 3, WHITE);
  RenderText("SPACE - PAUSE (IN GAME)", GRID_LENGTH * 14.5, 3, WHITE);
  RenderText("R - RESTART AFTER GAME OVER", GRID_LENGTH * 17, 3, WHITE);
  RenderText("Q - QUIT TO MAIN MENU", GRID_LENGTH * 19.5, 3, WHITE);

  RenderText("ON THE MAIN MENU:", GRID_LENGTH * 23, 3, YELLOW);
  RenderText("ENTER - NEW GAME   SPACE - CONTINUE", GRID_LENGTH * 25.5, 3, WHITE);
  RenderText("1 - SETTINGS   2 - HELP   3 - LEADERBOARD", GRID_LENGTH * 28, 3, WHITE);

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 32, 3, GetColor(0xDEADCAFE));
  if(IsKeyPressed(KEY_Q)) currentScreen = MENU;
}