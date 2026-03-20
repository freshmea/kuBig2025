#include "../include/board.h"
#include <stdio.h>

#define UI_FONT_SIZE 64
#define UI_CODEPOINT_CAPACITY 512

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 78
#define BUTTON_HEIGHT 48
#define BUTTON_GAP 12
#define BUTTON_COLUMNS 6

static const Color BACKGROUND_COLOR = {246, 239, 228, 255};
static const Color PANEL_COLOR = {255, 250, 242, 255};
static const Color PANEL_BORDER = {107, 76, 48, 255};
static const Color ACCENT_COLOR = {201, 102, 41, 255};
static const Color ACCENT_DARK = {131, 58, 21, 255};
static const Color LANE_COLOR = {214, 184, 132, 255};
static const Color WOOD_STRIPE = {193, 154, 105, 255};
static const Color TEXT_COLOR = {47, 34, 23, 255};
static const Color MUTED_TEXT = {117, 94, 72, 255};

static Font gUiFont;
static bool gUiFontLoaded = false;

static int appendUniqueCodepoint(int *buffer, int count, int capacity, int codepoint)
{
    for (int index = 0; index < count; ++index)
    {
        if (buffer[index] == codepoint)
        {
            return count;
        }
    }

    if (count < capacity)
    {
        buffer[count] = codepoint;
        return count + 1;
    }

    return count;
}

static int buildUiCodepoints(int *buffer, int capacity)
{
    static const char *uiTexts[] = {
        "원본 bowling 예제의 점수 규칙을 raylib 화면으로 옮긴 버전",
        "플레이어 이름",
        "이름을 입력하세요",
        "게임 시작",
        "Enter로 시작, Backspace로 수정",
        "%d 프레임 %d 투구: 쓰러뜨린 핀 수를 선택하세요.",
        "게임 종료",
        "최종 점수 %d",
        "다시 시작해서 새 게임을 플레이할 수 있습니다.",
        "다시 시작",
    };
    int count = 0;

    for (int codepoint = 32; codepoint <= 126; ++codepoint)
    {
        count = appendUniqueCodepoint(buffer, count, capacity, codepoint);
    }

    for (int textIndex = 0; textIndex < (int)(sizeof(uiTexts) / sizeof(uiTexts[0])); ++textIndex)
    {
        int codepointCount = 0;
        int *codepoints = LoadCodepoints(uiTexts[textIndex], &codepointCount);

        for (int codepointIndex = 0; codepointIndex < codepointCount; ++codepointIndex)
        {
            count = appendUniqueCodepoint(buffer, count, capacity, codepoints[codepointIndex]);
        }

        UnloadCodepoints(codepoints);
    }

    return count;
}

static Font getUiFont(void)
{
    return gUiFontLoaded ? gUiFont : GetFontDefault();
}

static float getUiSpacing(float fontSize)
{
    return fontSize * 0.05f;
}

static Vector2 measureUiText(const char *text, float fontSize)
{
    return MeasureTextEx(getUiFont(), text, fontSize, getUiSpacing(fontSize));
}

static void drawUiText(const char *text, float posX, float posY, float fontSize, Color color)
{
    DrawTextEx(getUiFont(), text, (Vector2){posX, posY}, fontSize, getUiSpacing(fontSize), color);
}

bool initializeBoardResources(void)
{
    static const char *fontPaths[] = {
        "/usr/share/fonts/truetype/nanum/NanumGothic.ttf",
        "/usr/share/fonts/truetype/nanum/NanumBarunGothic.ttf",
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc",
    };
    int codepoints[UI_CODEPOINT_CAPACITY];
    int codepointCount = buildUiCodepoints(codepoints, UI_CODEPOINT_CAPACITY);

    if (gUiFontLoaded)
    {
        return true;
    }

    for (int index = 0; index < (int)(sizeof(fontPaths) / sizeof(fontPaths[0])); ++index)
    {
        if (!FileExists(fontPaths[index]))
        {
            continue;
        }

        gUiFont = LoadFontEx(fontPaths[index], UI_FONT_SIZE, codepoints, codepointCount);
        if (gUiFont.texture.id != 0)
        {
            SetTextureFilter(gUiFont.texture, TEXTURE_FILTER_BILINEAR);
            gUiFontLoaded = true;
            return true;
        }
    }

    return false;
}

