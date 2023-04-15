#include "HealthIncrease.h"

#pragma once

HealthIncrease::HealthIncrease(Vector2 pos, Texture2D texture) : Item(pos, texture) {}

HealthIncrease::~HealthIncrease() {}

void HealthIncrease::interact(Character* player)
{
	if (getConsumed())return;
	player->setMaxHealth(increaseValue);
	player->heal(50);
	setConsumed(true);
}
