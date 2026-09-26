Vector2 GetGhostSprite(Ghost gh) {
  Vector2 g = GetSpriteDirection(ghosts[gh.name], gh.direction);
  if (gh.state == FRIGHTENED) {
    g = frightened;
    double t = GetCurrentTime(frightenedTimer);
    if (t >= 5.5) g = ((int) (t / 0.25)) % 2 ? frightenedWhite : frightened;
  }
  if (gh.state == EATEN) g = GetSpriteDirection(eyes, gh.direction);
  return g;
}

void DrawGhost(Ghost gh, int index) {
  Vector2 g = GetGhostSprite(gh);
  Vector2 pos = gh.position;
  DrawTexturePro(
    characters,
    (Rectangle) { g.x + (index * UNIT_SPRITE_LENGTH), g.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { pos.x, pos.y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

void InitGhosts() {
  Vector2 ghostPositions[] = GHOST_HOMES;
  blinky = (Ghost) { BLINKY, SCATTER, ghostPositions[BLINKY], S_RIGHT };
  pinky  = (Ghost) { PINKY , SCATTER, ghostPositions[PINKY] , S_RIGHT };
  inky   = (Ghost) { INKY  , SCATTER, ghostPositions[INKY]  , S_RIGHT };
  clyde  = (Ghost) { CLYDE , SCATTER, ghostPositions[CLYDE] , S_RIGHT };
}

Ghost *g(int idx) {
  return idx == BLINKY ? &blinky
    :    idx == PINKY  ? &pinky
    :    idx == INKY   ? &inky
    :    idx == CLYDE  ? &clyde
    :    &(Ghost) { 0 };
}

double GetDistance(Vector2 tile1, Vector2 tile2) {
  return sqrt(
    pow(tile1.x - tile2.x, 2) +
    pow(tile1.y - tile2.y, 2)
  );
}

Vector2 AddToTile(Vector2 tile, int direction, int step) {
  if (direction == S_LEFT)  return (Vector2) { tile.x - step, tile.y };
  if (direction == S_DOWN)  return (Vector2) { tile.x, tile.y + step };
  if (direction == S_UP)    return (Vector2) { tile.x, tile.y - step };
  if (direction == S_RIGHT) return (Vector2) { tile.x + step, tile.y };
}
Vector2 GetSteppedTile(Vector2 pacmanTile, int step) {
  if (direction == S_LEFT) return (Vector2) { pacmanTile.x - step, pacmanTile.y };
  if (direction == S_DOWN) return (Vector2) { pacmanTile.x, pacmanTile.y + step };
  if (direction == S_UP)
    return (Vector2) { pacmanTile.x - step, pacmanTile.y - step };
  if (direction == S_RIGHT) return (Vector2) { pacmanTile.x + step, pacmanTile.y };
}

Vector2 GetTargetTile(Ghost ghost, Vector2 pacmanTile, Vector2 blinkyTile) {
  Vector2 scatters[] = {
    (Vector2) { GRID_WIDTH - 2, -1 },
    (Vector2) { 2, -1 },
    (Vector2) { GRID_WIDTH - 1, GRID_HEIGHT - 2 },
    (Vector2) { 1, GRID_HEIGHT - 2 },
  };

  if (ghost.state == SCATTER) return scatters[ghost.name];

  if (ghost.state == CHASE) {
    if (ghost.name == BLINKY) return pacmanTile;
    if (ghost.name == PINKY) return GetSteppedTile(pacmanTile, 4);
    if (ghost.name == INKY) {
      Vector2 intermediate = GetSteppedTile(pacmanTile, 2);
      Vector2 inkyTarget = Vector2Add(Vector2Scale(intermediate, 2), Vector2Scale(blinkyTile, -1));
      return inkyTarget;
    }
    if (ghost.name == CLYDE) {
      bool isEightTilesAway = GetDistance(Tileify(ghost.position), pacmanTile) >= 8;
      return isEightTilesAway ? pacmanTile : scatters[CLYDE];
    }
  }

  // TODO: Implement rng for FRIGHTENED state
  if (ghost.state == FRIGHTENED) return GHOST_GATE;

  if (ghost.state == EATEN) return GHOST_HOME;

  return GHOST_GATE;
}

bool IsGhostInHouse(Vector2 tile) {
  int houseLeft = 11, houseDown = 19, houseUp = 14, houseRight = 18;
  return houseLeft < tile.x && tile.x < houseRight &&
    houseUp < tile.y && tile.y < houseDown;
}

bool HitsWallNonetheless(Vector2 nextPositions[], int direction, int name) {
  bool hitWalls[] = HIT_WALLS(name);
  for (int i = 0; i < LENGTH(hitWalls); i++) if (hitWalls[i]) return true;
  return false;
}

bool SurroundedByWalls(Vector2 nextPositions[], int direction, int name) {
  bool hitWalls[] = HIT_WALLS(name);
  if (direction == S_LEFT)  return hitWalls[S_UP]   && hitWalls[S_DOWN];
  if (direction == S_DOWN)  return hitWalls[S_LEFT] && hitWalls[S_RIGHT];
  if (direction == S_UP)    return hitWalls[S_LEFT] && hitWalls[S_RIGHT];
  if (direction == S_RIGHT) return hitWalls[S_UP]   && hitWalls[S_DOWN];
  return false;
}

bool HitTwoWalls(Vector2 nextPositions[], int direction, int name) {
  bool hitWalls[] = HIT_WALLS(name);
  HIT_TWO_WALLS(S_LEFT , S_UP  , S_DOWN )
  HIT_TWO_WALLS(S_DOWN , S_LEFT, S_RIGHT)
  HIT_TWO_WALLS(S_UP   , S_LEFT, S_RIGHT)
  HIT_TWO_WALLS(S_RIGHT, S_UP  , S_DOWN )
  return false;
}

int DirectionWhenTwoWalls(Vector2 nextPositions[], int direction, int name) {
  bool hitWalls[] = HIT_WALLS(name);
  TWO_WALLS(S_LEFT , S_UP  , S_DOWN )
  TWO_WALLS(S_DOWN , S_LEFT, S_RIGHT)
  TWO_WALLS(S_UP   , S_LEFT, S_RIGHT)
  TWO_WALLS(S_RIGHT, S_UP  , S_DOWN )
}

bool IsGoodToTurn(Vector2 nextPositions[], int direction, int name, bool snap) {
  bool hitWalls[] = HIT_WALLS(name);
  return snap && (
    UNTURNABLE(S_LEFT , S_UP  , S_DOWN)  ||
    UNTURNABLE(S_DOWN , S_LEFT, S_RIGHT) ||
    UNTURNABLE(S_UP   , S_LEFT, S_RIGHT) ||
    UNTURNABLE(S_RIGHT, S_UP  , S_DOWN)
  ) && !HitsWallNonetheless(nextPositions, direction, name);
}

int Turn(Vector2 nextTiles[], Vector2 targetTile, int direction) {
  int dir1 = S_UP, dir2 = S_DOWN;
  if (direction == S_LEFT)  { dir1 = S_UP  ; dir2 = S_DOWN ; }
  if (direction == S_DOWN)  { dir1 = S_LEFT; dir2 = S_RIGHT; }
  if (direction == S_UP)    { dir1 = S_LEFT; dir2 = S_RIGHT; }
  if (direction == S_RIGHT) { dir1 = S_UP  ; dir2 = S_DOWN ; }

  double d1 = GetDistance(nextTiles[dir1], targetTile);
  double d2 = GetDistance(nextTiles[dir2], targetTile);

  return d1 > d2 ? dir2 : dir1;
}

int TurnOrGoStraight(Vector2 nextTiles[], Vector2 targetTile, int direction) {
  int turnDir = Turn(nextTiles, targetTile, direction);

  double d_straight = GetDistance(nextTiles[direction], targetTile);
  double d_turn = GetDistance(nextTiles[turnDir], targetTile);

  return d_straight > d_turn ? turnDir : direction;
}

int GetNextDirection(Ghost ghost, Vector2 targetTile) {
  int gDir = ghost.direction;
  int n = ghost.name;
  Vector2 ghostTile = Tileify(ghost.position);
  int snapCount = 0;

  Vector2 nextTiles[] = {
    AddToTile(ghostTile, S_LEFT , 1),
    AddToTile(ghostTile, S_DOWN , 1),
    AddToTile(ghostTile, S_UP   , 1),
    AddToTile(ghostTile, S_RIGHT, 1),
  };
  Vector2 nextPositions[] = {
    GetTilePosition(nextTiles[S_LEFT]),
    GetTilePosition(nextTiles[S_DOWN]),
    GetTilePosition(nextTiles[S_UP]),
    GetTilePosition(nextTiles[S_RIGHT]),
  };

  int dir = gDir;

  if (IsGhostInHouse(ghostTile)) {
    int leftOrRight = ghostTile.x < 13 ? S_RIGHT : ghostTile.x > 14 ? S_LEFT : S_UP;
    OpenGhostHouse(MAPS[n]);
    return ghostTile.y == 16 ? leftOrRight : S_UP;
  } else if (ghost.state != EATEN) CloseGhostHouse(MAPS[n]);

  for (int i = 0; i < LENGTH(nextTiles); i++) {
    bool backwards =
      (i == S_LEFT  && gDir == S_RIGHT) ||
      (i == S_DOWN  && gDir == S_UP)    ||
      (i == S_UP    && gDir == S_DOWN)  ||
      (i == S_RIGHT && gDir == S_LEFT);

    Vector2 pos = nextPositions[i];
    Vector2 currentPos = nextPositions[gDir];

    bool snap = Snaps(ghost.position, &snapCount);

    #if DEBUG
    if (ghost.name == BLINKY && IsGoodToTurn(nextPositions, gDir, n, snap)) printf("GOOD TO TURN\n");
    if (ghost.name == BLINKY)
    printf(
      "ghost = %d, state = %d, "
      "i = %d, dir = %d, gDir = %d, targetTile = (%.2f, %.2f)\n"
      "pos = (%.2f, %.2f), currentPos = (%.2f, %.2f), backwards = %d\n"
      "nextTiles[i] = (%.2f, %.2f), nextTiles[dir] = (%.2f, %.2f)\n"
      "will hit wall = %d, will currentPos hit = %d, is good to turn = %d\n"
      "hit two walls = %d, dir when two walls = %d, surrounded = %d\n"
      , ghost.name, ghost.state
      , i, dir, gDir
      , targetTile.x, targetTile.y
      , pos.x, pos.y, currentPos.x, currentPos.y, backwards
      , nextTiles[i].x, nextTiles[i].y, nextTiles[dir].x, nextTiles[dir].y
      , WillHitWall(pos, MAPS[n]), WillHitWall(currentPos, MAPS[n]), IsGoodToTurn(nextPositions, gDir)
      , HitTwoWalls(nextPositions, dir), DirectionWhenTwoWalls(nextPositions, dir)
      , SurroundedByWalls(nextPositions, dir)
    );
    #endif

    if (backwards) continue;
    if (SurroundedByWalls(nextPositions, gDir, n)) { dir = gDir; break; }
    if (HitTwoWalls(nextPositions, gDir, n)) {
      dir = DirectionWhenTwoWalls(nextPositions, gDir, n);
      break;
    }
    if (WillHitWall(currentPos, MAPS[n])) {
      dir = Turn(nextTiles, targetTile, gDir);
      break;
    }
    if (IsGoodToTurn(nextPositions, gDir, n, snap)) dir = TurnOrGoStraight(nextTiles, targetTile, gDir);
  }

  return dir;
}

void GoToTile(Ghost *ghost, Vector2 tile, float delta) {
  float distance = (ghost->state == EATEN ? EATEN_GHOST_SPEED : GHOST_SPEED) * delta;

  ghost->direction = GetNextDirection(*ghost, tile);
  ghost->position = CanTurn(ghost->position, ghost->direction, MAPS[ghost->name])
    ? MoveInDirection(ghost->position, ghost->direction, distance)
    : GetCoordinates(ghost->position);

  #if DEBUG
  printf("(%.2f, %.2f), %d\n", tile.x, tile.y, ghost->direction);
  #endif

  // GHOST WALL COLLISION
  int up = 4, down = 32;
  if (ghost->position.x < -GRID_LENGTH) ghost->position.x = WIDTH - 1;
  if (ghost->position.x >= WIDTH)       ghost->position.x = -GRID_LENGTH;
  if (ghost->position.y < GRID_LENGTH * up)   ghost->position.y = GRID_LENGTH * up;
  if (ghost->position.y > GRID_LENGTH * down) ghost->position.y = GRID_LENGTH * down;
}

void RotateGhost(Ghost *ghost, int prevState, int newState) {
  bool rotatable =
    ((prevState == SCATTER || prevState == CHASE  ) && newState == FRIGHTENED) ||
    ( prevState == SCATTER || newState  == CHASE  ) ||
    ( prevState == CHASE   || newState  == SCATTER);
  if (!rotatable) return;
  if (ghost->direction == S_LEFT)  ghost->direction = S_RIGHT;
  if (ghost->direction == S_DOWN)  ghost->direction = S_UP;
  if (ghost->direction == S_UP)    ghost->direction = S_DOWN;
  if (ghost->direction == S_RIGHT) ghost->direction = S_LEFT;
}

void ChangeState(Ghost *ghost, int state) {
  if (SCATTER > state || state > EATEN) return;
  RotateGhost(ghost, ghost->state, state);
  ghost->state = state;
}

bool BlinkyWillChase() {
  return (
    BLINKY_CHASE( 1,  1,  20) ||
    BLINKY_CHASE( 2,  2,  30) ||
    BLINKY_CHASE( 3,  5,  40) ||
    BLINKY_CHASE( 6,  8,  50) ||
    BLINKY_CHASE( 9, 11,  60) ||
    BLINKY_CHASE(12, 14,  80) ||
    BLINKY_CHASE(15, 18, 100) ||
    BLINKY_CHASE(19, MAX_LEVEL, 120)
  );
}

int GetGhostState(Ghost gh, bool frightened) {
  if (frightened) return FRIGHTENED;

  if (gh.name == BLINKY && BlinkyWillChase()) return CHASE;

  int states[3][7] = {
    { 7, 20, 7, 20, 5,           20, 5 },
    { 7, 20, 7, 20, 5, 17 * 60 + 14, 1 },
    { 5, 20, 5, 20, 5, 17 * 60 + 14, 1 }
  };
  int stateIndex = level == 1 ? 0 : 2 <= level && level <= 4 ? 1 : 2;

  int totalTime = 0;
  int state;

  for (int i = 0; i < LENGTH(states[stateIndex]); i++) {
    int t = states[stateIndex][i];
    totalTime += t;
    double p = GetCurrentTime(levelTimer);
    if (totalTime - t <= p && p <= totalTime) return i % 2;
  }

  return CHASE;
}

void MakeFrightened() {
  ghostsEaten = 0;
  for (int i = 0; i < LENGTH(ghosts); i++)
    ChangeState(g(i), FRIGHTENED);
  SetTimer(&frightenedTimer);
}

void GhostToHome(Ghost *ghost, float delta) {
  if (ghost->state != EATEN) return;

  float distance = EATEN_GHOST_SPEED * delta;
  Vector2 ghostTile = Tileify(ghost->position);
  int n = ghost->name;

  if (ghostTile.x == GHOST_GATE.x && GHOST_HOME.y >= ghostTile.y && ghostTile.y >= GHOST_GATE.y) {
    OpenGhostHouse(MAPS[n]);
    ghost->direction = S_DOWN;
    ghost->position = MoveInDirection(ghost->position, ghost->direction, distance);
    // INFO: BRUTE FORCE, THIS IS THE POINT WHERE I LOSE ALL SANITY AND BRUTE FORCE
    // GOOD BRUTE FORCE ^-^
    for (float i = 15; i <= 16; i += 0.2)
      if (ghostTile.y == i) ghost->position.y = GetTilePosition((Vector2) { 0, i + 1 }).y;
  }
  if (ghostTile.x == GHOST_HOME.x && ghostTile.y == GHOST_HOME.y)
    ghost->state = SCATTER;
}
