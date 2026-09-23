#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

#include "./defines/imports.h"

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

// game_state.h
void InitGameState();
void InitMaps();
void MiniReset();
void ResetGameState(Vector2 *pacmanPosition);
void NextLevel(Vector2 *pacmanPosition);
void AddScore(int points);
void LoseLife();

// assets.h
void InitTextures();
Sound InitAudio(int idx);
void InitAudios();
void DrawOrbs();
void DrawBlorbs(int blorbColor);
void UnloadTextures();
void UnloadAudios();

// gridwall.h
void InitMap(int MAP[GRID_HEIGHT][GRID_WIDTH]);
bool IsCollidable(float x, float y, int object, int MAP[GRID_HEIGHT][GRID_WIDTH]);
bool IsWall(float x, float y, int MAP[GRID_HEIGHT][GRID_WIDTH]);
bool WillHitWall(Vector2 pos, int MAP[GRID_HEIGHT][GRID_WIDTH]);
bool CanTurn(Vector2 pos, int dir, int MAP[GRID_HEIGHT][GRID_WIDTH]);
bool IsOrb(float x, float y);
bool IsBlorb(float x, float y);
bool IsEveryPelletEaten(int pelletCount);
void OpenGhostHouse(int MAP[GRID_HEIGHT][GRID_WIDTH]);
void CloseGhostHouse(int MAP[GRID_HEIGHT][GRID_WIDTH]);

// timer.h
void SetTimer(double *timer);
void InitTimers();
double GetCurrentTime(double start);

// util.h
void QueueDirection(int *queued);
void Play(int audioIndex);
void DrawCredits();
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
bool Snaps(Vector2 pos, int *snapCount);

// player.h
void DrawPacman(int x, int y, int direction, int index);
Vector2 MoveInDirection(Vector2 pos, int dir, float distance);
void EatPellet(float x, float y);
void CollideWithGhost(Ghost *ghost, Vector2 pacmanPosition);
void GetEaten();
void AnimateGameOver(Vector2 pacmanPosition);

// ghosts.h
Vector2 GetGhostSprite(Ghost gh);
void DrawGhost(Ghost gh, int index);
void InitGhosts();
Ghost *g(int idx);
double GetDistance(Vector2 tile1, Vector2 tile2);
Vector2 AddToTile(Vector2 tile, int direction, int step);
Vector2 GetSteppedTile(Vector2 pacmanTile, int step);
Vector2 GetTargetTile(Ghost ghost, Vector2 pacmanTile, Vector2 blinkyTile);
bool IsGhostInHouse(Vector2 tile);
bool SurroundedByWalls(Vector2 nextPositions[], int direction, int name);
bool HitTwoWalls(Vector2 nextPositions[], int direction, int name);
int DirectionWhenTwoWalls(Vector2 nextPositions[], int direction, int name);
bool IsGoodToTurn(Vector2 nextPositions[], int direction, int name, bool snap);
int Turn(Vector2 nextTiles[], Vector2 targetTile, int direction);
int GetNextDirection(Ghost ghost, Vector2 targetTile);
void GoToTile(Ghost *ghost, Vector2 tile, float delta);
void RotateGhost(Ghost *ghost, int prevState, int newState);
void ChangeState(Ghost *ghost, int state);
bool BlinkyWillChase();
int GetGhostState(Ghost gh, bool frightened);
void MakeFrightened();
void GhostToHome(Ghost *ghost, float delta);
