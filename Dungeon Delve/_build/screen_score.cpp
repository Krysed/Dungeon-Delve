#include "raylib.h"
#include "screens.h"
#include <string.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Image image;
static Texture2D background;
static float alpha = 0.0f;
static bool isIncreasing = true;

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitScoreScreen(void)
{
    // TODO: Initialize OPTIONS screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    image = LoadImage("resources/screens/menu.png");
    ImageResize(&image, 800, 600);
    background = LoadTextureFromImage(image);
}

// Options Screen Update logic
void UpdateScoreScreen(void)
{
}

// Options Screen Draw logic
void DrawScoreScreen(void)
{
    // TODO: Draw OPTIONS screen here!
}

// Options Screen Unload logic
void UnloadScoreScreen(void)
{
    // TODO: Unload OPTIONS screen variables here!
}

// Options Screen should finish?
int FinishScoreScreen(void)
{
    return finishScreen;
}