void unloadBoardResources(void)
{
    if (gUiFontLoaded)
    {
        UnloadFont(gUiFont);
        gUiFontLoaded = false;
    }
}

static void drawCenteredText(const char *text, Rectangle bounds, int fontSize, Color color)
{
    Vector2 size = measureUiText(text, (float)fontSize);
    int posX = (int)(bounds.x + (bounds.width - size.x) / 2.0f);
    int posY = (int)(bounds.y + (bounds.height - size.y) / 2.0f);
    drawUiText(text, (float)posX, (float)posY, (float)fontSize, color);
}

static bool isRollVisible(const BowlingGame *game, int frame, int roll)
{
    if (game->rollsPlayed[frame][roll])
    {
        return true;
    }

    if (game->isFinished)
    {
        return false;
    }

    if (frame < game->currentFrame)
    {
        return true;
    }

    if (frame == game->currentFrame && roll < game->currentRoll)
    {
        return true;
    }

    return false;
}

static void getRollMark(const BowlingGame *game, int frame, int roll, char *buffer, int bufferSize)
{
    const Score *player = &game->player;
    int value = player->score[frame][roll];

    if (!isRollVisible(game, frame, roll))
    {
        if (bufferSize > 0)
        {
            buffer[0] = '\0';
        }
        return;
    }

    if (frame < 10)
    {
        if (roll == 1 && value == 10)
        {
            snprintf(buffer, bufferSize, "X");
            return;
        }

        if (roll == 2 && player->score[frame][1] != 10 &&
            player->score[frame][1] + value == 10)
        {
            snprintf(buffer, bufferSize, "/");
            return;
        }
    }
    else
    {
        if (value == 10)
        {
            snprintf(buffer, bufferSize, "X");
            return;
        }

        if (roll == 2 && player->score[10][1] != 10 && player->score[10][1] + value == 10)
        {
            snprintf(buffer, bufferSize, "/");
            return;
        }

        if (roll == 3)
        {
            if (player->score[10][1] == 10 && player->score[10][2] != 10 &&
                player->score[10][2] + value == 10)
            {
                snprintf(buffer, bufferSize, "/");
                return;
            }

            if (player->score[10][1] != 10 && player->score[10][1] + player->score[10][2] == 10)
            {
                if (value == 10)
                {
                    snprintf(buffer, bufferSize, "X");
                }
                else
                {
                    snprintf(buffer, bufferSize, "%d", value);
                }
                return;
            }
        }
    }

    if (value == 0)
    {
        snprintf(buffer, bufferSize, "-");
    }
    else
    {
        snprintf(buffer, bufferSize, "%d", value);
    }
}

