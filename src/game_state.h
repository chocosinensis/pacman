bool playButtonPressed = false;

bool gameStarted = false;
bool beginning = false;
bool gamePaused = true;

bool gotEatenStart = false;
bool gotEatenEnd = true;
bool gameOver = false;

bool soundMuted = false;
bool sfxMuted = false;

bool nameEntered = false;
bool savedGame = false;

int currentScreen = MENU;

bool menuPlayedOnce = false;
bool menuOpen = false;
bool movementInMenu = false;

int direction = S_LEFT;
int queuedDirection = S_LEFT;

char playerName[MAX_NAME + 1] = "";
int nameLength = 0;
Player player = { 0 };

int currentScore = 0;
int highScore = 0;
int lives = MAX_LIVES;
int level = 0;

int pelletsEaten = 0;
int ghostsEaten = 0;
bool fruitExists = false;

int MAP[GRID_HEIGHT][GRID_WIDTH];
int MAPS[GHOSTS][GRID_HEIGHT][GRID_WIDTH];

void InitGameState() {
  playButtonPressed = false;
  gameOver = false;
  currentScore = 0;
  direction = S_LEFT;
  queuedDirection = S_LEFT;
  level = 1;
  lives = MAX_LIVES;
  pelletsEaten = 0;
  ghostsEaten = 0;
  fruitExists = false;
  InitMaps();
}

void InitMaps() {
  InitMap(MAP);
  for (int i = 0; i < GHOSTS; i++) InitMap(MAPS[i]);
}

void MiniReset() {
  gameStarted = false;
  beginning = false;
  gamePaused = true;
  direction = S_LEFT;
  queuedDirection = S_LEFT;
  fruitExists = false;
}

void ResetGameState(Vector2 *pacmanPosition) {
  MiniReset();
  pelletsEaten = 0;
  ghostsEaten = 0;
  *pacmanPosition = PACMAN_STARTING_POSITION;
  InitGhosts();
  InitMaps();
}

void NextLevel(Vector2 *pacmanPosition) {
  level++;
  if (level > MAX_LEVEL) level = 1;
  ResetGameState(pacmanPosition);
  UpdatePlayerDetails();
  if (!IsNameInList(playerName)) return;
  player.lastLevelScore = currentScore;
  player.elapsedTime = GetGameElapsed();
}

void AddScore(int points) {
  currentScore += points;
  if (currentScore > highScore)
    highScore = currentScore;
}

void AddLife() {
  if (lives < MAX_LIVES)
    lives++;
}

void LoseLife() {
  if (lives > 0)
    lives--;
}

void QuitFromGame() {
  playButtonPressed = false;

  gameStarted = false;
  beginning = false;
  gamePaused = true;

  gotEatenStart = false;
  gotEatenEnd = true;

  direction = S_LEFT;
  queuedDirection = S_LEFT;

  if (!gameOver) savedGame = true;

  StopAllAudios();
  menuPlayedOnce = false;

  PauseGameTimer();
  if (currentScreen == NAME_ENTRY) ResetCache();
  currentScreen = MENU;
  UpdatePlayerDetails();
}
