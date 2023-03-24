#include "src/Character.h"


Character::Character(int windowWidth, int windowHeight)
{
    width = texture.width;// / maxFrames;
    height = texture.height;

    screenPosition = {
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width / 6.f),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * width / 6.f)
    };
}



void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
}