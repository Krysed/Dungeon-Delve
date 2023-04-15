#pragma once
#include "raylib.h"
#include "Enemy.h"

class Prop
{
public:
	Prop() {};
	Prop(Vector2 pos, Texture2D tex);
	~Prop();
	void Render(Vector2 knightPos);
	Rectangle getCollisionRec(Vector2 knightPos); // -- Prostok¹t kolizji --
	Vector2 getWorldPos() { return worldPos; }
	void setTexture(Texture2D tex);

private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

