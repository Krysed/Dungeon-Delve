#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:

public:
	Character(int windowWidth, int windowHeight);

	void tick(float deltaTime);
};