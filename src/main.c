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
int player1Score, player2Score;
int ballX, ballY;
int ballSpeedX, ballSpeedY;

void initialize()
{
  // Initialize window
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pong");
  // Set icon
  Image icon = LoadImage("../assets/icon.png");
  SetWindowIcon(icon);
  UnloadImage(icon);
  // Set Target FPS
  SetTargetFPS(60);

  player1Y = player2Y = ((SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
  player1Score = player2Score = 0;
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;
  ballSpeedX = ballSpeedY = BALL_SPEED;
}

void draw()
{
  BeginDrawing();
  ClearBackground(BLACK);

  // Line dividing the field
  for (int i = 0; i <= 400; i += 100)
  {
    DrawRectangle((SCREEN_WIDTH / 2), i, (PADDLE_WIDTH / 2), 50, WHITE);
  }

  // Player 1 paddle
  DrawRectangle(20, player1Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
  // Player 2 paddle
  DrawRectangle(SCREEN_WIDTH - 30, player2Y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
  // Ball
  DrawRectangle(ballX, ballY, BALL_WIDTH, BALL_HEIGHT, WHITE);

  // Score
  DrawText(TextFormat("%d", player1Score), 200, 80, 50, WHITE);
  DrawText(TextFormat("%d", player2Score), 600, 80, 50, WHITE);

  EndDrawing();
}

void updatePaddleMovement()
{
  // Player 1 movement
  if (IsKeyDown(KEY_W) && player1Y > 0)
    player1Y -= PADDLE_SPEED;
  if (IsKeyDown(KEY_S) && player1Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
    player1Y += PADDLE_SPEED;

  // Player 2 movement
  if (IsKeyDown(KEY_UP) && player2Y > 0)
    player2Y -= PADDLE_SPEED;
  if (IsKeyDown(KEY_DOWN) && player2Y < (SCREEN_HEIGHT - PADDLE_HEIGHT))
    player2Y += PADDLE_SPEED;
}

void updateBallMovement()
{
  // Check for collision with upper and bottom borders
  if (ballY < 0 || ballY > (SCREEN_HEIGHT - 10))
    ballSpeedY *= -1;

  // Check if ball has reached left border (teleport ball back to center and increase score of last player to hit ball)
  if (ballX < 10 || ballX > (SCREEN_WIDTH - 10))
  {
    ballX < 10 ? player2Score++ : player1Score++;

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
    ballX = 20 + PADDLE_WIDTH;
  }
  // Check for collision with player 2
  if (ballX > (SCREEN_WIDTH - 30 - PADDLE_WIDTH) && (ballY > player2Y && ballY < (player2Y + PADDLE_HEIGHT)))
  {
    ballSpeedX *= -1;
    ballSpeedY *= -1;
    ballX = SCREEN_WIDTH - 30 - PADDLE_WIDTH;
  }

  ballX += ballSpeedX;
  ballY += ballSpeedY;
}

int main(void)
{
  initialize();

  while (!WindowShouldClose())
  {
    updatePaddleMovement();
    updateBallMovement();
    draw();
  }

  CloseWindow();
  return 0;
}