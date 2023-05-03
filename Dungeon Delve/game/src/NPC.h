#pragma once
#include "BaseCharacter.h"

class NPC : public BaseCharacter
{
public:
	void interact(); //todo
	NPC(Vector2 pos, Texture2D idle_texture);
	Vector2 getScreenPos() override;
	
	//tick

private:
	Vector2 startPostion{};

	int windowWidth{};
	int windowHeight{};
};