#pragma once

#include "gameobject.h"
#include "graphics.h"

class Invader : public GameObject, public Collidable
{
	graphics::Brush brush;
	int drawInvader;
	
	float pos_x, pos_y;
	float speed;
	float size;
	bool active = true;
	bool moveLeft = false;
	bool moveRight = true;
	bool wall = false;

public:

	float getPosY() { return pos_y; };
	float getPosX() { return pos_x; };

	bool getWall() { return wall; }
	void setWall(bool isThereAwall) { wall = isThereAwall; }

	bool getLeft() { return moveLeft; }
	void setLeft(bool left) { moveLeft = left; }
	bool getRight() { return moveRight; }
	void setRight(bool right) { moveRight = right; }

	void movePosY() { pos_y += 10.0f; }

	void setActive(bool a) { active = a; }

	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Invader(const class Game& mygame, float x, float y, int type);
	~Invader();
	Disk getCollisionHull() const override;
};