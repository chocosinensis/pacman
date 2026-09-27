void RenderHowToPlay(int pacmanIndex, int blorbColor, int ghostIndex) {
  RenderText("HOW TO PLAY:", GRID_LENGTH * 7, 3, YELLOW);

  int elementPos = 5;
  float textPos = (elementPos + 2) * GRID_LENGTH;
  float fontSize = FONT_SIZE * 3.75 / 5;
  Color color = WHITE;

  float orbPos = 9;
  DrawSingleOrb(elementPos, orbPos);
  DrawText("EAT ORBS TO COLLECT POINTS", textPos, orbPos * GRID_LENGTH, fontSize, color);

  float blorbPos = orbPos + 1.5;
  DrawSingleBlorb(elementPos, blorbPos, blorbColor);
  DrawText("EAT BLORBS TO FRIGHTEN GHOST", textPos, blorbPos * GRID_LENGTH, fontSize, color);

  float gPos = blorbPos + 1.5;
  Ghost g = { BLINKY, FRIGHTENED, GetTilePosition((Vector2) { elementPos, gPos }), S_RIGHT };
  DrawGhost(g, ghostIndex);
  DrawText("EAT FRIGHTENED GHOSTS FOR FUN", textPos, gPos * GRID_LENGTH, fontSize, color);

  float fruitPos = gPos + 1.5;
  DrawFruitAnywhere(elementPos, fruitPos);
  DrawText("EAT FRUIT TO INCREASE LIFE", textPos, fruitPos * GRID_LENGTH, fontSize, color);

  float pPos = fruitPos + 1.5;
  Vector2 pacmanPos = GetTilePosition((Vector2) { elementPos, pPos });
  DrawPacman(pacmanPos.x, pacmanPos.y, S_RIGHT, pacmanIndex);
  DrawText("EAT ALL ORBS TO FINISH LEVEL", textPos, pPos * GRID_LENGTH, fontSize, color);
}

void RenderHelp(int pacmanIndex, int blorbColor, int ghostIndex) {
  RenderText("HELP", GRID_LENGTH * 4, 7, YELLOW);

  RenderHowToPlay(pacmanIndex, blorbColor, ghostIndex);

  RenderText("IN GAME:", GRID_LENGTH * 18, 3, YELLOW);
  RenderText("ARROWS / WASD - MOVE   SPACE - PAUSE   R - RESTART", GRID_LENGTH * 20, 3, WHITE);

  RenderText("ON THE MAIN MENU:", GRID_LENGTH * 23, 3, YELLOW);
  RenderText("ENTER - NEW GAME   SPACE - CONTINUE", GRID_LENGTH * 24.5, 3, WHITE);
  RenderText("1 - SETTINGS   2 - HELP   3 - LEADERBOARD   4 - CREDITS", GRID_LENGTH * 26, 3, WHITE);

  RenderText("Q - BACK TO MENU", GRID_LENGTH * 29, 3, GetColor(0xDEADCAFE));
  RenderText("ESC - EXIT GAME" , GRID_LENGTH * 31, 3, GetColor(0xDEADCAFE));
  if (IsKeyPressed(KEY_Q)) currentScreen = MENU;
}
