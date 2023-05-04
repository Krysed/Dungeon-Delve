#pragma once

#include "raylib.h"
#include "Prop.h"
#include <string>

class NPC : public Prop
{
public:
	NPC();
	~NPC();
	NPC(Vector2 pos, Texture2D tex);
	void Render(Vector2 knightPos);
private:

};
