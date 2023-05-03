#include "NPC.h"

NPC::NPC(Vector2 pos, Texture2D idle_texture)
{
    startPostion = pos;
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    width = texture.width;
    height = texture.height;
}

Vector2 NPC::getScreenPos()
{
    return screenPosition;
}

void NPC::interact()
{

}
