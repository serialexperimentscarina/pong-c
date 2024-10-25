#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 70

int player1Y, player2Y;

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pong");
  SetTargetFPS(60);

  player1Y = player2Y = ((SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2));

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_UP) && player2Y > 0)
      player2Y -= 2;
    if (IsKeyDown(KEY_DOWN) && player2Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
      player2Y += 2;
    if (IsKeyDown(KEY_W) && player1Y > 0)
      player1Y -= 2;
    if (IsKeyDown(KEY_S) && player1Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
      player1Y += 2;

    DrawRectangle(20, player1Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    DrawRectangle(770, player2Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}