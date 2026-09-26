void DrawPacman(int x, int y, int direction, int index) {
  Vector2 pc = GetSpriteDirection(pacman, direction);
  DrawTexturePro(
    characters,
    (Rectangle) { pc.x + (index * UNIT_SPRITE_LENGTH), pc.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

Vector2 MoveInDirection(Vector2 pos, int dir, float distance) {
  if (dir == S_LEFT)  pos.x -= distance;
  if (dir == S_RIGHT) pos.x += distance;
  if (dir == S_UP)    pos.y -= distance;
  if (dir == S_DOWN)  pos.y += distance;
  return pos;
}

void EatPellet(float x, float y) {
  bool orb = IsOrb(x, y);
  bool blorb = IsBlorb(x, y);

  int gridX = (int) (x / GRID_LENGTH);
  int gridY = (int) (y / GRID_LENGTH);

  if (!orb && !blorb) return;

  MAP[gridY][gridX] = ORB_EATEN;
  AddScore(orb ? SCORE_PELLET : blorb ? SCORE_POWER_PELLET : 0);
  pelletsEaten++;

  if (blorb) MakeFrightened();

  if (orb) Play(AUDIO_EATDOT);
  if (blorb) Play(AUDIO_FRIGHT);
}

void EatFruit(float x, float y) {
  double fruitT = GetCurrentTime(fruitTimer);
  bool noFruit = lives == 0 || !gameStarted || gameStarted && !PRESSED_PAUSE && gamePaused;
  fruitExists = !noFruit && fruitT > FRUIT_TIME && pelletsEaten > 70 && lives < MAX_LIVES;
  if (!fruitExists) return;
  DrawFruit();
  if (fruitT > FRUIT_TIME + 10) {
    SetTimer(&fruitTimer);
    return;
  }
  if (x == GRID_LENGTH * 13.5 && y == GRID_LENGTH * 20) {
    AddLife();
    AddScore(SCORE_FRUIT);
    Play(AUDIO_EATFRUIT);
    SetTimer(&fruitTimer);
  }
}

void CollideWithGhost(Ghost *ghost, Vector2 pacmanPosition) {
  Vector2 ghostTile = Tileify(ghost->position);
  Vector2 pacmanTile = Tileify(pacmanPosition);
  bool hasCollided = ghostTile.x == pacmanTile.x && ghostTile.y == pacmanTile.y;
  if (hasCollided) {
    if (ghost->state == FRIGHTENED) {
      ghostsEaten++;
      ChangeState(ghost, EATEN);
      AddScore(pow(SCORE_GHOST / 100, ghostsEaten) * 100);
      Play(AUDIO_EATGHOST);
    }
    if (ghost->state == SCATTER || ghost->state == CHASE)
      // TODO: Uncomment for functionality to work
      if (!SUPERPOWER_BASE) GetEaten();
      printf("");
  }
}

void GetEaten() {
  gotEatenStart = true;
  gameStarted = false;
  gamePaused = true;
  beginning = false;
  LoseLife();
  UpdatePlayerDetails();
  SetTimer(&gotEatenTimer);

  Play(AUDIO_DEATH);
}

void AnimateGameOver(Vector2 pacmanPosition) {
  int idx = 0;
  int DEAD_SPRITES = 11;

  // for (int i = 0; i < GHOSTS; i++) {
  //   g(i)->position = (Vector2) { -GRID_LENGTH, -GRID_LENGTH };
  // }

  double time = 1;
  while (GetCurrentTime(gotEatenTimer) < time && idx != DEAD_SPRITES + 1) {
    ClearBackground(BLACK);
    DrawBaseElements(PELLET_COLOR);
    DrawTexturePro(
      characters,
      (Rectangle) {
        dead.x + (idx * UNIT_SPRITE_LENGTH), dead.y,
        UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH
      },
      (Rectangle) { pacmanPosition.x, pacmanPosition.y, GRID_LENGTH, GRID_LENGTH },
      Vector2Zero(), 0, WHITE
    );
    if (GetCurrentTime(gotEatenTimer) >= idx * time / (DEAD_SPRITES * 1.0)) idx++;
    EndDrawing();
  }

  gotEatenEnd = true;
  gotEatenStart = false;
}

