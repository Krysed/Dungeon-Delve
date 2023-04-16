#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitOptionsScreen(void)
{
    // TODO: Initialize OPTIONS screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Options Screen Update logic
void UpdateOptionsScreen(void)
{
    // TODO: Update OPTIONS screen variables here!

//----------------------------------------------------------------------------------
// Logic of button
//----------------------------------------------------------------------------------

    Rectangle buttonPlay = { 400, 300, 200, 50 };
    if (CheckCollisionPointRec(GetMousePosition(), buttonPlay))
    {
        //Change cursor on button
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonPlay) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        finishScreen = 2;
    }

}

// Options Screen Draw logic
void DrawOptionsScreen(void)
{
    // TODO: Draw OPTIONS screen here!

    // Draw the button
    DrawRectangle(290, 185, 220, 50, DARKGRAY);
    DrawText("PLAY GAME", 352, 200, 20, WHITE);

    DrawRectangle(290, 255, 220, 50, DARKGRAY);
    DrawText("SCORE BOARD", 343, 270, 20, WHITE);

    DrawRectangle(290, 325, 220, 50, DARKGRAY);
    DrawText("EXIT", 375, 340, 20, WHITE);
}

// Options Screen Unload logic
void UnloadOptionsScreen(void)
{
    // TODO: Unload OPTIONS screen variables here!
}

// Options Screen should finish?
int FinishOptionsScreen(void)
{
    return finishScreen;
}
