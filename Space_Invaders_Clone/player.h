#pragma once
#include "gameobject.h"
#include "config.h"

class Player : public GameObject, public Collidable
{
	float speed = 10.0f;
	float pos_x = CANVAS_WIDTH/2, pos_y = 440.60f;
	float height = 1.0f;
	float life = 1.0f;
	int alive = 5;



public:
	Player(const class Game& mygame);



	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; };
	float getPosX() { return pos_x; };
	Disk getCollisionHull() const override;
	float getRemaingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	void amIAlive() { alive = alive - 1; }
	bool damage() { return alive <= 0; }
};