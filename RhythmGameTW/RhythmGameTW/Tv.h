/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>#pragma once
/// // Tv class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <SFML/Audio.hpp>

#include <iostream>


class Tv
{
	// data members are private by default

	sf::Texture texture; // texture for Hit Text
	sf::Sprite sprite;   // sprite used to represent Hit Text

	//buffer for tv noises
	sf::SoundBuffer tvBufferGreetings; 
	sf::SoundBuffer tvBufferHappy;
	sf::SoundBuffer tvBufferSad;

	//tv sounds for talking to player
	sf::Sound tvTalk; 
	
	//deciding what row/emotion of the sprite sheet to focus on
	int currentRow;

	bool playingAnimation; // value to say if animation is being played or not
	bool allowInterrupt; // value to check if allowed to interrupt dialogue or not

public:	  // declaration of member functions	
	Tv(); // default constructor
	void setPosition(int xPos, int yPos); //sets sprite position
	void setupSprite(); // loads sprite texture
	void setupAudio(); // loads audio
	void changeFrame(int t_frame); //changes from frame 1 to 2
	void setEmotion(int t_emotion); //sets the emotion to be displayed on the tv animation
	void sayDialogue(int t_dialogue); //says current dialogue oassed onto it

	bool getInterrupt(); //returns whether can interrupt or not
	sf::Sprite getBody(); // returns sprite
};