#include "raylib.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pong Game - Raylib Example");
    SetTargetFPS(60);

    // Pelota
    Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 10;

    // Límites de velocidad
    const float MAX_SPEED = 8.0f;

    // Paletas
    const int paddleWidth = 10;
    const int paddleHeight = 80;
    Rectangle player1 = { 50, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };
    Rectangle player2 = { screenWidth - 60, screenHeight / 2 - paddleHeight / 2, paddleWidth, paddleHeight };

    const float paddleSpeed = 6.0f;

    // Puntuación
    int score1 = 0;
    int score2 = 0;

    // Main game loop
    while (!WindowShouldClose())
    {
        // --- UPDATE ---

        // Movimiento de los jugadores
        if (IsKeyDown(KEY_W)) player1.y -= paddleSpeed;
        if (IsKeyDown(KEY_S)) player1.y += paddleSpeed;
        if (IsKeyDown(KEY_UP)) player2.y -= paddleSpeed;
        if (IsKeyDown(KEY_DOWN)) player2.y += paddleSpeed;

        // Limitar movimiento de las paletas
        if (player1.y < 0) player1.y = 0;
        if (player1.y + paddleHeight > screenHeight) player1.y = screenHeight - paddleHeight;
        if (player2.y < 0) player2.y = 0;
        if (player2.y + paddleHeight > screenHeight) player2.y = screenHeight - paddleHeight;

        // Mover pelota
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Rebote con techo y suelo
        if ((ballPosition.y <= ballRadius) || (ballPosition.y >= screenHeight - ballRadius))
            ballSpeed.y *= -1;

        // Rebote con paletas
        if (CheckCollisionCircleRec(ballPosition, ballRadius, player1))
        {
            ballSpeed.x *= -1;
            ballSpeed.x += 0.2f; // aumentar un poco la velocidad
        }

        if (CheckCollisionCircleRec(ballPosition, ballRadius, player2))
        {
            ballSpeed.x *= -1;
            ballSpeed.x -= 0.2f;
        }

        // Limitar velocidad máxima
        if (ballSpeed.x > MAX_SPEED) ballSpeed.x = MAX_SPEED;
        if (ballSpeed.x < -MAX_SPEED) ballSpeed.x = -MAX_SPEED;
        if (ballSpeed.y > MAX_SPEED) ballSpeed.y = MAX_SPEED;
        if (ballSpeed.y < -MAX_SPEED) ballSpeed.y = -MAX_SPEED;

        // Anotar punto si la pelota sale de los límites
        if (ballPosition.x < 0)
        {
            score2++;
            ballPosition = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = (Vector2){ 5.0f, 4.0f };
        }
        else if (ballPosition.x > screenWidth)
        {
            score1++;
            ballPosition = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
            ballSpeed = (Vector2){ -5.0f, 4.0f };
        }

        // --- DRAW ---
        BeginDrawing();
            ClearBackground(BLACK);

            // Pelota
            DrawCircleV(ballPosition, ballRadius, RAYWHITE);

            // Paletas
            DrawRectangleRec(player1, RAYWHITE);
            DrawRectangleRec(player2, RAYWHITE);

            // Línea central
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, GRAY);

            // Marcador
            DrawText(TextFormat("%d", score1), screenWidth / 2 - 50, 20, 40, LIGHTGRAY);
            DrawText(TextFormat("%d", score2), screenWidth / 2 + 30, 20, 40, LIGHTGRAY);

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
