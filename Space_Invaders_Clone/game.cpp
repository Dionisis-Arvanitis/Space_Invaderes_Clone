#include "game.h"
#include "graphics.h"
#include "config.h"
#include "player.h"
#include "invader.h"
#include "pilar.h"

void Game::pillarCollision()
{
	for (int i = 0; i < totalPilars; i++)
	{
		for (int j = 0; j < totalShots; j++)
		{
			if (checkPilars(pilars[i], shots[j]))
			{
				delete shots[j];
				shots[j] = nullptr;
				shotCounter--;

				pilars[i]->tookDamage();
			}
		}

		for (int j = 0; j < totalInvaderShots; j++)
		{
			if (checkPilars(pilars[i], enemyShots[j]))
			{
				delete enemyShots[j];
				enemyShots[j] = nullptr;
				enemyShotCounter--;

				pilars[i]->tookDamage();
			}
		}

		for (int j = 0; j < totalInvaders; j++)
		{
			if (checkPilarCollisionWithInvader(pilars[i], badGuyList[j]))
			{
				delete badGuyList[j];
				badGuyList[j] = nullptr;

				pilars[i]->tookDamage();
			}
		}
	}
}

bool Game::checkPilarCollisionWithInvader(Pilar* pilar, Invader* enemy)
{
	if (!pilar || !enemy)
	{
		return false;
	}

	Disk d1 = pilar->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.center_x - d2.center_x;
	float dy = d1.center_y - d2.center_y;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::spawnPilars()
{
	if (!all_pilars)
	{
		float x = 200.0f;
		for (int i = 0; i < totalPilars; i++)
		{
			pilars[i] = new Pilar(*this, x);
			x += 200.0f;

			if (i == 3)
			{
				all_pilars = true;
			}
		}
	}
}

void Game::playerBullets()
{
	for (int i = 0; i < totalShots; i++)
	{
		if (shots[i] && !shots[i]->isActive())
		{
			delete shots[i];
			shots[i] = nullptr;
			shotCounter--;
		}

		if (shots[i])
		{
			shots[i]->update();
		}
	}

	for (int shot = 0; shot < totalShots; shot++)
	{
		if (shots[shot])
		{
			for (int i = 0; i < totalInvaders; i++)
			{
				if (badGuyList[i])
				{
					if (checkCollisionBullet(badGuyList[i], shots[shot]))
					{
						delete badGuyList[i];
						badGuyList[i] = nullptr;

						delete shots[shot];
						shots[shot] = nullptr;

						shotCounter--;

					}
				}
			}
		}
	}
}

void Game::spawnInvaders()
{
	float x = 75.0f;
	float y = 50.0f;
	int type = 1;

	if(!all_invaders)
	{
		for (int i = 0; i < totalInvaders; i++)
		{
			if (i == 10 || i == 20)
			{
				x = 75.0f;
				y += 50.0f;
				type += 1;
			}

			badGuyList[i] = new Invader(*this, x, y, type);
			x += 50.0f;

			if (i == 29)
			{
				all_invaders = true;
			}
		}
	}
}

void Game::moveInvaders()
{
	for (int i = 0; i < totalInvaders; i++)
	{
		if (badGuyList[i] && !badGuyList[i]->isActive())
		{
			delete badGuyList[i];
			badGuyList[i] = nullptr;
		}

		if (badGuyList[i]) {

			if (badGuyList[i]->getWall())
			{
				badGuyList[i]->movePosY();
				if (badGuyList[i]->getLeft()) {
					for (int j = 0; j < totalInvaders; j++)
					{
						if (badGuyList[j] && j != i)
						{
							badGuyList[j]->movePosY();
							badGuyList[j]->setRight(false);
							badGuyList[j]->setLeft(true);
						}
					}
				}
				else
				{
					for (int j = 0; j < totalInvaders; j++)
					{
						if (badGuyList[j] && j != i)
						{
							badGuyList[j]->movePosY();
							badGuyList[j]->setLeft(false);
							badGuyList[j]->setRight(true);
						}
					}
				}
				badGuyList[i]->setWall(false);
			}
			badGuyList[i]->update();
		}
	}
}

void Game::invaderShots()
{
	if (graphics::getGlobalTime() > enemy_Shot + 1000.0f)
	{
		for (int i = 0; i < totalInvaderShots; i++)
		{
			int x = rand() % 30;   // random invader 0-29
			while(!badGuyList[x])
			{
				x = rand() % 30;
			}

			if (enemyShotCounter < totalInvaderShots && badGuyList[x])
			{
				enemyShots[enemyShotCounter] = new Bullet(*this, badGuyList[x]->getPosX(), badGuyList[x]->getPosY() + 50.0f, -1);
				enemyShotCounter++;
			}
		}
		enemy_Shot = graphics::getGlobalTime();
	}
}

void Game::checkInvaderShots()
{
	for (int i = 0; i < totalInvaderShots; i++)
	{

		if (checkEnemyBulletsCollision(enemyShots[i]))
		{
			graphics::playSound(std::string(ASSET_PATH) + "Bruh - Sound Effect (HD).mp3", 0.2f, false);
			delete enemyShots[i];
			enemyShots[i] = nullptr;
			enemyShotCounter--;
		}


		if (enemyShots[i] && !enemyShots[i]->isActive())
		{
			delete enemyShots[i];
			enemyShots[i] = nullptr;
			enemyShotCounter--;
		}

		if (enemyShots[i])
		{
			enemyShots[i]->update();
		}
	}
}

bool Game::checkEnemyBulletsCollision(Bullet* shot)
{
	
	if (!player || !shot)
	{
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = shot->getCollisionHull();

	float dx = d1.center_x - d2.center_x;
	float dy = d1.center_y - d2.center_y;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		player->amIAlive();
		player->drainLife(0.2f);
		
		if (player && player->damage())
		{
			graphics::stopMusic(0);
			status = STATUS_DEAD;
			delete player;
			player = nullptr;
		}
		
		return true;
	}
	else
		return false;
}

bool Game::checkPilars(Pilar* pilar, Bullet* shot)
{
	if (!pilar || !shot)
	{
		return false;
	}

	Disk d1 = shot->getCollisionHull();
	Disk d2 = pilar->getCollisionHull();

	float dx = d1.center_x - d2.center_x;
	float dy = d1.center_y - d2.center_y;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::checkCollisionBullet(Invader *target, Bullet *shot)
{
	if (!shot || !target)
	{
		return false;
	}

	Disk d1 = shot->getCollisionHull();
	Disk d2 = target->getCollisionHull();

	float dx = d1.center_x - d2.center_x;
	float dy = d1.center_y - d2.center_y;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		score += 100;
		if (score == 3000 && player)
		{

			graphics::stopMusic(0);
			status = STATUS_VICTORY;
			delete player;
			player = nullptr;
		}
		return true;
	}
	else
	{
		return false;
	}	
}

bool Game::checkCollisionWithInvader(Invader* target)
{
	if (!player || !target)
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = target->getCollisionHull();

	float dx = d1.center_x - d2.center_x;
	float dy = d1.center_y - d2.center_y;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::collisionWithInvaders()
{
	for (int i = 0; i < totalInvaders; i++)
	{
		if (checkCollisionWithInvader(badGuyList[i]))
		{
			graphics::stopMusic(0);
			status = STATUS_DEAD;
			delete player;
			player = nullptr;
		}
	}
}

void Game::updateStartScreen()
{

	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		graphics::stopMusic(0);
		status = STATUS_PLAYING;
		graphics::playMusic(std::string(ASSET_PATH) + "Wii Music - Gaming Background Music (HD).mp3", 0.2f, true, 4000);
	}
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		graphics::stopMusic(0);
		status = STATUS_PLAYING;
		graphics::playMusic(std::string(ASSET_PATH) + "Wii Music - Gaming Background Music (HD).mp3", 0.2f, true, 4000);
	}
}

