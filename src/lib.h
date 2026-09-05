#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

typedef struct Character {
  Vector2 right;
  Vector2 left;
  Vector2 up;
  Vector2 down;
  int sprites;
  int name;
} Character;

typedef struct Ghost {
  int name;
  int state;
  Vector2 position;
  int direction;
} Ghost;

// game.h
void CoreLogic();
void Game();

// assets.h
void InitTextures();
Sound InitAudio(int idx);
void InitAudios();
void DrawOrbs();
void DrawBlorbs(int blorbColor);
void UnloadTextures();
void UnloadAudios();

// gridwall.h
bool IsCollidable(float x, float y, int object);
bool IsWall(float x, float y);
bool WillHitWall(Vector2 pos);
bool CanTurn(Vector2 pos, int dir);
bool IsOrb(float x, float y);
bool IsBlorb(float x, float y);

// util.h
void QueueDirection(int *queued);
void Play(int audioIndex);
Vector2 MakeSprite(int x, int y);
Vector2 GetSpriteDirection(Character ch, int direction);
Character InitCharacter(
  int right_x, int right_y,
  int left_x, int left_y,
  int up_x, int up_y,
  int down_x, int down_y,
  int sprites, int name
);
Vector2 Tileify(Vector2 pos);
Vector2 GetTilePosition(Vector2 tile);
Vector2 GetCoordinates(Vector2 pos);

// game_state.h
void InitGameState();
void AddScore(int points);
void LoseLife();

// player.h
void DrawPacman(int x, int y, int direction, int index);
Vector2 MoveInDirection(Vector2 pos, int dir, float distance);
void EatPellet(float x, float y);

// ghosts.h
void DrawGhost(int x, int y, int direction, int name, int index);
void InitGhosts(Vector2 ghostPositions[]);
Ghost *g(int idx);
double GetDistance(Vector2 tile1, Vector2 tile2);
Vector2 GetSteppedTile(Vector2 pacmanTile, int step);
Vector2 GetTargetTile(Ghost ghost, Vector2 pacmanTile);
int GetNextDirection(Ghost ghost, Vector2 targetTile);
void GoToTile(Ghost ghost, Vector2 tile);

