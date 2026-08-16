#define AUDIO_LENGTH 7

#define AUDIO_BEGINNING 0
#define AUDIO_CHOMP 1
#define AUDIO_DEATH 2
#define AUDIO_EATFRUIT 3
#define AUDIO_EATGHOST 4
#define AUDIO_EXTRAPAC 5
#define AUDIO_INTERMISSION 6

#define SPRITE_X 14
#define SPRITE_Y 13
#define UNIT_SPRITE_LENGTH 56

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

const char *audio_names[] = { "beginning", "chomp", "death", "eatfruit", "eatghost", "extrapac", "intermission" };
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
  sprintf(path, "assets/audio/pacman_%s.wav", audio_names[idx]);
  return LoadSound(path);
}
void InitAudios() {
  for (int i = 0; i < LENGTH(audios); i++)
    audios[i] = InitAudio(i);
}

void UnloadTextures() {
  UnloadTexture(characters);
  UnloadTexture(emptyMaze);
  UnloadTexture(filledMaze);
}
void UnloadAudios() {
  for (int i = 0; i < LENGTH(audios); i++) UnloadSound(audios[i]);
}

