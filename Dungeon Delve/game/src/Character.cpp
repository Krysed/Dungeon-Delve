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
    worldPositionLastFrame = worldPosition;

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