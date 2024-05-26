/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Hit Text class declaration
#pragma once


#include "SFML/Graphics.hpp" 

#include <iostream>

class HitText
{
	// data members are private by default

	sf::Texture texture; // texture for Hit Text
	sf::Sprite sprite;   // sprite used to represent Hit Text

	sf::IntRect good; //good SpriteSheet
	sf::IntRect great; //great SpriteSheet
	sf::IntRect miss; //miss SpriteSheet

	bool active; // bool for deciding if Hit Text should be moving or not
	int upCount; // int for setting up when a sprite should disappear
	sf::Uint8 transparencyCount; // int for slowly changing sprite transparency

public:	  // declaration of member functions	
	HitText(); // default constructor

	sf::Sprite getBody(); // returns sprite
	void setPosition(int xPos, int yPos); //sets sprite position
	void setupSprite(); // loads sprite texture
	void spawn(sf::Vector2f pos); // spawns sprite


	void move(); // moves sprite
};