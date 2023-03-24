#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    
    width = texture.width;
	height = texture.height;
    speed = 3.5f;
}
void Enemy::setTarget(Character* character)
{
    target = character;
}
void Enemy::tick(float deltaTime) 
{
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(),screenPosition);
    //normalize toTarget
    toTarget = Vector2Normalize(toTarget);
    //multiply toTarget
    toTarget = Vector2Scale(toTarget, speed);
    //move the enemy
    worldPosition = Vector2Add(worldPosition, toTarget);

    screenPosition = Vector2Subtract(worldPosition,target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}