static void drawScoreBoard(const BowlingGame *game)
{
    Rectangle panel = {40, 24, 1200, 225};
    DrawRectangleRounded(panel, 0.03f, 8, PANEL_COLOR);
    DrawRectangleRoundedLinesEx(panel, 0.03f, 8, 3, PANEL_BORDER);

    drawUiText(game->player.name, 70, 48, 30, TEXT_COLOR);

    char summary[128];
    snprintf(summary, sizeof(summary), "Frame %d  Roll %d  Total %d",
             game->currentFrame,
             game->currentRoll,
             game->player.frameScore[game->currentFrame > 10 ? 10 : game->currentFrame]);
    drawUiText(summary, 70, 88, 22, MUTED_TEXT);

    float startX = 60.0f;
    float topY = 132.0f;
    float frameHeight = 88.0f;
    float normalFrameWidth = 105.0f;
    float tenthFrameWidth = 165.0f;

    for (int frame = 1; frame <= 10; ++frame)
    {
        float frameWidth = (frame == 10) ? tenthFrameWidth : normalFrameWidth;
        Rectangle frameRect = {startX, topY, frameWidth, frameHeight};

        DrawRectangleRounded(frameRect, 0.08f, 8, Fade(BEIGE, 0.8f));
        DrawRectangleRoundedLinesEx(frameRect, 0.08f, 8, 2, PANEL_BORDER);

        char frameLabel[8];
        snprintf(frameLabel, sizeof(frameLabel), "%d", frame);
        drawCenteredText(frameLabel, (Rectangle){frameRect.x, frameRect.y - 26, frameRect.width, 20}, 18, MUTED_TEXT);

        if (frame < 10)
        {
            float shotWidth = frameRect.width / 2.0f;
            DrawLineEx((Vector2){frameRect.x + shotWidth, frameRect.y},
                       (Vector2){frameRect.x + shotWidth, frameRect.y + frameHeight * 0.45f}, 2.0f,
                       PANEL_BORDER);
            DrawLineEx((Vector2){frameRect.x, frameRect.y + frameHeight * 0.45f},
                       (Vector2){frameRect.x + frameRect.width, frameRect.y + frameHeight * 0.45f}, 2.0f,
                       PANEL_BORDER);

            char mark[8];
            getRollMark(game, frame, 1, mark, sizeof(mark));
            drawCenteredText(mark, (Rectangle){frameRect.x, frameRect.y + 4, shotWidth, 28}, 28, TEXT_COLOR);
            getRollMark(game, frame, 2, mark, sizeof(mark));
            drawCenteredText(mark, (Rectangle){frameRect.x + shotWidth, frameRect.y + 4, shotWidth, 28}, 28,
                             TEXT_COLOR);
        }
        else
        {
            float shotWidth = frameRect.width / 3.0f;
            DrawLineEx((Vector2){frameRect.x + shotWidth, frameRect.y},
                       (Vector2){frameRect.x + shotWidth, frameRect.y + frameHeight * 0.45f}, 2.0f,
                       PANEL_BORDER);
            DrawLineEx((Vector2){frameRect.x + shotWidth * 2.0f, frameRect.y},
                       (Vector2){frameRect.x + shotWidth * 2.0f, frameRect.y + frameHeight * 0.45f}, 2.0f,
                       PANEL_BORDER);
            DrawLineEx((Vector2){frameRect.x, frameRect.y + frameHeight * 0.45f},
                       (Vector2){frameRect.x + frameRect.width, frameRect.y + frameHeight * 0.45f}, 2.0f,
                       PANEL_BORDER);

            for (int roll = 1; roll <= 3; ++roll)
            {
                char mark[8];
                getRollMark(game, frame, roll, mark, sizeof(mark));
                drawCenteredText(mark,
                                 (Rectangle){frameRect.x + shotWidth * (roll - 1), frameRect.y + 4, shotWidth, 28},
                                 28, TEXT_COLOR);
            }
        }

        if ((frame < 10 && isRollVisible(game, frame, 2)) ||
            (frame == 10 && (isRollVisible(game, frame, 2) || game->isFinished)))
        {
            char totalText[16];
            snprintf(totalText, sizeof(totalText), "%d", game->player.frameScore[frame]);
            drawCenteredText(totalText,
                             (Rectangle){frameRect.x, frameRect.y + frameHeight * 0.5f, frameRect.width,
                                         frameHeight * 0.4f},
                             30, ACCENT_DARK);
        }

        startX += frameWidth + 10.0f;
    }
}

