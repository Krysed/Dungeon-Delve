#include "Prop.h"
#include "raymath.h"

//----------------------------------------------------------------------------
Prop::Prop(Vector2 pos, Texture2D tex) : // -- Konstruktor z inicjalizacją --
	worldPos(pos), texture(tex)
{}
Prop::~Prop() {}
void Prop::Render(Vector2 knightPos)
{
	Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
	DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos) // -- Prostokąt kolizji --
{
	Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		texture.width * scale,
		texture.height * scale
	};
}

void Prop::setTexture(Texture2D tex)
{
	texture = tex;
}
void Prop::setScale(float scale)
{
	this->scale = scale;
}