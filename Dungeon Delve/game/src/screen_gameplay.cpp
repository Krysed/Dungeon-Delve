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
#include <algorithm>
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
#include "fstream"

static int framesCounter = 0;
static int finishScreen = 0;
int Character::experience = 0;
int Character::goldAmount = 0;
int Character::key = 0;

std::string currentMap;
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    Character::experience = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    const int windowWidth{ 800 };
    const int windowHeight{ 600 };
    const float mapScale{ 4.0f };

    int mapVar = 0;

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

    std::vector<Prop>dungeonProps{};
    for (int i = 0; i < numOfProps; i++)

    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapDungeonLayout[i][j] == ' ')continue;
            else if (mapDungeonLayout[i][j] == 'w')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(wall1Texture) });
            else if (mapDungeonLayout[i][j] == 'x')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85 }, LoadTexture(wall2Texture) });
            else if (mapDungeonLayout[i][j] == 's')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(wall3Texture) });
            else if (mapDungeonLayout[i][j] == 'b')dungeonProps.push_back(Prop{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(rockTexture) });
        }
    }

    std::vector<Prop>currentProps = props;
    //Enemies
    std::vector<Enemy> enemiesArray;
    for (int i = 0; i < numOfProps; i++)
    {
        for (int j = 0; j < numOfProps; j++)
        {
            if (mapLayoutEnemies[i][j] == ' ')continue;
            else if (mapLayoutEnemies[i][j] == 'x')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(goblinIdleTexture),LoadTexture(goblinRunTexture) });
            else if (mapLayoutEnemies[i][j] == 'o')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(slimeIdleTexture),LoadTexture(slimeRunTexture) });
            else if (mapLayoutEnemies[i][j] == 's')enemiesArray.push_back(Enemy{ Vector2{float(j) * 85,float(i) * 85}, LoadTexture(skeletonIdleTexture),LoadTexture(skeletonRunTexture) });
        }
    }
    std::vector<Enemy*> enemies;
    for (int i = 0; i < enemiesArray.size(); i++) {
        enemies.push_back(&enemiesArray[i]);
        enemies[i]->setSpeed(3.f);
    }


    //potion test
    Potion pot(Vector2{500.f,500.f}, LoadTexture(potionTexture));
    GoldCoin gold(Vector2{ 550.f,500.f }, LoadTexture(coinTexture));
    Key key(Vector2{ 600.f,500.f }, LoadTexture(keyTexture));
    HealthIncrease health(Vector2{ 500.f,550.f }, LoadTexture(healthTexture));
    Stairs stairs(Vector2{ 400.f,500.f }, LoadTexture(stairLockedTexture));

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
        // Fullscreen
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
        {
            ToggleFullscreen();
        }
        if (IsKeyPressed(KEY_E) && CheckCollisionRecs(stairs.getCollisionRec(player.getWorldPos()), player.getCollisionRec()))
        {
            if(mapVar == 0){
                if (stairs.getConsumed()) {
                    map = LoadTexture(dungeonMap);
                    currentMap = dungeonMap;
                    currentProps = dungeonProps;
                    mapVar = 1;
                    for (auto& prop : currentProps)prop.setScale(5.3f);
                    for (auto& enemy : enemies) {
                        enemy->setWorldPos(enemy->getStartPosition().x,enemy->getStartPosition().y);
                        enemy->setAlive(true);
                    }
                }
            }
            else if (mapVar == 1) {
                if (stairs.getConsumed()) {
                    map = LoadTexture(baseMap);
                    currentMap = baseMap;
                    currentProps = props;
                    mapVar = 0;
                }
            }
            if (Character::key > 0) {
                Character::key--;
                stairs.setTexture(LoadTexture(stairTexture));
                stairs.setConsumed(true);
            }
        }
        mapPosition = Vector2Scale(player.getWorldPos(), -1.f);
        //Drawing map
        DrawTextureEx(map, mapPosition, 0.0f, mapScale, WHITE);
        
        stairs.Render(player.getWorldPos());
        
        player.tick(GetFrameTime());
        
        if(!pot.getConsumed())pot.Render(player.getWorldPos());
        if (!gold.getConsumed())gold.Render(player.getWorldPos());
        if (!key.getConsumed())key.Render(player.getWorldPos());
        if (!health.getConsumed())health.Render(player.getWorldPos());

        for (auto prop : currentProps)
        {
            prop.Render(player.getWorldPos());
            //stairs.Render(player.getWorldPos());

        }

        if (!player.getAlive()) 
        {
            DrawText("Game Over", 300.f, 80.f, 40, RED);
            DrawText(TextFormat("Final Experience: %d", Character::experience), 210.f, 250.f, 40, YELLOW);
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
        for (auto prop : currentProps)
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

    // Saving final experience to file
    std::ofstream outfile;
    outfile.open ("./game/experience.txt", std::ios::app);
    outfile << Character::experience << " - "<< name << std::endl;
    outfile.close();
    Character::key = 0;
    Character::goldAmount = 0;
    Character::experience = 0;
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