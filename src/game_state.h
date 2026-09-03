bool gameStarted = false;
bool beginning = false;
bool gamePaused = true;

int direction = S_LEFT;
int prevDirection;
bool changeDirection = false;
bool isPath = true;

int currentScore = 0;
int highScore = 0;
int lives = MAX_LIVES;

void InitGameState() {
  currentScore = 0;
  prevDirection = direction;
  lives = MAX_LIVES;
}

void AddScore(int points) {
  currentScore += points;
  if (currentScore > highScore) {
    highScore = currentScore;
  }
}

void LoseLife() {
  if (lives > 0) {
    lives--;
  }
}

