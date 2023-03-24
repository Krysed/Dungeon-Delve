#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
	int windowWidth{};
	int windowHeight{};
public:
	Character(int windowWidth, int windowHeight);

	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;
};