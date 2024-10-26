#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 70
#define PADDLE_SPEED 3
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_SPEED 5

int player1Y, player2Y;
int ballX, ballY;
int ballSpeedX, ballSpeedY;

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pong");
  SetTargetFPS(60);

  player1Y = player2Y = ((SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;
  ballSpeedX = ballSpeedY = BALL_SPEED;

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_UP) && player2Y > 0)
      player2Y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_DOWN) && player2Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
      player2Y += PADDLE_SPEED;
    if (IsKeyDown(KEY_W) && player1Y > 0)
      player1Y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_S) && player1Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
      player1Y += PADDLE_SPEED;

    DrawRectangle(20, player1Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    DrawRectangle(SCREEN_WIDTH - 30, player2Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

    DrawRectangle(ballX, ballY, BALL_WIDTH, BALL_HEIGHT, WHITE);

    // Check for collision with upper and bottom borders
    if (ballY < 0 || ballY > (SCREEN_HEIGHT - 10))
      ballSpeedY *= -1;

    // Check if ball has reached left/right borders (teleport ball back to center)
    if (ballX < 0 || ballX > (SCREEN_WIDTH - 10))
    {
      ballX = SCREEN_WIDTH / 2;
      ballY = SCREEN_HEIGHT / 2;
      ballSpeedX *= -1;
      ballSpeedY *= -1;
    }

    // Check for collision with player 1
    if (ballX < (20 + PADDLE_WIDTH) && (ballY > player1Y && ballY < (player1Y + PADDLE_HEIGHT)))
    {
      ballSpeedX *= -1;
      ballSpeedY *= -1;
    }
    // Check for collision with player 2
    if (ballX > (SCREEN_WIDTH - 30 - PADDLE_WIDTH) && (ballY > player2Y && ballY < (player2Y + PADDLE_HEIGHT)))
    {
      ballSpeedX *= -1;
      ballSpeedY *= -1;
    }

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    EndDrawing();
  }

  CloseWindow();
  return 0;
}