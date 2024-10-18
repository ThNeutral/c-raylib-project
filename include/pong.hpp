#ifndef PONG_H
#define PONG_H

#include "raylib.h"
#include "resource_dir.h"
#include "pong_objects.hpp"
#include "consts.h"

#define SPEED_SCALE_FACTOR 1.075
#define STARTING_SPEED Vector2{500, 100}

enum GAME_STATES {
    RUNNING,
    ENDED
};

void RunPong() {
    DisableCursor();

    float deltaTime;
	Vector2 mousePosition;
    int score = 0;
    GAME_STATES gameState = RUNNING;

	Circle* ball = new Circle(Vector2{100, 20}, STARTING_SPEED, 10.0,  BLUE);
    Circle* ballCopy; 
    Rect* walls[3] = {
        // Top
        new Rect(Vector2{0, 0}, Vector2{GAME_WIDTH, 10}, Vector2{0, 0}, GRAY),
        // Right
        new Rect(Vector2{GAME_WIDTH - 10, 0}, Vector2{10, GAME_HEIGHT}, Vector2{0, 0}, GRAY),
        // Bottom
        new Rect(Vector2{0, GAME_HEIGHT - 10}, Vector2{GAME_WIDTH, 10}, Vector2{0, 0}, GRAY),
    };
    Rect* collider = new Rect(Vector2{0, 0}, Vector2{10, GAME_HEIGHT}, Vector2{0, 0}, RED); 
	Player* player = new Player(Vector2{100, 100}, Vector2{25, 100}, BLUE);

	while (!WindowShouldClose())
	{
        // Exit --------------------------------------------------------------------------
        if (IsMouseButtonPressed(KEY_ESCAPE)) break;

        // Game end ----------------------------------------------------------------------
        if (gameState == ENDED) {
            BeginDrawing();
            DrawText(TextFormat("Game has ended!\nYour score: %i\nTo restart game press \"R\"\nTo leave press \"Esc\"", score), GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2 - 70, 32, WHITE);
            EndDrawing();
            if (IsMouseButtonPressed(KEY_R)) {
                gameState = RUNNING;
                score = 0;
                ball->SetSpeed(STARTING_SPEED);
            }
            continue;
        }

		// Update ------------------------------------------------------------------------
		deltaTime = GetFrameTime();
		mousePosition = GetMousePosition();

        ballCopy = ball->Copy();
        ballCopy->MoveSelf(deltaTime);
        for (int i = 0; i < 5; i++) {
		    Rect* rect = i == 3 ? player : i == 4 ? collider : walls[i];
            if (CheckCollisionCircleRec(ballCopy->GetPosition(), ballCopy->GetRadius(), rect->ToRect())) {
                if (i == 4) {
                    gameState = ENDED;
                    continue;
                }
                if (i == 3) {
                    score += 1;
                } 
                ball->ReverseSpeed(i % 2 == 1 ? true : false, i % 2 != 1 ? true : false);
                ball->ScaleSpeed(SPEED_SCALE_FACTOR);
            }
        }
        delete ballCopy;
		ball->MoveSelf(deltaTime);
		player->MoveSelf(mousePosition);

		// Draw --------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(BLACK);

        for (Rect* wall : walls) {
		    wall->DrawSelf();
        }
        collider->DrawSelf();
		ball->DrawSelf();
        player->DrawSelf();

		EndDrawing();
	}

    for (Rect* wall : walls) {
	    delete wall;
    }
    delete collider;
	delete ball;
}

#endif