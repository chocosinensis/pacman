void CoreLogic() {
  int pacmanIndex = 2;
  int ghostIndeces[GHOSTS] = { 0 };
  int blorbColor = PELLET_COLOR;

  Vector2 pacmanPosition = PACMAN_STARTING_POSITION;
  Vector2 pacmanTile = Tileify(pacmanPosition);

  InitGhosts();

  while (!WindowShouldClose()) {
    float delta = GetFrameTime();
    float playerDistance = PACMAN_SPEED * delta;
    if (SUPERPOWER_SPEED) playerDistance = SUPER_SPEED * delta;

    BeginDrawing();
    ClearBackground(BLACK);

    // if (playButtonPressed && PRESSED_QUIT) QuitFromGame();
    // if (!playButtonPressed) {
    //   beginning = false;
    //   RenderMainMenu();
    //   EndDrawing();
    //   continue;
    // }

    QueueDirection(&queuedDirection);
    DrawBaseElements(blorbColor);

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

    if (lives == 0) {
      gameOver = true;
      gameStarted = false;
      gamePaused = true;
      beginning = true;
      RenderTextInGame("GAME OVER");
    }

    if (gameOver) {
      if (PRESSED_RESTART) InitGameState();
      EndDrawing();
      continue;
    }

    // Ghosts are rendered for the first time here
    for (int i = 0; i < LENGTH(ghosts); i++) DrawGhost(*g(i), ghostIndeces[i]);

    // INFO: THIS IS WHERE THE GAME STARTS
    if (lives >= 0 && !gotEatenStart && GetKeyPressed() != 0) {
      if (!gameStarted) InitTimers();
      gameStarted = true;
      if (!PRESSED_PAUSE) gamePaused = false;
    }
    if (!gameStarted) RenderTextInGame("READY!");
    if (gameStarted && !PRESSED_PAUSE && gamePaused) RenderTextInGame("PAUSE");
    if (!gameStarted && !beginning && gamePaused) {
      Play(AUDIO_START);
      beginning = true;
    }
    if (PRESSED_PAUSE) gamePaused = !gamePaused;
    if (IsEveryPelletEaten(pelletsEaten)) NextLevel(&pacmanPosition);

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

        if (isClose && CanTurn(snap, queuedDirection, MAP)) {
          pacmanPosition = snap;
          direction = queuedDirection;
        }
      }

      Vector2 nextPos = MoveInDirection(pacmanPosition, direction, playerDistance);
      if (!WillHitWall(nextPos, MAP)) pacmanPosition = nextPos;

      pacmanPosition.x = (int) round(pacmanPosition.x);
      pacmanPosition.y = (int) round(pacmanPosition.y);
      pacmanTile = Tileify(pacmanPosition);

      // Eating
      EatPellet(pacmanPosition.x, pacmanPosition.y);

      for (int i = 0; i < LENGTH(ghosts); i++) {
        Ghost *gh = g(i);
        Vector2 blinkyTile = Tileify(g(BLINKY)->position);
        Vector2 targetTile = GetTargetTile(*gh, pacmanTile, blinkyTile);
        if (gh->state != EATEN) gh->state = GetGhostState(*gh, gh->state == FRIGHTENED);
        GoToTile(gh, targetTile, delta);
        GhostToHome(gh, delta);
        CollideWithGhost(gh, pacmanPosition);
        if (gh->state == FRIGHTENED && GetCurrentTime(frightenedTimer) >= 8)
          gh->state = GetGhostState(*gh, false);
        #if DEBUG
        printf("POSITION FOR %d : (%.2f, %.2f)\n", gh->name, gh->position.x, gh->position.y);
        #endif
      }

      pacmanIndex = (int) (GetTime() / ANIMATION_SPEED) % pacman.sprites;
      for (int i = 0; i < LENGTH(ghostIndeces); i++)
        ghostIndeces[i] = g(i)->state == EATEN ? 0 : (int) (GetTime() / ANIMATION_SPEED) % ghosts[i].sprites;
      blorbColor = ((int) (GetTime() / 0.2) % 2) ? PELLET_COLOR : 0x00000000;
    } else pacmanIndex = 2;

    if (!gotEatenStart && gotEatenEnd && !gameStarted) {
      MiniReset();
      pacmanPosition = PACMAN_STARTING_POSITION;
      pacmanTile = Tileify(pacmanPosition);
      InitGhosts();
      gotEatenEnd = false;
      // gamePaused = false;
    }

    if (gotEatenStart) {
      AnimateGameOver(pacmanPosition);
      continue;
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
