void CoreLogic() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexturePro(
      emptyMaze,
      (Rectangle) { 0, 0, emptyMaze.width, emptyMaze.height },
      (Rectangle) { 0, 0, WIDTH, HEIGHT },
      Vector2Zero(), 0, WHITE
    );

    // if (!gameStarted) DrawText("READY!", 190, 200, 20, YELLOW);
    if (!gameStarted && !beginning) {
      PlaySound(audios[AUDIO_BEGINNING]);
      beginning = true;
    }

    EndDrawing();
  }
}

void Game() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  InitAudioDevice();
  SetTargetFPS(60);

  InitTextures();
  InitAudios();

  CoreLogic();

  UnloadTextures();
  UnloadAudios();

  CloseAudioDevice();
  CloseWindow();
}

