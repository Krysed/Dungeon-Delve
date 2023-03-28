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
#include <iostream>
#include <string>
#include "mapLayouts.h"
#include "raylib.h"
#include "screens.h"
#include "raymath.h"
#include "src/Character.h"
#include "src/Prop.h"
#include "src/Enemy.h"
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
int Character::experience = 0;
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    const int windowWidth{ 800 };
    const int windowHeight{ 600 };
    const float mapScale{ 4.0f };

    Texture2D map = LoadTexture("resources/maps/test_map1.png");
    Vector2 mapPosition{ 0.0f,0.0f };
    Character player{ windowWidth,windowHeight }; // -- Powo³anie do ¿ycia obiektu "player" -- 

    //populating level with props
    Prop props[200]{};
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (mapLayout[i][j] == ' ')continue;
            else if (mapLayout[i][j] == 'x')props[j] = Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture("resources/props/Rock.png")};
            else if (mapLayout[i][j] == 'o')props[j] = Prop{ Vector2{float(j) * 110,float(i) * 85}, LoadTexture("resources/props/Log.png") };
            else if (mapLayout[i][j] == 's')props[j] = Prop{ Vector2{float(j) * 110,float(i) * 85}, LoadTexture("resources/props/sign.png") };
            else if (mapLayout[i][j] == 'b')props[j] = Prop{ Vector2{float(j) * 110,float(i) * 85}, LoadTexture("resources/props/Bush.png") };
        }
    }


    Enemy goblin{ Vector2{800.f,300.f},
        LoadTexture("resources/characters/goblin_idle_spritesheet.png"),
        LoadTexture("resources/characters/goblin_run_spritesheet.png") 
    };
    Enemy slime{ Vector2{800.f,400.f},
        LoadTexture("resources/characters/slime_idle_spritesheet.png"),
        LoadTexture("resources/characters/slime_run_spritesheet.png")
    };
    Enemy* enemies[2]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&player);
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsKeyPressed(KEY_ESCAPE))
        {
            finishScreen = 1;
            //PlaySound(fxCoin);
        }

        mapPosition = Vector2Scale(player.getWorldPos(), -1.f);
        //Drawing map
        DrawTextureEx(map, mapPosition, 0.0f, mapScale, WHITE);
        player.tick(GetFrameTime());

        for (auto prop : props)
        {
            prop.Render(player.getWorldPos());
        }

        if (!player.getAlive()) 
        {
            DrawText("Game Over", 300.f, 80.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            //write Player character stats to screen
            std::string playerHealth = "Health: ";
            std::string playerExperience = "Experience: ";
            playerHealth.append(std::to_string(player.getHealth()), 0, 5);
            playerExperience.append(std::to_string(Character::experience), 0, 5);
            DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
            DrawText(playerExperience.c_str(), 450.f, 45.f, 40, YELLOW);

        }
        //checking player-map bounds
        if (
            player.getWorldPos().x < 0.f ||
            player.getWorldPos().y < 0.f ||
            player.getWorldPos().x + windowWidth > map.width * mapScale ||
            player.getWorldPos().y + windowHeight > map.height * mapScale
            ) {
            player.undoMovement();
        }
        //checking player-prop collision
        for (auto prop : props)
        {
            //debug lines
            DrawRectangleLines(
                prop.getCollisionRec(player.getWorldPos()).x,
                prop.getCollisionRec(player.getWorldPos()).y,
                prop.getCollisionRec(player.getWorldPos()).width,
                prop.getCollisionRec(player.getWorldPos()).height,
                RED
            );
            if (CheckCollisionRecs(prop.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                player.undoMovement();
            }
        }
        
        //checking enemy-prop collision
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime(),&player);
            //debug lines
            DrawRectangleLines(
                enemy->getCollisionRec().x,
                enemy->getCollisionRec().y,
                enemy->getCollisionRec().width,
                enemy->getCollisionRec().height,
                RED
            );

            for (auto prop: props) {
                //debug info
                //std::cout << "prop: " << prop.getCollisionRec(enemy->getScreenPos()).x << " " << prop.getCollisionRec(enemy->getScreenPos()).y << "\n";
                //std::cout << "enemy: " << enemy->getCollisionRec().x << " " << enemy->getCollisionRec().y << "\n";

                if (CheckCollisionRecs(enemy->getCollisionRec(), prop.getCollisionRec(player.getScreenPos())))
                { 
                    enemy->undoMovement();
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), player.getWeaponCollisionRec()))
                {
                    if(enemy->getAlive()==true)Character::experience++;
                    enemy->setAlive(false);
                }
            }
        }
        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            player.setSpeed(player.getSprintSpeed());
        }
        else
            player.setSpeed(player.getBaseSpeed());
        UnloadGameplayScreen();
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    EndDrawing();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}