#pragma once
#include "gameobject.h"
#include "graphics.h"


class Bullet : public GameObject, public Collidable
{

	int updateDirection;

	float pos_x, pos_y;
	float speed;
	float size;
	float height = 0.5f;
	graphics::Brush brush;
	bool active = true;

public:

	void setActive(bool a) { active = a; }

	
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Bullet(const class Game& mygame, float x, float y, int direction);
	~Bullet();
	Disk getCollisionHull() const override;
};