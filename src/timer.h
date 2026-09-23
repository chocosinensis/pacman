double levelTime;

void InitTimers() {
  levelTime = GetTime();
  printf("Timers initialized, levelTime = %.2lf\n", levelTime);
}

void ResetTimers() {
  levelTime = GetTime();
}

double GetCurrentTime(double start) {
  return GetTime() - start;
}
