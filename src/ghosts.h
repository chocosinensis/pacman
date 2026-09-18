void DrawGhost(Ghost gh, int index) {
  Vector2 g = GetSpriteDirection(ghosts[gh.name], gh.direction);
  if (gh.state == FRIGHTENED) g = frightened;
  if (gh.state == EATEN) g = GetSpriteDirection(eyes, gh.direction);

  Vector2 pos = gh.position;
  DrawTexturePro(
    characters,
    (Rectangle) { g.x + (index * UNIT_SPRITE_LENGTH), g.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { pos.x, pos.y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

void InitGhosts(Vector2 ghostPositions[]) {
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

Vector2 GetTargetTile(Ghost ghost, Vector2 pacmanTile) {
  Vector2 scatters[] = {
    (Vector2) { -1, GRID_WIDTH - 2 },
    (Vector2) { -1, 2 },
    (Vector2) { GRID_HEIGHT - 2, 1 },
    (Vector2) { GRID_HEIGHT - 2, GRID_WIDTH - 1 }
  };

  if (ghost.state == SCATTER) return scatters[ghost.name];

  if (ghost.state == CHASE) {
    if (ghost.name == BLINKY) return pacmanTile;
    if (ghost.name == PINKY) return GetSteppedTile(pacmanTile, 4);
    // TODO: Implement inky's target tile
    if (ghost.name == INKY) {
      Vector2 intermediate = GetSteppedTile(pacmanTile, 2);
      return scatters[INKY];
    }
    if (ghost.name == CLYDE) {
      bool isEightTilesAway = GetDistance(Tileify(ghost.position), pacmanTile) >= 8;
      return isEightTilesAway ? pacmanTile : scatters[CLYDE];
    }
  }

  // TODO: Implement rng for FRIGHTENED state
  if (ghost.state == FRIGHTENED) return GHOST_GATE;

  if (ghost.state == EATEN) return GHOST_GATE;

  return GHOST_GATE;
}

bool IsNextWall(Vector2 tiles[], int dir, int idx, int direction) {
  Vector2 pos = GetTilePosition(tiles[idx]);
  return !WillHitWall(pos) && (dir == direction || idx == direction);
}

bool IsGhostInHouse(Vector2 tile) {
  int houseLeft = 11, houseDown = 19, houseUp = 14, houseRight = 18;
  return houseLeft < tile.x && tile.x < houseRight &&
    houseUp < tile.y && tile.y < houseDown;
}

bool SurroundedByWalls(Vector2 nextTiles[], int direction) {
  bool hitWalls[] = HIT_WALLS;
  if (direction == S_LEFT)  return hitWalls[S_UP]   && hitWalls[S_DOWN];
  if (direction == S_DOWN)  return hitWalls[S_LEFT] && hitWalls[S_RIGHT];
  if (direction == S_UP)    return hitWalls[S_LEFT] && hitWalls[S_RIGHT];
  if (direction == S_RIGHT) return hitWalls[S_UP]   && hitWalls[S_DOWN];
  return false;
}

int DirectionWhenTwoWalls(Vector2 nextTiles[], int direction) {
  bool hitWalls[] = HIT_WALLS;
  TWO_WALLS(S_LEFT , S_UP  , S_DOWN )
  TWO_WALLS(S_DOWN , S_LEFT, S_RIGHT)
  TWO_WALLS(S_UP   , S_LEFT, S_RIGHT)
  TWO_WALLS(S_RIGHT, S_UP  , S_DOWN )
}

// TODO: Implement GetNextDirection function
// INFO: MORE WORK TO BE DONE
int GetNextDirection(Ghost ghost, Vector2 targetTile) {
  Vector2 ghostTile = Tileify(ghost.position);
  Vector2 nextTiles[] = {
    AddToTile(ghostTile, S_LEFT , 1),
    AddToTile(ghostTile, S_DOWN , 1),
    AddToTile(ghostTile, S_UP   , 1),
    AddToTile(ghostTile, S_RIGHT, 1),
  };
  int gDir = ghost.direction;

  int dir = S_UP;

  if (IsGhostInHouse(ghostTile)) {
    int leftOrRight = ghostTile.x < 13 ? S_RIGHT : ghostTile.x > 14 ? S_LEFT : S_UP;
    return ghostTile.y == 16 ? leftOrRight : S_UP;
  }

  for (int i = 0; i < LENGTH(nextTiles); i++) {
    bool backwards = (i == S_LEFT  && gDir == S_RIGHT)
      || (i == S_DOWN  && gDir == S_UP)
      || (i == S_UP    && gDir == S_DOWN)
      || (i == S_RIGHT && gDir == S_LEFT);

    if (backwards) continue;

    Vector2 pos = GetTilePosition(nextTiles[i]);
    if (SurroundedByWalls(nextTiles, i)) { continue; }

    double d_i = GetDistance(nextTiles[i], targetTile);
    double d = GetDistance(nextTiles[dir], targetTile);

    #if DEBUG
    printf(
      "ghost = %d, i = %d, dir = %d, d_i = %.2lf, d = %.2lf, "
      "nextTiles[i] = (%.2f, %.2f), nextTiles[dir] = (%.2f, %.2f), "
      "will hit wall = %d\n",
      ghost.name, i, dir, d_i, d,
      nextTiles[i].x, nextTiles[i].y, nextTiles[dir].x, nextTiles[dir].y, WillHitWall(pos)
    );
    #endif

    if (!backwards && WillHitWall(ghost.position)) { dir = DirectionWhenTwoWalls(nextTiles, i); continue; }
    if (!backwards && d_i < d && !WillHitWall(pos)) dir = i;
    if (!backwards && d_i == d) {
      if (IsNextWall(nextTiles, dir, i, S_UP   )) { dir = S_UP;    break; }
      if (IsNextWall(nextTiles, dir, i, S_LEFT )) { dir = S_LEFT;  break; }
      if (IsNextWall(nextTiles, dir, i, S_DOWN )) { dir = S_DOWN;  break; }
      if (IsNextWall(nextTiles, dir, i, S_RIGHT)) { dir = S_RIGHT; break; }
    }
  }

  return dir;
}

// TODO: Implement GoToTile function
void GoToTile(Ghost *ghost, Vector2 tile, float distance) {
  ghost->direction = GetNextDirection(*ghost, tile);
  ghost->position = CanTurn(ghost->position, ghost->direction)
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

void MakeFrightened() {
  ghostsEaten = 0;
  for (int i = 0; i < LENGTH(ghosts); i++)
    ChangeState(g(i), FRIGHTENED);
}

void GhostToHome(Ghost *ghost, float distance, bool *reachedGate) {
  if (ghost->state != EATEN) return;
  if (ghost->position.x == GHOST_GATE.x && ghost->position.y == GHOST_GATE.y)
    *reachedGate = true;
    // GoToTile(ghost, GHOST_HOME, distance);
  if (ghost->position.x == GHOST_HOME.x && ghost->position.y == GHOST_HOME.y)
    ghost->state = SCATTER;
}
