#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Character.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
private:
	Character* target;

public:
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

	void setTarget(Character* character);
	virtual void tick(float deltaTime) override;
}; 
#endif