#pragma once
#include "raylib.h"
//--------------------------------------------------------------------------
class Prop
{
public:
	Prop();
	Prop(Vector2 pos, Texture2D tex);
	~Prop();
	void Render(Vector2 knightPos);
	Rectangle getCollisionRec(Vector2 knightPos); // -- Prostok¹t kolizji --
private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

