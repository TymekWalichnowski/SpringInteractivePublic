/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Beat class declaration
#pragma once

#include "SFML/Graphics.hpp" 



#include <iostream>

class Beat
{
	// data members are private by default

	sf::CircleShape circle; //beat graphics (debug)

	sf::Texture texture; // texture for Beat
	sf::Sprite sprite;   // sprite used to represent Beat

	bool active; // bool for deciding if beat should be moving or not
	
	int numberGen = rand(); // random number generator for deciding what line beat goes on

	public:	  // declaration of member functions	
		Beat(); // default constructor

		sf::CircleShape getBody(); // returns circle
		void setPosition(int xPos, int yPos); //sets beat position
		
		void spawn(); // spawns beat
		void reset(); // resets beat

		float getXPosition(); // returns x position of beat
		float getYPosition(); // returns y position of beat
		sf::Vector2f getPosition(); //returns x and y vector of beat

		void move(); // moves beat to the left
};