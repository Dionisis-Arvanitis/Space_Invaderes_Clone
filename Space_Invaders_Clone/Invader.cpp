#include "invader.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"


void Invader::update()
{
	if (moveLeft)
	{
		pos_x -= speed * graphics::getDeltaTime();
		if (pos_x < 0)
		{
			pos_x = 0;
			moveRight = true;
			moveLeft = false;
			wall = true;
		}
	}

	if (moveRight)
	{
		pos_x += speed * graphics::getDeltaTime();
		if (pos_x > CANVAS_WIDTH)
		{
			pos_x = CANVAS_WIDTH;
			moveRight = false;
			moveLeft = true;
			wall = true;
		}
	}
}

void Invader::draw()
{
	if (drawInvader == 2)
	{
		brush.texture = std::string(ASSET_PATH) + "green.png";
		
	}
	if (drawInvader == 1)
	{
		brush.texture = std::string(ASSET_PATH) + "red face.png";
	}
	if (drawInvader == 3)
	{
		brush.texture = std::string(ASSET_PATH) + "purple skull.png";
	}
	brush.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();
}

void Invader::init()
{
	speed = 0.1f;
	size = 45;
	brush.outline_opacity = 0.0f;

}

Invader::Invader(const Game& mygame, float x, float y, int type) 
	:GameObject(mygame)
{
	drawInvader = type;
	pos_x = x;
	pos_y = y;
	init();
}

Invader::~Invader()
{
}

Disk Invader::getCollisionHull() const
{
	Disk disk;
	disk.center_x = pos_x;
	disk.center_y = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}
