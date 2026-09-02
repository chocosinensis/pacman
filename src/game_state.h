bool gameStarted = false;
bool beginning = false;
bool gamePaused = true;

int direction = S_LEFT;

int currentScore = 0;
int highScore = 0;
int lives = MAX_LIVES;

void InitGameState(void) {
    currentScore = 0;
    lives = MAX_LIVES;
}

void AddScore(int points) {
    currentScore += points;
    if (currentScore > highScore) {
        highScore = currentScore;
    }
}

void LoseLife(void) {
    if (lives > 0) {
        lives--;
    }
}

void DrawPacman(int x, int y, int direction, int index) {
  Vector2 pc = getSpriteDirection(pacman, direction);
  DrawTexturePro(
    characters,
    (Rectangle) { pc.x + (index * UNIT_SPRITE_LENGTH), pc.y, UNIT_SPRITE_LENGTH, UNIT_SPRITE_LENGTH },
    (Rectangle) { x, y, GRID_LENGTH, GRID_LENGTH },
    Vector2Zero(), 0, WHITE
  );
}

