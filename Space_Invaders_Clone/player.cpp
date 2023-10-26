#include "player.h"
#include "graphics.h"
#include "game.h"

 


Player::Player(const Game& mygame)
	: GameObject(mygame)
{
}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime()/10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}

	


	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;

}

void Player::draw()
{

	if (alive > 3)
	{
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

		graphics::Brush br;
		br.outline_opacity = 0.0f;

		

		br.fill_opacity = 1.0f;
		br.texture = std::string(ASSET_PATH) + "ship.png";
		graphics::drawRect(pos_x, pos_y, 80, 80, br);
		graphics::resetPose();

		//left blast 
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f + glow * 0.5f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.3f;
		br.fill_secondary_color[1] = 0.1f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = true;
		graphics::setScale(height, height);
		graphics::drawDisk(pos_x - 14 * height, pos_y + 48 * height, 18, br);
		graphics::resetPose();

		//right blast
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f + glow * 0.5f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.3f;
		br.fill_secondary_color[1] = 0.1f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = true;
		graphics::setScale(height, height);
		graphics::drawDisk(pos_x + 14 * height, pos_y + 48 * height, 18, br);
		graphics::resetPose();
	}
	if (alive <= 3 && alive > 1)
	{
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

		graphics::Brush br;
		br.outline_opacity = 0.0f;


		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.3f;
		br.fill_secondary_color[1] = 0.1f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = false;
		graphics::setScale(height, height);
		graphics::drawDisk(pos_x, pos_y, height, br);
		graphics::resetPose();


		

		br.fill_opacity = 1.0f;
		br.texture = std::string(ASSET_PATH) + "ship.png";
		graphics::drawRect(pos_x, pos_y, 80, 80, br);
		graphics::resetPose();			

		//left blast 
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f + glow * 0.5f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.3f;
		br.fill_secondary_color[1] = 0.1f;
		br.fill_secondary_color[2] = 0.0f; 
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = true;
		graphics::setScale(height, height);
		graphics::drawDisk(pos_x - 14 * height, pos_y + 48 * height, 18, br);
		graphics::resetPose();
	}
	if (alive == 1)
	{
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

		graphics::Brush br;
		br.outline_opacity = 0.0f;


		br.texture = "";
		br.fill_color[0] = 1.0f; //red
		br.fill_color[1] = 0.5f; //green
		br.fill_color[2] = 0.0f; //blue
		br.fill_secondary_color[0] = 0.3f; //red
		br.fill_secondary_color[1] = 0.1f; //green
		br.fill_secondary_color[2] = 0.0f; //blue
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = false;
		graphics::setScale(height, height);
		graphics::drawDisk(pos_x, pos_y, height, br);
		graphics::resetPose();



		br.fill_opacity = 1.0f;
		br.texture = std::string(ASSET_PATH) + "ship.png";
		graphics::drawRect(pos_x, pos_y, 80, 80, br);
		graphics::resetPose();

		
	}

	

}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.center_x = pos_x;
	disk.center_y = pos_y;
	disk.radius = 45.0f;
	return disk;
}
