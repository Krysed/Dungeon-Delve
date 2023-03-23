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