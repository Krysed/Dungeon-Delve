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
#include <vector>
#include "src/HealthIncrease.h"
#include "src/Character.h"
#include "src/GoldCoin.h"
#include "src/Globals.h"
#include "mapLayouts.h"
#include "src/Potion.h"
#include "src/Stairs.h"
#include "src/Enemy.h"
#include "src/Prop.h"
#include "raymath.h"
#include "screens.h"
#include "src/Key.h"
#include "raylib.h"

static int framesCounter = 0;
static int finishScreen = 0;
int Character::experience = 0;
int Character::goldAmount = 0;
int Character::key = 0;
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

    //fix sound
    Sound game = LoadSound(gameplayMusic);
    SetMusicVolume(music, 0.1f);
    PlaySound(game);

    Texture2D map = LoadTexture(baseMap);
    Vector2 mapPosition{ 0.0f,0.0f };
    Character player{ windowWidth,windowHeight };

    //populating level with props
    std::vector<Prop> props{};
    std::cout << mapLayout->length() << "\n\n";
    for (int i = 0; i < numOfProps; i++)
    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapLayout[i][j] == ' ')continue;
            else if (mapLayout[i][j] == 'x')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(rockTexture) });
            else if (mapLayout[i][j] == 'o')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85 }, LoadTexture(logTexture) });
            else if (mapLayout[i][j] == 's')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(signTexture) });
            else if (mapLayout[i][j] == 'b')props.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(bushTexture) });
        }
    }

    //potion test
    Potion pot(Vector2{500.f,500.f}, LoadTexture(potionTexture));
    GoldCoin gold(Vector2{ 550.f,500.f }, LoadTexture(coinTexture));
    Key key(Vector2{ 600.f,500.f }, LoadTexture(keyTexture));
    HealthIncrease health(Vector2{ 500.f,550.f }, LoadTexture(healthTexture));
    Stairs stairs(Vector2{ 800.f,500.f }, LoadTexture(stairTexture));
    //Key
    Enemy goblin
    {
        Vector2{800.f,300.f},
        LoadTexture(goblinIdleTexture),
        LoadTexture(goblinRunTexture)
    };
    Enemy goblin2
    {
        Vector2{1200.f,300.f},
        LoadTexture(goblinIdleTexture),
        LoadTexture(goblinRunTexture)
    };
    Enemy goblin3
    {
        Vector2{1000.f,700.f},
        LoadTexture(goblinIdleTexture),
        LoadTexture(goblinRunTexture)
    };
    Enemy slime{ Vector2{800.f,400.f},
        LoadTexture(slimeIdleTexture),
        LoadTexture(slimeRunTexture)
    };
    Enemy slime2{ Vector2{800.f,1600.f},
        LoadTexture(slimeIdleTexture),
        LoadTexture(slimeRunTexture)
    };
    Enemy slime3{ Vector2{1300.f,1600.f},
        LoadTexture(slimeIdleTexture),
        LoadTexture(slimeRunTexture)
    };
    Enemy skeleton{ Vector2{700.f,800.f},
        LoadTexture(skeletonIdleTexture),
        LoadTexture(skeletonRunTexture)
    };
    Enemy skeleton2{ Vector2{700.f,1200.f},
        LoadTexture(skeletonIdleTexture),
        LoadTexture(skeletonRunTexture)
    };
    Enemy skeleton3{ Vector2{700.f,1500.f},
        LoadTexture(skeletonIdleTexture),
        LoadTexture(skeletonRunTexture)
    };
    Enemy* enemies[9]{
        &goblin,
        &goblin2,
        &goblin3,
        &slime,
        &slime2,
        &slime3,
        &skeleton,
        &skeleton2,
        &skeleton3
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

        if (IsKeyPressed(KEY_E) && CheckCollisionRecs(stairs.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
        {
            map = LoadTexture(dungeonMap);
        }
        mapPosition = Vector2Scale(player.getWorldPos(), -1.f);
        //Drawing map
        DrawTextureEx(map, mapPosition, 0.0f, mapScale, WHITE);
        player.tick(GetFrameTime());

        for (auto prop : props)
        {
            prop.Render(player.getWorldPos());
            if(!pot.getConsumed())pot.Render(player.getWorldPos());
            if (!gold.getConsumed())gold.Render(player.getWorldPos());
            if (!key.getConsumed())key.Render(player.getWorldPos());
            if (!health.getConsumed())health.Render(player.getWorldPos());
            stairs.Render(player.getWorldPos());

        }

        if (!player.getAlive()) 
        {
            DrawText("Game Over", 300.f, 80.f, 40, RED);
            Character::experience = 0;
            EndDrawing();
            continue;
        }
        else
        {
            //write Player character stats to screen
            std::string playerHealth = "Health: ";
            std::string playerExperience = "Experience: ";
            std::string playerGold = "Gold: ";
            std::string playerKey = "Key: ";

            playerHealth.append(std::to_string(player.getHealth()), 0, 5);
            playerExperience.append(std::to_string(Character::experience), 0, 5);
            playerGold.append(std::to_string(Character::goldAmount), 0, 5);
            playerKey.append(std::to_string(Character::key), 0, 5);
            DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
            DrawText(playerExperience.c_str(), 450.f, 45.f, 40, YELLOW);
            DrawText(playerGold.c_str(), 450.f, 90.f, 40, YELLOW);
            if(Character::key > 0) DrawText(playerKey.c_str(), 450.f, 135.f, 40, RED);

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
            /*DrawRectangleLines(
                prop.getCollisionRec(player.getWorldPos()).x,
                prop.getCollisionRec(player.getWorldPos()).y,
                prop.getCollisionRec(player.getWorldPos()).width,
                prop.getCollisionRec(player.getWorldPos()).height,
                RED
            );*/
            if (CheckCollisionRecs(prop.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                player.undoMovement();
            }
            if (CheckCollisionRecs(pot.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                pot.interact(&player);
            }
            if (CheckCollisionRecs(gold.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                gold.interact(&player);
            }
            if (CheckCollisionRecs(key.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                key.interact(&player);
            }
            if (CheckCollisionRecs(health.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
            {
                health.interact(&player);
            }
        }
        
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime(),&player);
            //debug lines
            //DrawRectangleLines(
            //    enemy->getCollisionRec().x,
            //    enemy->getCollisionRec().y,
            //    enemy->getCollisionRec().width,
            //    enemy->getCollisionRec().height,
            //    RED
            //);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), player.getWeaponCollisionRec()))
                {
                    if(enemy->getAlive()==true)
                        Character::experience++;
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
    UnloadSound(game);
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{

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