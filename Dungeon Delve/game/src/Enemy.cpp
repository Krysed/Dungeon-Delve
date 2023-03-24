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
    velocity = Vector2Subtract(target->getScreenPos(),getScreenPos());
    BaseCharacter::tick(deltaTime);
}
Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPosition, target->getWorldPos());
}
