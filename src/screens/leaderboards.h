void RenderLeaderboard() {
  RenderText("LEADERBOARD", GRID_LENGTH * 7, 10, YELLOW);
  RenderText("Q - BACK TO MENU", GRID_LENGTH * 20, 3, GetColor(0xDEADCAFE));
  if(IsKeyPressed(KEY_Q)) currentScreen = MENU;
}