static void drawLane(const BowlingGame *game)
{
    Rectangle laneShadow = {83, 283, 1114, 355};
    Rectangle lane = {90, 275, 1100, 355};
    DrawRectangleRounded(laneShadow, 0.04f, 10, Fade(BLACK, 0.12f));
    DrawRectangleRounded(lane, 0.04f, 10, LANE_COLOR);
    DrawRectangleRoundedLinesEx(lane, 0.04f, 10, 3, PANEL_BORDER);

    for (int stripe = 0; stripe < 8; ++stripe)
    {
        Rectangle stripeRect = {lane.x + 90 + stripe * 110.0f, lane.y + 12, 54, lane.height - 24};
        DrawRectangleRounded(stripeRect, 0.12f, 6, Fade(WOOD_STRIPE, stripe % 2 == 0 ? 0.45f : 0.24f));
    }

    DrawRectangle((int)lane.x + 24, (int)lane.y, 44, (int)lane.height, Fade(ACCENT_DARK, 0.22f));
    DrawRectangle((int)(lane.x + lane.width - 68), (int)lane.y, 44, (int)lane.height, Fade(ACCENT_DARK, 0.22f));
    DrawLineEx((Vector2){lane.x + 100, lane.y + 32}, (Vector2){lane.x + 100, lane.y + lane.height - 32}, 4,
               Fade(WHITE, 0.65f));

    int standingPins = getStandingPins(game);
    Vector2 pinOrigin = {lane.x + lane.width - 210, lane.y + 105};
    Vector2 offsets[10] = {
        {45, 0}, {22, 34}, {68, 34}, {0, 68}, {45, 68},
        {90, 68}, {22, 102}, {68, 102}, {113, 102}, {45, 136},
    };

    for (int pin = 0; pin < 10; ++pin)
    {
        Vector2 center = {pinOrigin.x + offsets[pin].x, pinOrigin.y + offsets[pin].y};
        bool active = pin < standingPins;
        Color pinColor = active ? RAYWHITE : Fade(TEXT_COLOR, 0.18f);
        DrawCircleV(center, 13, pinColor);
        DrawCircleLines((int)center.x, (int)center.y, 13, PANEL_BORDER);
        if (active)
        {
            DrawCircleV((Vector2){center.x, center.y - 4}, 4, ACCENT_COLOR);
        }
    }

    float progress = ((float)(game->currentFrame - 1) * 2.0f + (float)(game->currentRoll - 1)) / 20.0f;
    if (game->isFinished)
    {
        progress = 1.0f;
    }
    float ballX = lane.x + 140 + progress * 760.0f;
    float ballY = lane.y + 275;
    DrawCircleGradient((int)ballX, (int)ballY, 34, ACCENT_COLOR, ACCENT_DARK);
    DrawCircleLines((int)ballX, (int)ballY, 34, PANEL_BORDER);
}

static Rectangle getPinButtonRectForValue(int value)
{
    int row = value / BUTTON_COLUMNS;
    int column = value % BUTTON_COLUMNS;
    return (Rectangle){90 + column * (BUTTON_WIDTH + BUTTON_GAP), 646 + row * (BUTTON_HEIGHT + 10), BUTTON_WIDTH,
                       BUTTON_HEIGHT};
}

static void drawPinButtons(const BowlingGame *game)
{
    int maxPins = getMaxPinsForRoll(game);
    Vector2 mouse = GetMousePosition();

    char prompt[128];
    snprintf(prompt, sizeof(prompt), "%d 프레임 %d 투구: 쓰러뜨린 핀 수를 선택하세요.",
             game->currentFrame, game->currentRoll);
    drawUiText(prompt, 90, 600, 28, TEXT_COLOR);

    for (int value = 0; value <= maxPins; ++value)
    {
        Rectangle rect = getPinButtonRectForValue(value);
        bool hovered = CheckCollisionPointRec(mouse, rect);
        DrawRectangleRounded(rect, 0.18f, 8, hovered ? ACCENT_COLOR : PANEL_COLOR);
        DrawRectangleRoundedLinesEx(rect, 0.18f, 8, 2, PANEL_BORDER);

        char label[8];
        snprintf(label, sizeof(label), "%d", value);
        drawCenteredText(label, rect, 28, hovered ? RAYWHITE : TEXT_COLOR);
    }
}

