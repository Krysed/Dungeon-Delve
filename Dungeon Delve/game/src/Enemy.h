#pragma once
#include "raylib.h"
#include "raymath.h"

class Enemy
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
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

	Vector2 getWorldPos();
	void undoMovement();


	void tick(float deltaTime);
	Rectangle getCollisionRec();
};