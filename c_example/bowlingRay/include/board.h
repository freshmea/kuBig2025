#ifndef BOWLING_RAY_BOARD_H
#define BOWLING_RAY_BOARD_H

#include "bowling.h"
#include <raylib.h>

bool initializeBoardResources(void);
void unloadBoardResources(void);
void drawNameEntryScreen(const char *nameBuffer);
void drawGameScreen(const BowlingGame *game);
void drawFinishScreen(const BowlingGame *game);
Rectangle getStartButtonBounds(void);
Rectangle getRestartButtonBounds(void);
int getPinButtonValue(const BowlingGame *game, Vector2 point);

#endif