void drawNameEntryScreen(const char *nameBuffer)
{
    ClearBackground(BACKGROUND_COLOR);
    DrawCircleGradient(1040, 110, 210, Fade(ACCENT_COLOR, 0.36f), Fade(BACKGROUND_COLOR, 0.02f));
    DrawCircleGradient(180, 620, 180, Fade(LANE_COLOR, 0.58f), Fade(BACKGROUND_COLOR, 0.02f));

    drawUiText("Bowling Ray", 84, 88, 74, TEXT_COLOR);
    drawUiText("원본 bowling 예제의 점수 규칙을 raylib 화면으로 옮긴 버전", 88, 170, 28, MUTED_TEXT);

    Rectangle panel = {82, 252, 560, 220};
    DrawRectangleRounded(panel, 0.05f, 8, PANEL_COLOR);
    DrawRectangleRoundedLinesEx(panel, 0.05f, 8, 3, PANEL_BORDER);

    drawUiText("플레이어 이름", 116, 292, 28, TEXT_COLOR);
    Rectangle inputRect = {116, 342, 360, 64};
    DrawRectangleRounded(inputRect, 0.12f, 8, BACKGROUND_COLOR);
    DrawRectangleRoundedLinesEx(inputRect, 0.12f, 8, 2, PANEL_BORDER);
    drawUiText(nameBuffer[0] == '\0' ? "이름을 입력하세요" : nameBuffer, 136, 360, 28,
               nameBuffer[0] == '\0' ? MUTED_TEXT : TEXT_COLOR);

    Rectangle startButton = getStartButtonBounds();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), startButton);
    DrawRectangleRounded(startButton, 0.2f, 8, hovered ? ACCENT_DARK : ACCENT_COLOR);
    drawCenteredText("게임 시작", startButton, 30, RAYWHITE);

    drawUiText("Enter로 시작, Backspace로 수정", 116, 428, 22, MUTED_TEXT);
}

void drawGameScreen(const BowlingGame *game)
{
    ClearBackground(BACKGROUND_COLOR);
    drawScoreBoard(game);
    drawLane(game);
    drawPinButtons(game);
}

void drawFinishScreen(const BowlingGame *game)
{
    drawGameScreen(game);

    Rectangle overlay = {320, 212, 640, 260};
    DrawRectangleRounded(overlay, 0.05f, 8, Fade(PANEL_COLOR, 0.96f));
    DrawRectangleRoundedLinesEx(overlay, 0.05f, 8, 3, PANEL_BORDER);

    drawUiText("게임 종료", 565, 252, 42, TEXT_COLOR);

    char total[64];
    snprintf(total, sizeof(total), "최종 점수 %d", game->player.frameScore[10]);
    drawUiText(total, 518, 314, 36, ACCENT_DARK);
    drawUiText("다시 시작해서 새 게임을 플레이할 수 있습니다.", 424, 364, 24, MUTED_TEXT);

    Rectangle restartButton = getRestartButtonBounds();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), restartButton);
    DrawRectangleRounded(restartButton, 0.2f, 8, hovered ? ACCENT_DARK : ACCENT_COLOR);
    drawCenteredText("다시 시작", restartButton, 28, RAYWHITE);
}

Rectangle getStartButtonBounds(void)
{
    return (Rectangle){116, 496, 190, 58};
}

Rectangle getRestartButtonBounds(void)
{
    return (Rectangle){544, 408, 192, 56};
}

int getPinButtonValue(const BowlingGame *game, Vector2 point)
{
    int maxPins = getMaxPinsForRoll(game);

    for (int value = 0; value <= maxPins; ++value)
    {
        if (CheckCollisionPointRec(point, getPinButtonRectForValue(value)))
        {
            return value;
        }
    }

    return -1;
}