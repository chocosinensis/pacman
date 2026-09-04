void CoreLogic() {
  int pacmanIndex = 2;
  Vector2 pacmanPosition = { (float) GRID_LENGTH * 13.5, (float) GRID_LENGTH * 26.0 };
  int blorbColor = PELLET_COLOR;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);

    queueDirection(&queuedDirection);
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
    DrawBlorbs(blorbColor);

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

    // TODO: Implement the maze and detect collision ghosts
    // PACMAN BARE COLLISION
    if (pacmanPosition.x < -GRID_LENGTH) {
      queuedDirection = S_LEFT;
      pacmanPosition.x = WIDTH - 1; // subtracted 1 b/c otherwise queuedDirection was messing up
    }
    if (pacmanPosition.x >= WIDTH) { // changed > to a >= b/c otherwise queuedDirection was messing up
      queuedDirection = S_RIGHT;
      pacmanPosition.x = -GRID_LENGTH;
    }

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
      if (queuedDirection != direction) {
        Vector2 snap = getCoordinates(pacmanPosition);

        bool isClose =
          fabsf(pacmanPosition.x - snap.x) < 4 &&
          fabsf(pacmanPosition.y - snap.y) < 4;

        if (isClose && CanTurn(snap, queuedDirection)) {
          pacmanPosition = snap;
          direction = queuedDirection;
        }
      }

      Vector2 nextPos = MoveInDirection(pacmanPosition, direction, SPEED * dt);
      if (!WillHitWall(nextPos)) pacmanPosition = nextPos;

      pacmanPosition.x = (int) round(pacmanPosition.x);
      pacmanPosition.y = (int) round(pacmanPosition.y);

      // Eating
      EatPellet(pacmanPosition.x, pacmanPosition.y);

      pacmanIndex = (int) (GetTime() / 0.075) % pacman.sprites;
      blorbColor = ((int) (GetTime() / 0.2) % 2) ? PELLET_COLOR : 0x00000000;
    } else pacmanIndex = 2;

    DrawPacman(pacmanPosition.x, pacmanPosition.y, direction, pacmanIndex);

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
