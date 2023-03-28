#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
	int windowWidth{};
	int windowHeight{};
	float health{ 100.f };
	
	Texture2D weapon{LoadTexture("resources/characters/weapon_sword.png")};
	Rectangle weaponCollisionRec{};

public:
	static int experience;
	Character(int windowWidth, int windowHeight);

	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;
	Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
	float getHealth() const { return health; }
	void takeDamage(float damage);
	void setWeaponTexture(Texture2D newWeapon) { weapon = newWeapon; }
};