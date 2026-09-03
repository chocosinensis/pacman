#define AUDIO_LENGTH 7

#define AUDIO_START 0
#define AUDIO_SIREN 1
#define AUDIO_EATDOT 2
#define AUDIO_FRIGHT 3
#define AUDIO_EYES 4
#define AUDIO_EATGHOST 5
#define AUDIO_DEATH 6

#define SPRITE_X 14
#define SPRITE_Y 13
#define UNIT_SPRITE_LENGTH 56

#define PELLET_COLOR 0xffb6adff

#define S_RIGHT 0
#define S_LEFT 1
#define S_UP 2
#define S_DOWN 3

Texture2D characters;
Texture2D emptyMaze;
Texture2D filledMaze;

Character pacman;
Character blinky;
Character pinky;
Character inky;
Character clyde;
Vector2 fruit;

const char *audio_names[] = { "start", "siren", "eatdot", "fright", "eyes", "eat_ghost", "eat_fruit", "death" };
Sound audios[AUDIO_LENGTH];

void InitTextures() {
  characters = LoadTexture("assets/sprites/characters.png");
  emptyMaze = LoadTexture("assets/sprites/maze.png");
  filledMaze = LoadTexture("assets/sprites/filled-maze.png");

  pacman = newCharacter(0, 0, 0, 1, 0, 2, 0, 3, 3);
  blinky = newCharacter(4, 0, 4, 2, 4, 4, 4, 6, 2);
  pinky = newCharacter(5, 0, 5, 2, 5, 4, 5, 6, 2);
  inky = newCharacter(6, 0, 6, 2, 6, 4, 6, 6, 2);
  clyde = newCharacter(7, 0, 7, 2, 7, 4, 7, 6, 2);
  fruit = makeSprite(3, 3);
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
void DrawBlorbs() {
  int r = GRID_LENGTH / 3;
  int offset = GRID_LENGTH / 2;
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (MAP[i][j] != BLORB) continue;

      DrawCircle(
        j * GRID_LENGTH + offset, i * GRID_LENGTH + offset,
        r, GetColor(PELLET_COLOR)
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

