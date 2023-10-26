#include "pilar.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"



void Pilar::update()
{
	if (life == 0)
	{
		active = false;
	}
}

void Pilar::draw()
{
	if (life >= 3)
	{
		brush.texture = std::string(ASSET_PATH) + "ball 1.png";

	}
	if (life == 2)
	{
		brush.texture = std::string(ASSET_PATH) + "ball 2.png";
	}
	if (life == 1)
	{
		brush.texture = std::string(ASSET_PATH) + "ball 3.png";
	}
	brush.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();
}

void Pilar::init()
{
	size = 75.0f;
	pos_y = 360.0f;
	brush.outline_opacity = 0.0f;
}

Pilar::Pilar(const Game& mygame, float x)
	:GameObject(mygame)
{
	pos_x = x;
	init();
}

Pilar::~Pilar()
{
}

Disk Pilar::getCollisionHull() const
{
	Disk disk;
	disk.center_x = pos_x;
	disk.center_y = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}
