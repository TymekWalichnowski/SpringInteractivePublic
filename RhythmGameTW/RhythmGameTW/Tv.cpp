/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Tv class

#include "Tv.h" //Include Tv header file

// defining member functions of Tv class

Tv::Tv() //default constructor
{
	setupSprite();
	sprite.setPosition(700.0f, -35.0f);
	setupAudio();
	playingAnimation = true;
	allowInterrupt = true;
	currentRow = 0;
}

void Tv::setPosition(int xPos, int yPos)
{
}

/// <summary>
/// sets up tv sprite
/// </summary>
void Tv::setupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\tvSpriteSheet1.PNG"))
	{
		std::cout << "problem loading tv sprite sheet";
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 300, 300));

}

/// <summary>
/// sets up tv audio
/// </summary>
void Tv::setupAudio()
{
	tvBufferGreetings.loadFromFile("ASSETS\\SOUNDS\\TymekGreetings.wav");
	tvBufferHappy.loadFromFile("ASSETS\\SOUNDS\\TymekHappy.wav");
	tvBufferSad.loadFromFile("ASSETS\\SOUNDS\\TymekSad.wav");
}

/// <summary>
/// changes current frame of tv
/// </summary>
/// <param name="t_frame"></param>
void Tv::changeFrame(int t_frame)
{
	if (playingAnimation == true)
	{
		if (t_frame == 1)
		{
			sprite.setTextureRect(sf::IntRect(0, currentRow, 300, 300));
		}

		else if (t_frame == 2)
		{
			sprite.setTextureRect(sf::IntRect(300, currentRow, 300, 300));
		}
	}

}

//changes emotion on tv
void Tv::setEmotion(int t_emotion)
{
	if (t_emotion == 1) //neutral
	{
		currentRow = 0;
		playingAnimation = true;
	}
	else if (t_emotion == 2) //sad
	{
		currentRow = 300;
		playingAnimation = true;

	}

	else if (t_emotion == 3) //shock
	{
		currentRow = 600;
		sprite.setTextureRect(sf::IntRect(0, currentRow, 300, 300));
		playingAnimation = false;

	}

	else if (t_emotion == 4) //joy
	{
		currentRow = 900;
		playingAnimation = true;
	}

}

/// <summary>
/// plays dialogue
/// </summary>
/// <param name="t_dialogue"></param>
void Tv::sayDialogue(int t_dialogue)
{
	if (t_dialogue == 1) //greetings  
	{
		tvTalk.setBuffer(tvBufferGreetings);
		tvTalk.play();

	}
	else if (t_dialogue == 2) //happy
	{
		tvTalk.setBuffer(tvBufferHappy);
		tvTalk.play();
		allowInterrupt = false;
	}
	else if (t_dialogue == 3) //sad
	{
		tvTalk.setBuffer(tvBufferSad);
		tvTalk.play();
		allowInterrupt = true;
	}
}

//returns allow interrupt bool
bool Tv::getInterrupt()
{
	return allowInterrupt;
}

//returns sprite body
sf::Sprite Tv::getBody()
{
	return sprite;
}
