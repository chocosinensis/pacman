void CoreLogic() {
  int pacmanIndex = 2;
  int ghostIndeces[GHOSTS] = { 0 };
  int blorbColor = PELLET_COLOR;

  Vector2 pacmanPosition = (Vector2) { (float) GRID_LENGTH * 13.5, (float) GRID_LENGTH * 26.0 };
  Vector2 pacmanTile = Tileify(pacmanPosition);
  Vector2 ghostPositions[] = {
    (Vector2) { (12 + BLINKY) * GRID_LENGTH, 17 * GRID_LENGTH },
    (Vector2) { (12 + PINKY)  * GRID_LENGTH, 17 * GRID_LENGTH },
    (Vector2) { (12 + INKY)   * GRID_LENGTH, 17 * GRID_LENGTH },
    (Vector2) { (12 + CLYDE)  * GRID_LENGTH, 17 * GRID_LENGTH },
  };

  InitGhosts(ghostPositions);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    float distance = SPEED * dt;

    BeginDrawing();
    ClearBackground(BLACK);

    QueueDirection(&queuedDirection);
    DrawTexturePro(
      emptyMaze,
      (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
      (Rectangle) { 0, GRID_LENGTH * 3, WIDTH, GRID_LENGTH * 31 },
      Vector2Zero(), 0, WHITE
    );

    // Score at top
    DrawText(TextFormat("1UP  %04d", currentScore), GRID_LENGTH * 3, GRID_LENGTH * 1, FONT_SIZE - 3, WHITE);
    DrawText(TextFormat("HIGH %04d", highScore), GRID_LENGTH * 19.5, GRID_LENGTH * 1, FONT_SIZE - 3, WHITE);

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

    // TODO: fix gameover
    if (lives == 0) {
      gameStarted = false;
      gamePaused = true;
      beginning = true;
      int textWidth = MeasureText("GAME OVER", FONT_SIZE);
      DrawText("GAME OVER", (WIDTH - textWidth) / 2, GRID_LENGTH * 20, FONT_SIZE, YELLOW);
      return;
    }

    // Draw orbs and blorbs
    DrawOrbs();
    DrawBlorbs(blorbColor);

    // TODO: Implement ghost movement independent of each other
    // Ghosts are rendered for the first time here
    for (int i = 0; i < LENGTH(ghosts); i++) DrawGhost(*g(i), ghostIndeces[i]);

    if (lives >= 0 && GetKeyPressed() != 0) {
      gameStarted = true;
      if (!PRESSED_PAUSE) gamePaused = false;
    }
    if (!gameStarted) {
      int textWidth = MeasureText("READY!", FONT_SIZE);
      DrawText("READY!", (WIDTH - textWidth) / 2, GRID_LENGTH * 20, FONT_SIZE, YELLOW);
    }
    if (gameStarted && !PRESSED_PAUSE && gamePaused) {
      int textWidth = MeasureText("PAUSE", FONT_SIZE);
      DrawText("PAUSE", (WIDTH - textWidth) / 2, GRID_LENGTH * 20, FONT_SIZE, YELLOW);
    }
    if (!gameStarted && !beginning && gamePaused) {
      Play(AUDIO_START);
      beginning = true;
    }
    if (PRESSED_PAUSE) gamePaused = !gamePaused;

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
      Play(AUDIO_SIREN);

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
        Vector2 snap = GetCoordinates(pacmanPosition);

        bool isClose =
          fabsf(pacmanPosition.x - snap.x) < GRID_LENGTH / 5 &&
          fabsf(pacmanPosition.y - snap.y) < GRID_LENGTH / 5;

        if (isClose && CanTurn(snap, queuedDirection)) {
          pacmanPosition = snap;
          direction = queuedDirection;
        }
      }

      Vector2 nextPos = MoveInDirection(pacmanPosition, direction, distance);
      if (!WillHitWall(nextPos)) pacmanPosition = nextPos;

      pacmanPosition.x = (int) round(pacmanPosition.x);
      pacmanPosition.y = (int) round(pacmanPosition.y);
      pacmanTile = Tileify(pacmanPosition);

      // Eating
      EatPellet(pacmanPosition.x, pacmanPosition.y);

      for (int i = 0; i < LENGTH(ghosts); i++) {
        Ghost *gh = g(i);
        bool reachedGate = false;
        Vector2 targetTile = reachedGate ? GHOST_HOME : GetTargetTile(*gh, pacmanTile);
        GoToTile(gh, targetTile, distance);
        GhostToHome(gh, distance, &reachedGate);
        CollideWithGhost(gh, pacmanPosition);
        #if DEBUG
        printf("POSITION FOR %d : (%.2f, %.2f)\n", gh->name, gh->position.x, gh->position.y);
        #endif
      }

      pacmanIndex = (int) (GetTime() / ANIMATION_SPEED) % pacman.sprites;
      for (int i = 0; i < LENGTH(ghostIndeces); i++)
        ghostIndeces[i] = g(i)->state == EATEN ? 0 : (int) (GetTime() / ANIMATION_SPEED) % ghosts[i].sprites;
      blorbColor = ((int) (GetTime() / 0.2) % 2) ? PELLET_COLOR : 0x00000000;
    } else pacmanIndex = 2;

    if (gameOver && !gameStarted) {
      pacmanPosition = (Vector2) { (float) GRID_LENGTH * 13.5, (float) GRID_LENGTH * 26.0 };
      pacmanTile = Tileify(pacmanPosition);
      for (int i = 0; i < LENGTH(ghosts); i++)
        g(i)->position = (Vector2) { (12 + i) * GRID_LENGTH, 17 * GRID_LENGTH };
      gameOver = false;
      // gamePaused = false;
    }

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
