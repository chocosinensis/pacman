#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "raymath.h"

// game.h
void CoreLogic();
void Game();

// assets.h
void InitTextures();
Sound InitAudio(int idx);
void InitAudios();
void UnloadTextures();
void UnloadAudios();

