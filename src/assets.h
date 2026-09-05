Texture2D characters;
Texture2D emptyMaze;
Texture2D filledMaze;

Character pacman;
Character ghosts[GHOSTS];
Vector2 fruit;

Ghost blinky;
Ghost pinky;
Ghost inky;
Ghost clyde;

const char *audio_names[] = { "start", "siren", "eatdot", "fright", "eyes", "eat_ghost", "eat_fruit", "death" };
Sound audios[AUDIO_LENGTH];

void InitTextures() {
  characters = LoadTexture("assets/sprites/characters.png");
  emptyMaze = LoadTexture("assets/sprites/maze.png");
  filledMaze = LoadTexture("assets/sprites/filled-maze.png");

  pacman = InitCharacter(0, 0, 0, 1, 0, 2, 0, 3, 3, PACMAN);

  ghosts[BLINKY] = InitCharacter(0, 4, 2, 4, 4, 4, 6, 4, 2, BLINKY);
  ghosts[PINKY]  = InitCharacter(0, 5, 2, 5, 4, 5, 6, 5, 2, PINKY);
  ghosts[INKY]   = InitCharacter(0, 6, 2, 6, 4, 6, 6, 6, 2, INKY);
  ghosts[CLYDE]  = InitCharacter(0, 7, 2, 7, 4, 7, 6, 7, 2, CLYDE);

  fruit = MakeSprite(3, 3);
}
Sound InitAudio(int idx) {
  char path[50];
  sprintf(path, "assets/audio/%02d_%s.wav", idx, audio_names[idx]);
  return LoadSound(path);
}
void InitAudios() {
  for (int i = 0; i < LENGTH(audios); i++)
    audios[i] = InitAudio(i);
}

void DrawOrbs() {
  int l = GRID_LENGTH / 5;
  int offset = (GRID_LENGTH - l) / 2;
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (MAP[i][j] != ORB) continue;

      DrawRectangle(
        j * GRID_LENGTH + offset, i * GRID_LENGTH + offset,
        l, l, GetColor(PELLET_COLOR)
      );
    }
  }
}
void DrawBlorbs(int blorbColor) {
  int r = GRID_LENGTH / 3;
  int offset = GRID_LENGTH / 2;
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (MAP[i][j] != BLORB) continue;

      DrawCircle(
        j * GRID_LENGTH + offset, i * GRID_LENGTH + offset,
        r, GetColor(blorbColor)
      );
    }
  }
}

void UnloadTextures() {
  UnloadTexture(characters);
  UnloadTexture(emptyMaze);
  UnloadTexture(filledMaze);
}
void UnloadAudios() {
  for (int i = 0; i < LENGTH(audios); i++) UnloadSound(audios[i]);
}

