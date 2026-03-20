#include "../include/bowling.h"
#include <stdio.h>
#include <string.h>

static bool isSpare(const Score *player, int frame)
{
    return player->score[frame][1] != 10 &&
           (player->score[frame][1] + player->score[frame][2] == 10);
}

static int strikeBonus(const int (*score)[4], int frame)
{
    if (frame == 9)
    {
        return score[10][1] + score[10][2];
    }

    if (score[frame + 1][1] == 10)
    {
        return 10 + score[frame + 2][1];
    }

    return score[frame + 1][1] + score[frame + 1][2];
}

void initScore(Score *player, const char iname[])
{
    memset(player, 0, sizeof(*player));
    snprintf(player->name, sizeof(player->name), "%s", iname);
}

void calScore(int *frameScore, const int (*score)[4])
{
    int total = 0;

    for (int frame = 0; frame <= 10; ++frame)
    {
        frameScore[frame] = 0;
    }

    for (int frame = 1; frame <= 9; ++frame)
    {
        if (score[frame][1] == 10)
        {
            total += 10 + strikeBonus(score, frame);
        }
        else if (score[frame][1] + score[frame][2] == 10)
        {
            total += 10 + score[frame + 1][1];
        }
        else
        {
            total += score[frame][1] + score[frame][2];
        }

        frameScore[frame] = total;
    }

    total += score[10][1] + score[10][2] + score[10][3];
    frameScore[10] = total;
}

void initGame(BowlingGame *game, const char iname[])
{
    memset(game, 0, sizeof(*game));
    initScore(&game->player, iname);
    game->currentFrame = 1;
    game->currentRoll = 1;
}

bool hasBonusRoll(const BowlingGame *game)
{
    return game->player.score[10][1] == 10 || isSpare(&game->player, 10);
}

int getMaxPinsForRoll(const BowlingGame *game)
{
    int frame = game->currentFrame;
    int roll = game->currentRoll;
    const Score *player = &game->player;

    if (frame < 10)
    {
        if (roll == 1)
        {
            return 10;
        }

        return 10 - player->score[frame][1];
    }

    if (roll == 1)
    {
        return 10;
    }

    if (roll == 2)
    {
        if (player->score[10][1] == 10)
        {
            return 10;
        }

        return 10 - player->score[10][1];
    }

    if (player->score[10][1] == 10)
    {
        if (player->score[10][2] == 10)
        {
            return 10;
        }

        return 10 - player->score[10][2];
    }

    if (isSpare(player, 10))
    {
        return 10;
    }

    return 0;
}

int getStandingPins(const BowlingGame *game)
{
    return getMaxPinsForRoll(game);
}

void applyRoll(BowlingGame *game, int pins)
{
    if (game->isFinished)
    {
        return;
    }

    if (pins < 0 || pins > getMaxPinsForRoll(game))
    {
        return;
    }

    game->player.score[game->currentFrame][game->currentRoll] = pins;
    game->rollsPlayed[game->currentFrame][game->currentRoll] = true;
    calScore(game->player.frameScore, game->player.score);

    if (game->currentFrame < 10)
    {
        if (game->currentRoll == 1 && pins == 10)
        {
            game->currentFrame += 1;
            return;
        }

        if (game->currentRoll == 1)
        {
            game->currentRoll = 2;
            return;
        }

        game->currentFrame += 1;
        game->currentRoll = 1;
        return;
    }

    if (game->currentRoll == 1)
    {
        game->currentRoll = 2;
        return;
    }

    if (game->currentRoll == 2)
    {
        if (hasBonusRoll(game))
        {
            game->currentRoll = 3;
        }
        else
        {
            game->isFinished = true;
        }

        return;
    }

    game->isFinished = true;
}