#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    
    width = texture.width;
	height = texture.height;
}

void Enemy::tick(float deltaTime) 
{
	worldPositionLastFrame = worldPosition;

    //update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    //drawing character
    Rectangle source{ frame * width / 6.f,0.f,rightLeft * width / 6.f,height };
    Rectangle destination{ screenPosition.x,screenPosition.y,4.0f * width / 6.f,4.0f * height };
    DrawTexturePro(texture, source, destination, Vector2{}, 0.f, WHITE);
}