#pragma once
#include "raylib.h"

class Prop
{
public:
	Prop();
	Prop(Vector2 pos,Texture2D tex);
	~Prop();
private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

