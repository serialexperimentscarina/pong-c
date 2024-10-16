#include "raylib.h"

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "pong");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("placeholder", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}