void Game::updateLevelScreen()
{

	if (graphics::getKeyState(graphics::SCANCODE_SPACE) && graphics::getGlobalTime() > 2000.0f)
	{
		if (!shots[shotCounter] )
		{
			if (graphics::getGlobalTime() > last_time_shot + 400.0f)
			{	
				last_time_shot = graphics::getGlobalTime();
				graphics::playSound(std::string(ASSET_PATH) + "Nope.mp3", 0.2f, false);
				shots[shotCounter] = new Bullet(*this, player->getPosX(), player->getPosY(), 1);
				shotCounter++;
			}
		}
	}
	
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}

	if (player)
	{
		player->update();
		playerBullets();
	}
		
	spawnInvaders();
	spawnPilars();
	
	if (all_invaders)
	{
		moveInvaders();
		invaderShots();
		checkInvaderShots();
		collisionWithInvaders();
	}
		
	if (all_pilars)
	{
		pillarCollision();
		for (int i = 0; i < totalPilars; i++)
		{
			if (pilars[i] && !pilars[i]->isActive())
			{
				delete pilars[i];
				pilars[i] = nullptr;

			}
			if(pilars[i])
				pilars[i]->update();
		}
	}
}

void Game::updateDeadScreen()
{
	if (!diedSound)
	{
		graphics::playSound(std::string(ASSET_PATH) + "YOU DIED (HD).mp3", 0.2f, false);
		diedSound = true;
	}
}

