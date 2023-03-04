/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "raymath.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!

    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    
    // Press enter or tap to change to ENDING screen
    
    //ADD GLOBAL VARIABLES
    //temp
    const int windowWidth{ 800 };
    const int windowHeight{ 600 };

    Texture2D testMap = LoadTexture("resources/maps/test_map1.png");
    Vector2 mapPosition{ 0.0,0.0 };
    float movementSpeed = 4.f;

    Texture2D hero_idle = LoadTexture("resources/characters/knight_idle_spritesheet.png");
    Texture2D hero_run = LoadTexture("resources/characters/knight_run_spritesheet.png");

    Texture2D hero = LoadTexture("resources/characters/knight_idle_spritesheet.png");
    Vector2 heroPosition{
        (float)windowWidth / 2.f - 4.0f * (0.5 * (float)hero.width / 6.f),
        (float)windowHeight / 2.f - 4.0f * (0.5 * (float)hero.width / 6.f)
    };
    //direction
    float rightLeft{ 1.f };
    //animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.f / 12.f };



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);


        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0) 
        {
            mapPosition = Vector2Subtract(mapPosition,Vector2Scale(Vector2Normalize(direction),movementSpeed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            hero = hero_run;
        }
        else
        {
            hero = hero_idle;
        }

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            finishScreen = 1;
            PlaySound(fxCoin);
        }
        //Drawing map
        DrawTextureEx(testMap, mapPosition, 0, 4, WHITE);

        //update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        //drawing character
        Rectangle source{ frame*(float)hero.width / 6.f,0.f,rightLeft*(float)hero.width / 6.f,(float)hero.height };
        Rectangle destination{ heroPosition.x,heroPosition.y,4.0f * (float)hero.width / 6.f,4.f * (float)hero.height };
        DrawTexturePro(hero, source, destination, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    
    /*DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);*/

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}