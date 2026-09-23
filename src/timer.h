double levelTimer;
double frightenedTimer;
double gotEatenTimer;

void SetTimer(double *timer) {
  *timer = GetTime();
}

void InitTimers() {
  SetTimer(&levelTimer);
}

double GetCurrentTime(double start) {
  return GetTime() - start;
}
