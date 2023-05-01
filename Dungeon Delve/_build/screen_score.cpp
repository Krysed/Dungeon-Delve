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
    TraceLog(LOG_INFO, "Drawing sorted file contents...");

    // Draw sorted file content on the screen
    int lineCount = 0;
    for (int i = 0; i < lines.size() && lineCount < 10; i++) {
        DrawText(lines[i].c_str(), 100, 100 + lineCount * 20, 20, BLACK);
        lineCount++;
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
