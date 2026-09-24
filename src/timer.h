double levelTimer;
double frightenedTimer;
double gotEatenTimer;

double gameElapsed = 0;
double gameNewStart = 0;
bool gameTimerRun = false;

void SetTimer(double *timer) {
  *timer = GetTime();
}

void InitTimers() {
  SetTimer(&levelTimer);
}

void StartGameTimer() {
  gameElapsed = 0;
  gameNewStart = GetTime();
  gameTimerRun = true;
}

void ResumeGameTimer() {
  gameNewStart = GetTime();
  gameTimerRun = true;
}

void PauseGameTimer() {
  if (gameTimerRun) {
    gameElapsed += GetCurrentTime(gameNewStart);
    gameTimerRun = false;
  }
}

void ResetGameTimer() {
  gameElapsed = 0;
  gameTimerRun = false;
}

double GetGameElapsed() {
  if (gameTimerRun) return gameElapsed + GetCurrentTime(gameNewStart);
  return gameElapsed;
}

double GetCurrentTime(double start) {
  return GetTime() - start;
}

char *TimeFormat(double second) {
  static char time[16];
  if (second < 0) second = 0;
  int minute = (int) second / 60;
  int secs = (int) second % 60;
  sprintf(time, "%02d:%02d", minute, secs);
  return time;
}
