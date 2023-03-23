#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
	Texture2D texture{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D idle{ LoadTexture("resources/characters/knight_idle_spritesheet.png") };
	Texture2D run{ LoadTexture("resources/characters/knight_run_spritesheet.png") };
	Vector2 screenPosition{};
	Vector2 worldPosition{};
	Vector2 worldPositionLastFrame{};


	float rightLeft{ 1.f };
	float runningTime{};
	float speed{ 4.f };
	int frame{};

	float scale{ 4.f };
	float height{};
	float width{};

	const int maxFrames{ 6 };
	const float updateTime{ 1.f / 12.f };
public:
	Character(int windowWidth, int windowHeight);

	Vector2 getWorldPos();
	void undoMovement();


	void tick(float deltaTime);
	Rectangle getCollisionRec();
};