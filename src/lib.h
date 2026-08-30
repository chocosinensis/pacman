#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "raymath.h"

typedef struct Character {
  Vector2 right;
  Vector2 left;
  Vector2 up;
  Vector2 down;
  int sprites;
} Character;

// game.h
void CoreLogic();
void Game();

// assets.h
void InitTextures();
Sound InitAudio(int idx);
void InitAudios();
void UnloadTextures();
void UnloadAudios();

// gridwall.h
bool IsWall(float x, float y);

// util.h
int setDirection(int *p_direction);
Vector2 makeSprite(int x, int y);
Vector2 getSpriteDirection(Character ch, int direction);
Character newCharacter(
  int right_x, int right_y,
  int left_x, int left_y,
  int up_x, int up_y,
  int down_x, int down_y,
  int sprites
);

// game_state.h
void DrawPacman(int x, int y, int direction, int index);

