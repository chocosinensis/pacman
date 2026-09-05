void DrawGhost(int x, int y, int direction, int name, int index) {
  Vector2 g = GetSpriteDirection(ghosts[name], direction);
  DrawTexturePro(
    characters,
    (Rectangle) { g.x + (index * UNIT_SPRITE_LENGTH), g.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

void InitGhosts(Vector2 ghostPositions[]) {
  blinky = (Ghost) { BLINKY, SCATTER, ghostPositions[BLINKY], S_RIGHT };
  pinky  = (Ghost) { PINKY,  SCATTER, ghostPositions[PINKY],  S_RIGHT };
  inky   = (Ghost) { INKY,   SCATTER, ghostPositions[INKY],   S_RIGHT };
  clyde  = (Ghost) { CLYDE,  SCATTER, ghostPositions[CLYDE],  S_RIGHT };
}

Ghost *g(int idx) {
  return idx == BLINKY ? &blinky
    : idx == PINKY ? &pinky
    : idx == INKY ? &inky
    : idx == CLYDE ? &clyde
    : &(Ghost) { 0 };
}

double GetDistance(Vector2 tile1, Vector2 tile2) {
  return sqrt(
    pow(tile1.x - tile2.x, 2) +
    pow(tile1.y - tile2.y, 2)
  );
}

Vector2 GetSteppedTile(Vector2 pacmanTile, int step) {
  if (direction == S_LEFT) return (Vector2) { pacmanTile.x - step, pacmanTile.y };
  if (direction == S_DOWN) return (Vector2) { pacmanTile.x, pacmanTile.y + 2 };
  if (direction == S_UP)
    return (Vector2) { pacmanTile.x - step, pacmanTile.y - step };
  if (direction == S_RIGHT) return (Vector2) { pacmanTile.x + 2, pacmanTile.y };
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

int GetNextDirection(Ghost ghost, Vector2 targetTile) {
  Vector2 ghostTile = Tileify(ghost.position);
  double d = GetDistance(ghostTile, targetTile);
  return S_RIGHT;
}

// TODO: Implement GoToTile function
void GoToTile(Ghost ghost, Vector2 tile) {}
