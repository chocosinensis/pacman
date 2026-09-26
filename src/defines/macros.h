// ghosts.h
#define SET_GHOST_HOME(ghost) ((Vector2) { (12 + ghost) * GRID_LENGTH, 17 * GRID_LENGTH })
#define GHOST_HOMES { \
    SET_GHOST_HOME(BLINKY), \
    SET_GHOST_HOME(PINKY), \
    SET_GHOST_HOME(INKY), \
    SET_GHOST_HOME(CLYDE), \
  }

#define HIT_WALLS(name) { \
    WillHitWall(nextPositions[S_LEFT] , MAPS[(name)]), \
    WillHitWall(nextPositions[S_DOWN] , MAPS[(name)]), \
    WillHitWall(nextPositions[S_UP]   , MAPS[(name)]), \
    WillHitWall(nextPositions[S_RIGHT], MAPS[(name)]) \
  }

#define HIT_TWO_WALLS(dir1, dir2, dir3) \
  if (direction == (dir1) && hitWalls[(dir1)]) { \
    return hitWalls[(dir2)] || hitWalls[(dir3)]; }

#define TWO_WALLS(dir1, dir2, dir3) \
  if (direction == (dir1) && hitWalls[(dir1)]) { \
    if (hitWalls[(dir2)]) return (dir3); \
    if (hitWalls[(dir3)]) return (dir2); \
    return (dir1); \
  }

#define UNTURNABLE(dir1, dir2, dir3) (direction == (dir1) && (!hitWalls[(dir2)] || !hitWalls[(dir3)]))

#define BLINKY_CHASE(lvl1, lvl2, orbs) ( \
    (lvl1) <= level && level <= (lvl2) && \
    (orbs) >= (TOTAL_PELLETS - pelletsEaten) \
  )
