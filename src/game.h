void CoreLogic() {
  int pacmanIndex = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    int inputDirection = setDirection(&direction);

    DrawTexturePro(
      emptyMaze,
      (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
      (Rectangle) { 0, GRID_LENGTH * 3, GRID_LENGTH * 28, GRID_LENGTH * 31 },
      Vector2Zero(), 0, WHITE
    );

    if (GetKeyPressed() != 0) gameStarted = 1;
    if (!gameStarted) DrawText("READY!", GRID_LENGTH * 12.1, GRID_LENGTH * 20, 30, YELLOW);
    if (!gameStarted && !beginning) {
      // PlaySound(audios[AUDIO_BEGINNING]);
      beginning = true;
    }

    DrawPacman(GRID_LENGTH * 13.5, GRID_LENGTH * 26, inputDirection, pacmanIndex);

    EndDrawing();

    pacmanIndex = (int) (GetTime() / 0.075) % pacman.sprites;
  }
}

void Game() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  InitAudioDevice();
  SetTargetFPS(60);

  InitTextures();
  InitAudios();

  CoreLogic();

  UnloadTextures();
  UnloadAudios();

  CloseAudioDevice();
  CloseWindow();
}