void Game::updateVictoryScreen()
{
	if (!victorySound)
	{
		graphics::playSound(std::string(ASSET_PATH) + "CENA.mp3", 0.2f, false);
		victorySound = true;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Press Enter to start");
	graphics::drawText(CANVAS_WIDTH/2 - 150.0f, CANVAS_HEIGHT/2, 30, info, br);
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "night.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	if (player) {
		char info[40];
		sprintf_s(info, "SCORE: %i", getScore());
		graphics::drawText(50, 50, 40, info, br);
		player->draw();
		
		float player_life = player ? player->getRemaingLife() : 0.0f;
		br.outline_opacity = 1.0f;
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.2f;
		br.fill_color[2] = 0.0f;
		br.texture = "";
		br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
		br.fill_secondary_color[1] = 0.2f;
		br.fill_secondary_color[2] = 0.2 * (1.0f - player_life) + player_life * 1.0f;
		br.gradient = true;
		br.gradient_dir_u = 1.0f;
		br.gradient_dir_v = 0.0f;
		graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 40, br);

		br.outline_opacity = 1.0f;
		br.gradient = false;
		br.fill_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 40, br);

		for (int i = 0; i < totalShots; i++)
		{
			if (shots[i] && shots[i]->isActive())
			{
				shots[i]->draw();
			}
		}
	}

	if (all_pilars)
	{
		for (int i = 0; i < totalPilars; i++)
		{
			if (pilars[i])
				pilars[i]->draw();
		}
	}

	if (all_invaders)
	{
		for (int i = 0; i < totalInvaders; i++)
		{
			if (badGuyList[i])
				badGuyList[i]->draw();
		}

		for (int i = 0; i < totalInvaderShots; i++)
		{
			if (enemyShots[i])
				enemyShots[i]->draw();
		}

	}

	
}

void Game::drawDeadScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "You_Died_Screen.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 , CANVAS_WIDTH, CANVAS_WIDTH, br);

	char info[40];
	sprintf_s(info, "SCORE: %i", getScore());
	graphics::drawText(CANVAS_WIDTH / 2 - 100.0f, 150, 40, info, br);
	
}

void Game::drawVictoryScreen()
{
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "night.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	br.texture = std::string(ASSET_PATH) + "u win noback.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	char info[40];
	sprintf_s(info, "SCORE: %i", getScore());
	graphics::drawText(50, 50, 40, info, br);
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if(status == STATUS_PLAYING)
	{
		updateLevelScreen();

	}
	else if(status == STATUS_DEAD)
	{
		updateDeadScreen();
	}
	else if (status == STATUS_VICTORY)
	{
		updateVictoryScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if(status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else if(status == STATUS_DEAD)
	{
		drawDeadScreen();
	}
	else if (status == STATUS_VICTORY)
	{
		drawVictoryScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "letters.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "Star Wars.mp3", 0.2f, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}

	for (int i = 0; i < totalInvaders; i++)
	{
		if (badGuyList[i])
		{
			delete badGuyList[i];
		}
	}

	for (int i = 0; i < totalPilars; i++)
	{
		if (pilars[i])
		{
			delete pilars[i];
		}
	}

	for (int i = 0; i < totalInvaderShots; i++)
	{
		if (enemyShots[i])
		{
			delete enemyShots[i];
		}
	}

	for (int i = 0; i < totalShots; i++)
	{
		if (shots[i])
			delete shots[i];
	}
}
