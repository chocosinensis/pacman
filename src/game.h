void CoreLogic() {
  int pacmanIndex = 2;
  Vector2 pacmanPosition = { (float) GRID_LENGTH * 13.5, (float) GRID_LENGTH * 26.0 };

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);

    int inputDirection = direction;

    DrawTexturePro(
      emptyMaze,
      (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
      (Rectangle) { 0, GRID_LENGTH * 3, WIDTH, GRID_LENGTH * 31 },
      Vector2Zero(), 0, WHITE
    );

    // Score at top
    DrawText(TextFormat("1UP  %04d", currentScore), GRID_LENGTH * 3, GRID_LENGTH * 1, 20, WHITE);
    DrawText(TextFormat("HIGH %04d", highScore), GRID_LENGTH * 19.5, GRID_LENGTH * 1, 20, WHITE);

    // INFO: Hearts at bottom (ironic)
    // No heart is at bottom if you use i++ and not ++i
    // Also, just because open mouthed pacmans
    // look like hearts doesn't automatically
    // make them hearts
    for (int i = 0; i < lives; i++) {
      float lifeX = (GRID_LENGTH * 2) + (i * GRID_LENGTH * 1.5f);
      float lifeY = GRID_LENGTH * 34.5;

      DrawPacman(lifeX, lifeY, S_LEFT, 0);
    }

    // Draw orbs and blorbs
    DrawOrbs();
    DrawBlorbs();

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
      #if SOUND_ALLOWED
      PlaySound(audios[AUDIO_START]);
      #endif
      beginning = true;
    }
    if (PAUSE) gamePaused = !gamePaused;
    if (gameStarted && !gamePaused) {
      #if SOUND_ALLOWED
      if (!IsSoundPlaying(audios[AUDIO_SIREN])) PlaySound(audios[AUDIO_SIREN]);
      #endif

      #if DEBUG
      // INFO: UGLY AHH CODE
      // Red square debug, DELETE KORTE HOBEEE PORE
      // NO NEED TO DELETE NOW 😉
      for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
          // Render world position taking into account the 3-tile top offset
          float worldX = (x * GRID_LENGTH);
          float worldY = (y * GRID_LENGTH);
          if (IsWall(worldX + 2, worldY + 2)) {
            DrawRectangleLines(worldX, worldY, GRID_LENGTH, GRID_LENGTH, RED);
          }
        }
      }
      #endif

      // PACMAN MOVEMENT
      Vector2 nextPos = pacmanPosition;
      if (inputDirection == S_LEFT) nextPos.x -= SPEED * dt;
      if (inputDirection == S_RIGHT) nextPos.x += SPEED * dt;
      if (inputDirection == S_UP) nextPos.y -= SPEED * dt;
      if (inputDirection == S_DOWN) nextPos.y += SPEED * dt;

      // Corner check
      float margin = GRID_LENGTH / 10.0;
      float size = (float) GRID_LENGTH - margin;

      bool hitWall =
        IsWall(nextPos.x + margin, nextPos.y + margin) ||
        IsWall(nextPos.x + size,   nextPos.y + margin) ||
        IsWall(nextPos.x + margin, nextPos.y + size)   ||
        IsWall(nextPos.x + size,   nextPos.y + size);

      if (!hitWall) {
        pacmanPosition = nextPos;
      } // else 
        // TODO: Implement wall collision perfectly
        inputDirection = setDirection(&direction);

      // Eating
      // TODO: FIX THE BUG FOR POSITION REGARDING PELLET EATING
      // AS WELL AS THE BUG FOR MAZE-TRAVERSAL
      EatPellet(pacmanPosition.x, pacmanPosition.y);

      pacmanIndex = (int) (GetTime() / 0.075) % pacman.sprites;
    } else pacmanIndex = 2;

    // TODO: Implement the maze and detect collision ghosts
    // PACMAN BARE COLLISION
    if (pacmanPosition.x < -GRID_LENGTH) pacmanPosition.x = WIDTH;
    if (pacmanPosition.x > WIDTH) pacmanPosition.x = -GRID_LENGTH;

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

  InitGameState();
  CoreLogic();

  UnloadTextures();
  UnloadAudios();

  CloseAudioDevice();
  CloseWindow();
}

