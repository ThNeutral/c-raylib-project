#include <string.h>
#include "raylib.h"
#include "consts.h"
#include "resource_dir.h"
#include "pong.hpp"

int main (int argc, char** argv)
{
	void (*Runner)(void);

	if (argc != 2) {
		printf("Expected 2 arguments\n");
		return 1;
	} else if (strcmp(argv[1], "pong") == 0) {
		Runner = RunPong;
	} else {
		printf("Invalid game name");
		return 1;
	}

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(GAME_WIDTH, GAME_HEIGHT, "C-Game");
	
	SearchAndSetResourceDir("resources");

	Runner();

	CloseWindow();
	return 0;
}