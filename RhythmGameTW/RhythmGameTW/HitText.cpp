/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Hit Text class

#include "HitText.h" //Include Hit Text header file

// defining member functions of Hit Text class

HitText::HitText() //default constructor
{
	setupSprite();
	active = false;
	transparencyCount = 255;
	upCount = 0;
	good = sf::IntRect(0, 0, 180, 76);
	great = sf::IntRect(0, 80, 180, 76);
	miss = sf::IntRect(0, 160, 180, 80);
}

sf::Sprite HitText::getBody() // returns sprite
{
	return sprite;
}

void HitText::setPosition(int xPos, int yPos) // sets position of sprite
{
	sprite.setPosition(xPos, yPos);
}

void HitText::setupSprite() // loads and sets sprite texture
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\ScoreSplashSpriteSheet.PNG"))
	{
		std::cout << "problem loading score sprite sheet";
	}
	sprite.setTexture(texture);

	//sprite.setTextureRect(sf::IntRect(0, 0, 180, 76));
	//sprite.setTextureRect(sf::IntRect(0, 80, 180, 76));
	//sprite.setTextureRect(sf::IntRect(0, 160, 180, 80));

}

void HitText::spawn(sf::Vector2f pos) // spawns sprite
{
	//checking x position to see what score it is
	//miss
	if (pos.x <= -35.0f)
	{
		sprite.setTextureRect(miss);
	}
	//good
	if (pos.x <= 100.0f && pos.x > 15.0f)
	{
		sprite.setTextureRect(good);
	}
	//great
	if (pos.x < 100.0f && pos.x > 40.0f)
	{
		sprite.setTextureRect(great);
	}

	active = true;
	sprite.setPosition(10, pos.y-30.0f);
}

void HitText::move() // moves sprite
{
	//only moves if hit text is active
	if (active == true)
	{
		sf::Vector2f pos(sprite.getPosition());
		pos.y = pos.y - 2;
		sprite.setPosition(pos);
		sprite.setColor({255, 255, 255, transparencyCount});
		if (upCount >= 45)
		{
			//resetting sprite
			active = false;
			transparencyCount = 255;
			upCount = 0;
			sprite.setPosition(65.0f, 700.0f);
		}
		transparencyCount = transparencyCount - 5;
		upCount++;
	}
}
