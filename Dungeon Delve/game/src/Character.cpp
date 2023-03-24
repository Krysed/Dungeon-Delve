#include "src/Character.h"


Character::Character(int windowWidth, int windowHeight):
    windowWidth(windowWidth),windowHeight(windowHeight)
{
    width = texture.width;// / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos() 
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width / 6.f),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * width / 6.f)
    };
}


void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;
    BaseCharacter::tick(deltaTime);
}