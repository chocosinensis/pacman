#define AUDIO_LENGTH 7

#define AUDIO_BEGINNING 0
#define AUDIO_CHOMP 1
#define AUDIO_DEATH 2
#define AUDIO_EATFRUIT 3
#define AUDIO_EATGHOST 4
#define AUDIO_EXTRAPAC 5
#define AUDIO_INTERMISSION 6

// TODO: Divide spritesheet into segments
// AND the maze into regions

Texture2D characters;
Texture2D emptyMaze;
Texture2D filledMaze;

const char *audio_names[] = { "beginning", "chomp", "death", "eatfruit", "eatghost", "extrapac", "intermission" };
Sound audios[AUDIO_LENGTH];

void InitTextures() {
  characters = LoadTexture("assets/sprites/characters.png");
  emptyMaze = LoadTexture("assets/sprites/maze.png");
  filledMaze = LoadTexture("assets/sprites/filled-maze.png");
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

