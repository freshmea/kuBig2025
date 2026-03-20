#include "../include/board.h"
#include "../include/bowling.h"
#include <raylib.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef enum
{
    SCREEN_NAME_INPUT,
    SCREEN_PLAYING,
    SCREEN_FINISHED,
} AppScreen;

static void handleNameInput(char *nameBuffer)
{
    int key = GetCharPressed();

    while (key > 0)
    {
        int length = (int)strlen(nameBuffer);
        if (key >= 32 && key <= 125 && length < MAX_NAME_LENGTH)
        {
            nameBuffer[length] = (char)key;
            nameBuffer[length + 1] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        int length = (int)strlen(nameBuffer);
        if (length > 0)
        {
            nameBuffer[length - 1] = '\0';
        }
    }
}

int main(void)
{
    AppScreen screen = SCREEN_NAME_INPUT;
    BowlingGame game;
    char nameBuffer[MAX_NAME_LENGTH + 1] = "";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "bowlingRay");
    initializeBoardResources();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        if (screen == SCREEN_NAME_INPUT)
        {
            handleNameInput(nameBuffer);

            if (((clicked && CheckCollisionPointRec(mouse, getStartButtonBounds())) || IsKeyPressed(KEY_ENTER)) &&
                nameBuffer[0] != '\0')
            {
                initGame(&game, nameBuffer);
                screen = SCREEN_PLAYING;
            }
        }
        else if (screen == SCREEN_PLAYING)
        {
            if (clicked)
            {
                int selectedPins = getPinButtonValue(&game, mouse);
                if (selectedPins >= 0)
                {
                    applyRoll(&game, selectedPins);
                    if (game.isFinished)
                    {
                        screen = SCREEN_FINISHED;
                    }
                }
            }
        }
        else if ((clicked && CheckCollisionPointRec(mouse, getRestartButtonBounds())) || IsKeyPressed(KEY_ENTER))
        {
            nameBuffer[0] = '\0';
            screen = SCREEN_NAME_INPUT;
        }

        BeginDrawing();
        if (screen == SCREEN_NAME_INPUT)
        {
            drawNameEntryScreen(nameBuffer);
        }
        else if (screen == SCREEN_PLAYING)
        {
            drawGameScreen(&game);
        }
        else
        {
            drawFinishScreen(&game);
        }
        EndDrawing();
    }

    unloadBoardResources();
    CloseWindow();
    return 0;
}