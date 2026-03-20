#ifndef BOWLING_RAY_BOWLING_H
#define BOWLING_RAY_BOWLING_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 9

typedef struct
{
    int score[12][4];
    int frameScore[11];
    char name[MAX_NAME_LENGTH + 1];
} Score;

typedef struct
{
    Score player;
    bool rollsPlayed[12][4];
    int currentFrame;
    int currentRoll;
    bool isFinished;
} BowlingGame;

void initScore(Score *player, const char iname[]);
void calScore(int *frameScore, const int (*score)[4]);
void initGame(BowlingGame *game, const char iname[]);
int getMaxPinsForRoll(const BowlingGame *game);
int getStandingPins(const BowlingGame *game);
void applyRoll(BowlingGame *game, int pins);
bool hasBonusRoll(const BowlingGame *game);

#endif