/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Hit Button class

#include "HitButton.h" //Include Hit Button header file

// defining member functions of Hit Button class

HitButton::HitButton() //default constructor
{
	setupSprite();
	animationScale = 0.85f;
	gettingSmaller = false;
}

void HitButton::setupButton(int button) //sets up button sprite cropping and positon
{
	if (button == 0)
	{
		sprite.setTextureRect(sf::IntRect(0, 8, 120, 102));
		sprite.setPosition(65.0f, 300.0f);
	}

	else if (button == 1)
	{
		sprite.setTextureRect(sf::IntRect(0, 113, 120, 102));
		sprite.setPosition(65.0f, 400.0f);
	}

	else if (button == 2)
	{
		sprite.setTextureRect(sf::IntRect(0, 219, 120, 102));
		sprite.setPosition(65.0f, 500.0f);
	}

	else
	{
		sprite.setTextureRect(sf::IntRect(0, 328, 120, 102));
		sprite.setPosition(65.0f, 600.0f);
	}
}

void HitButton::setupSprite() //sets up sprite
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\HitButtons1.PNG"))
	{
		std::cout << "problem loading hit buttons";
	}

	sprite.setTexture(texture);
	sprite.setScale(0.85f, 0.85f);
	sprite.setOrigin(60.0f, 51.0f);
}

void HitButton::setActive()
{
	playingAnimation = true;
	gettingSmaller = true;
}

void HitButton::playAnimation() //plays hit animation to simulate impact
{
	if (playingAnimation == true)
	{
		if (gettingSmaller == true) //sprite being made smaller
		{
			animationScale = animationScale - 0.05;
		}

		else //sprite not being made smaller, therefore sprite being made bigger
		{
			animationScale = animationScale + 0.05;
		}

		if (animationScale <= 0.5f) //sprite has reached smallness threshold
		{
			gettingSmaller = false;
		}

		if (gettingSmaller == false && animationScale == 0.85f) //checking if back to normal
		{
			playingAnimation = false;
		}

		sprite.setScale(animationScale, animationScale); //scaling sprite
	}
}

sf::Sprite HitButton::getBody()
{
	return sprite;
}
