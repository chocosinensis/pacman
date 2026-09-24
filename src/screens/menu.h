void RenderMainMenu() {
  if (GetKeyPressed() != 0) {
    beginning = true;
    playButtonPressed = true;
  }

  RenderText("PAC-MAN", GRID_LENGTH * 7, 10, YELLOW);
  RenderText("PRESS ANY KEY TO PLAY", GRID_LENGTH * GRID_HEIGHT / 2, 5, GetColor(0xDEADCAFE));
  RenderText("PRESS R TO RESTART AFTER GAME OVER", GRID_LENGTH * 24, 3, WHITE);
  // TODO: QUITTING DOESN'T WORK FOR SOME REASON
  RenderText("PRESS Q TO RETURN TO MAIN MENU", GRID_LENGTH * 26, 3, WHITE);

  // DO YOUR MAGIC HERE AND OTHERS
}
