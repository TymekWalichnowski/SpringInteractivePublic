/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Hit Button class declaration
#pragma once



#include "SFML/Graphics.hpp" 

#include <iostream>

class HitButton
{
	// data members are private by default

	sf::Texture texture; // texture for Hit Text
	sf::Sprite sprite;   // sprite used to represent Hit Text

	float animationScale; // value used for hit animation scaling 
	bool gettingSmaller; // value used for hit animation
	bool playingAnimation; // value to say if animation is being played or not

public:	  // declaration of member functions	
	HitButton(); // default constructor
	void setupButton(int button);
	void setupSprite(); // loads sprite texture
	void setActive(); //sets the animation to play
	void playAnimation(); //plays hit animation


	sf::Sprite getBody(); // returns sprite
};