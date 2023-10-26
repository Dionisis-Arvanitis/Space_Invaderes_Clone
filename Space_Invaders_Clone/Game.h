#pragma once

#include "player.h"
#include "bullet.h"
#include "vector"
#include "Invader.h"
#include "pilar.h"

class Game
{
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_DEAD, STATUS_VICTORY } status_t;

	const int totalPilars = 4;
	const int totalInvaders = 30;
	const int totalShots = 10;
	const int totalInvaderShots = 3;

	int enemyShotCounter = 0;
	int shotCounter = 0;
	int score = 0;

	float last_time_shot = 0.0f;
	float enemy_Shot = 1000.0f;

	bool all_pilars = false;
	bool all_invaders = false;
	bool player_initialized = false;
	bool debug_mode = false;
	bool diedSound = false;
	bool victorySound = false;


	Player * player = nullptr;
	Invader* badGuyList[30];
	Bullet* shots[10];
	Bullet* enemyShots[3];
	Pilar* pilars[4];
	

	void spawnInvaders();
	void spawnPilars();
	void pillarCollision();
	void collisionWithInvaders();
	void playerBullets();
	void moveInvaders();
	void invaderShots();
	void checkInvaderShots();
	
	bool checkEnemyBulletsCollision(Bullet* shot);
	bool checkPilarCollisionWithInvader(Pilar* pilar, Invader* enemy);
	bool checkCollisionBullet(Invader *target, Bullet *shot);
	bool checkCollisionWithInvader(Invader* target);
	bool checkPilars(Pilar* pilar, Bullet* shot);
	
	status_t status = STATUS_START;

	void updateStartScreen();
	void updateLevelScreen();
	void updateDeadScreen();
	void updateVictoryScreen();

	void drawStartScreen();
	void drawLevelScreen();
	void drawDeadScreen();
	void drawVictoryScreen();

public:

	void update();
	void draw();
	void init();
	int getScore() { return score; }
	Game();
	~Game(); 
};