#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

Vector2 BaseCharacter::getWorldPos()
{
    return worldPosition;
}


void BaseCharacter::undoMovement()
{
    worldPosition = worldPositionLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle
    {
        screenPosition.x,
        screenPosition.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
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