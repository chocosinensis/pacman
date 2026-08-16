void CoreLogic() {
  int pacmanIndex = 2;
  Vector2 pacmanPosition = { GRID_LENGTH * 13.5, GRID_LENGTH * 26 };

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);

    int inputDirection = setDirection(&direction);

    DrawTexturePro(
      emptyMaze,
      (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
      (Rectangle) { 0, GRID_LENGTH * 3, GRID_LENGTH * 28, GRID_LENGTH * 31 },
      Vector2Zero(), 0, WHITE
    );

    if (GetKeyPressed() != 0) {
      gameStarted = true;
      if (!PAUSE) gamePaused = false;
    }
    if (!gameStarted) DrawText("READY!", GRID_LENGTH * 12.1, GRID_LENGTH * 20, 30, YELLOW);
    if (gameStarted && !PAUSE && gamePaused) DrawText("PAUSE", GRID_LENGTH * 12.2, GRID_LENGTH * 20, 30, YELLOW);
    if (!gameStarted && !beginning && gamePaused) {
      PlaySound(audios[AUDIO_BEGINNING]);
      beginning = true;
    }
    if (PAUSE) gamePaused = !gamePaused;
    if (gameStarted && !gamePaused) {
      if (!IsSoundPlaying(audios[AUDIO_CHOMP])) PlaySound(audios[AUDIO_CHOMP]);

      // PACMAN MOVEMENT
      if (inputDirection == S_LEFT) pacmanPosition.x -= SPEED * dt;
      if (inputDirection == S_RIGHT) pacmanPosition.x += SPEED * dt;
      if (inputDirection == S_UP) pacmanPosition.y -= SPEED * dt;
      if (inputDirection == S_DOWN) pacmanPosition.y += SPEED * dt;

      pacmanIndex = (int) (GetTime() / 0.075) % pacman.sprites;
    } else pacmanIndex = 2;

    // TODO: Implement the maze and detect collision for pacman and ghosts
    // PACMAN BARE COLLISION
    if (pacmanPosition.x < 0) pacmanPosition.x = WIDTH;
    if (pacmanPosition.x > WIDTH) pacmanPosition.x = 0;
    int upperwall = 4;
    int lowerwall = 3 + 29;
    if (pacmanPosition.y < GRID_LENGTH * upperwall) pacmanPosition.y = GRID_LENGTH * upperwall;
    if (pacmanPosition.y > GRID_LENGTH * lowerwall) pacmanPosition.y = GRID_LENGTH * lowerwall;

    DrawPacman(pacmanPosition.x, pacmanPosition.y, inputDirection, pacmanIndex);

    EndDrawing();
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

