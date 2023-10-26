#include "game.h"
#include "graphics.h"
#include "bullet.h"

void Bullet::update()
{
	if (updateDirection == 1)
	{
		pos_y -= speed * graphics::getDeltaTime();
		if (pos_y < -size)
		{
			active = false;
		}
	}

	if (updateDirection == -1)
	{
		pos_y += speed * graphics::getDeltaTime();
		if (pos_y > WINDOW_HEIGHT)
		{
			active = false;
		}
	}
}

void Bullet::draw()
{

	if (updateDirection == 1)
	{
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
		graphics::Brush br;

		br.texture = "";
		br.fill_color[0] = 1.0f; //red
		br.fill_color[1] = 0.0f; //green
		br.fill_color[2] = 1.0f + glow * 0.5f; //blue
		br.fill_secondary_color[0] = 1.0f; //red
		br.fill_secondary_color[1] = 0.0f; //green
		br.fill_secondary_color[2] = 1.0f + glow * 0.5f; //blue
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = true;
		graphics::setScale(height, height);
		graphics::drawDisk((pos_x - 14 * height) + 7, pos_y - 48 * height, 18, br);
		graphics::resetPose();
	}

	if (updateDirection == -1)
	{
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
		graphics::Brush br;

		br.texture = "";
		br.fill_color[0] = 0.5f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f + glow * 0.5f;
		br.fill_secondary_color[0] = 1.0f;
		br.fill_secondary_color[1] = 1.0f;
		br.fill_secondary_color[2] = 1.0f + glow * 0.5f; 
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 1.0f;
		br.gradient = false;
		graphics::setScale(height, height);
		graphics::drawDisk((pos_x - 14 * height) + 7, pos_y - 48 * height, 18, br);
		graphics::resetPose();
	}
}

void Bullet::init()
{
	speed = 0.2f;
	size = 50;
	brush.outline_opacity = 0.0f;
}

Bullet::Bullet(const Game& mygame, float x, float y, int direction)
	:GameObject(mygame)
{
	updateDirection = direction;
	pos_y = y;
	pos_x = x;
	init();
}

Bullet::~Bullet()
{
}

Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.center_x = pos_x;
	disk.center_y = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}
