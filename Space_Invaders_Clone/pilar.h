#pragma once

#include "gameobject.h"
#include "graphics.h"

class Pilar : public GameObject, public Collidable
{
	graphics::Brush brush;
	int life = 3;
	float pos_x, pos_y;
	float size;
	bool active = true;


public:
	void tookDamage() { life -= 1; }
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Pilar(const class Game& mygame, float x);
	~Pilar();
	Disk getCollisionHull() const override;
};