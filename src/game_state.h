bool gameStarted = false;
bool beginning = false;
bool gamePaused = true;

bool gameOver = true;

int direction = S_LEFT;
int queuedDirection = S_LEFT;

int currentScore = 0;
int highScore = 0;
int lives = MAX_LIVES;

int pelletsEaten = 0;
int ghostsEaten = 0;

void InitGameState() {
  currentScore = 0;
  direction = S_LEFT;
  queuedDirection = S_LEFT;
  bool isPath = true;
  lives = MAX_LIVES;
  pelletsEaten = 0;
  ghostsEaten = 0;
}

void AddScore(int points) {
  currentScore += points;
  if (currentScore > highScore)
    highScore = currentScore;
}

void LoseLife() {
  if (lives > 0)
    lives--;
}
