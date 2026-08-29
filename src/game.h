void CoreLogic() {
  int pacmanIndex = 2;
  Vector2 pacmanPosition = { (float)GRID_LENGTH * 13.5, (float)GRID_LENGTH * 26.0 };
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);

    int inputDirection = setDirection(&direction);

    DrawTexturePro(
    emptyMaze,
    (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
    (Rectangle) { 0, GRID_LENGTH * 3, WIDTH, GRID_LENGTH * 31 },
    Vector2Zero(), 0, WHITE
);

    if (GetKeyPressed() != 0) {
      gameStarted = true;
      if (!PAUSE) gamePaused = false;
    }
    if (!gameStarted) {
      int textWidth = MeasureText("READY!", 30);
      DrawText("READY!", (WIDTH - textWidth) / 2, GRID_LENGTH * 20, 30, YELLOW);
    }
    if (gameStarted && !PAUSE && gamePaused) {
      int textWidth = MeasureText("PAUSE", 30);
      DrawText("PAUSE", (WIDTH - textWidth) / 2, GRID_LENGTH * 20, 30, YELLOW);
    }
    if (!gameStarted && !beginning && gamePaused) {
      PlaySound(audios[AUDIO_BEGINNING]);
      beginning = true;
    }
    if (PAUSE) gamePaused = !gamePaused;
    if (gameStarted && !gamePaused) {
      if (!IsSoundPlaying(audios[AUDIO_CHOMP])) PlaySound(audios[AUDIO_CHOMP]);

      // PACMAN MOVEMENT
      Vector2 nextPos = pacmanPosition;
      if (inputDirection == S_LEFT) nextPos.x -= SPEED * dt;
      if (inputDirection == S_RIGHT) nextPos.x += SPEED * dt;
      if (inputDirection == S_UP) nextPos.y -= SPEED * dt;
      if (inputDirection == S_DOWN) nextPos.y += SPEED * dt;

      //Corner check
      float margin = 4.0;
      float size = (float)GRID_LENGTH - margin;

      bool hitWall = 
          IsWall(nextPos.x + margin, nextPos.y + margin) ||
          IsWall(nextPos.x + size,   nextPos.y + margin) ||
          IsWall(nextPos.x + margin, nextPos.y + size)   ||
          IsWall(nextPos.x + size,   nextPos.y + size);

      if (!hitWall) {
          pacmanPosition = nextPos;
      }

      pacmanIndex = (int) (GetTime() / 0.075) % pacman.sprites;
    } else pacmanIndex = 2;

    // TODO: Implement the maze and detect collision ghosts
    // PACMAN BARE COLLISION
    if (pacmanPosition.x < -GRID_LENGTH) pacmanPosition.x = WIDTH;
    if (pacmanPosition.x > WIDTH) pacmanPosition.x = -GRID_LENGTH;
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

