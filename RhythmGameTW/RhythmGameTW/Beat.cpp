/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
// Beat class

#include "Beat.h" //Include beat header file

// defining member functions of beat class

Beat::Beat() //default constructor
{
	//setting up circle (debug)
	circle.setFillColor(sf::Color::Magenta);
	circle.setRadius(30.0f);
	circle.setOrigin(30.0f, 30.0f);
	circle.setPosition(1090.0f, 300.0f);

	active = false;
}

void Beat::setPosition(int xPos, int yPos)  // set the position of the Beat on the screen
{
	circle.setPosition(xPos, yPos);
}

void Beat::spawn() //spawns beat on random line and sets it to be active
{
	sf::Vector2f pos(circle.getPosition());

	numberGen = (rand() % 5) + 1; //randomly generates number 1-5

	if (numberGen == 1) //spawns on line 1
	{
		pos.y = 300.0f;
		active = true;
		circle.setFillColor(sf::Color::Blue);
	}
	else if (numberGen == 2) //spawns on line 2
	{
		pos.y = 400.0f;
		active = true;
		circle.setFillColor(sf::Color::Green);
	}
	else if (numberGen == 3) //spawns on line 3
	{
		pos.y = 500.0f;
		active = true;
		circle.setFillColor(sf::Color::Red);
	}
	else if (numberGen == 4) //spawns on line 4
	{
		pos.y = 600.0f;
		active = true;
		circle.setFillColor(sf::Color::Yellow);
	}
	else //skips beat spawning
	{
		active = false;
	}

	circle.setPosition(pos);
}

void Beat::reset() //sets beat to be inactive and moves it back
{
	//moves beat back
	sf::Vector2f pos(circle.getPosition());
	pos.x = 1090.0f;
	circle.setPosition(pos);

	//sets active to false
	active = false;
}


float Beat::getXPosition() // returns beat x
{
	sf::Vector2f pos(circle.getPosition());
	return pos.x;
}

float Beat::getYPosition() // returns beat y
{
	sf::Vector2f pos(circle.getPosition());
	return pos.y;
}

sf::Vector2f Beat::getPosition() // returns beat x and y
{
	sf::Vector2f pos(circle.getPosition());
	return pos;
}

void Beat::move() //moves beat to the left and resets it when done
{
	//only moves if beat is active
	if (active == true)
	{
		sf::Vector2f pos(circle.getPosition());
		pos.x = pos.x - 5;
		circle.setPosition(pos);
		if (pos.x < -36)
		{
			reset();
		}

	}
}

sf::CircleShape Beat::getBody() // get the Beat's body (debug right now)
{
	return circle;
}
