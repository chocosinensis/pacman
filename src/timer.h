double levelTimer;
double frightenedTimer;

void SetTimer(double *timer) {
  *timer = GetTime();
}

void InitTimers() {
  SetTimer(&levelTimer);
}

double GetCurrentTime(double start) {
  return GetTime() - start;
}
