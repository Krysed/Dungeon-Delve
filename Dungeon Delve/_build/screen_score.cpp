#include "raylib.h"
#include "screens.h"
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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
    image = LoadImage("resources/screens/menutwo.png");
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
    std::ifstream file("./game/experience.txt");
    if (!file) {
        TraceLog(LOG_WARNING, "Cannot open file");
        return;
    }

    std::string line;
    std::vector<std::string> lines;

    // Read each line from file and store it in a vector
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // Sort the vector numerically
    std::sort(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) {
        return std::stoi(a) > std::stoi(b);
        });

    file.close();

    // Draw sorted file content on the screen
    int lineCount = 0;
    for (int i = 0; i < lines.size() && lineCount < 10; i++) {
        DrawText(lines[i].c_str(), 335, 180 + lineCount * 20, 20, BLACK);
        lineCount++;

        
    }

    DrawRectangle(240, 130, 326, 30, DARKGRAY);
    DrawText("TOP 10", 368, 135, 20, WHITE);

    //Button
    DrawRectangle(290, 400, 220, 50, DARKGRAY);
    DrawText("RETURN", 358, 415, 20, WHITE);
    Rectangle buttonReturn = { 290, 400, 220, 50 };

    if (CheckCollisionPointRec(GetMousePosition(), buttonReturn))
    {
        //Change cursor on button
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        //Animation
        if (isIncreasing)
        {
            alpha += 0.02f;
            if (alpha > 1.0f)
            {
                alpha = 1.0f;
                isIncreasing = false;
            }
        }
        else
        {
            alpha -= 0.02f;
            if (alpha < 0.0f)
            {
                alpha = 0.0f;
                isIncreasing = true;
            }
        }
        Color rectColor = { 79, 79, 79, (unsigned char)(alpha * 255) };
        DrawRectangle(290, 400, 220, 50, rectColor);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if (CheckCollisionPointRec(GetMousePosition(), buttonReturn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Set finishScreen to the ID of the screen you want to switch to
        finishScreen = 1;
    }
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
