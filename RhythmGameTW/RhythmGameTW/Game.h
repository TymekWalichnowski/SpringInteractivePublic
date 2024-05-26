/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include "Beat.h"   // include Beat header file
#include "HitButton.h"   // include Hit Button header file
#include "HitText.h"   // include Hit Text header file
#include "Tv.h" // include Tv header file

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Game
{


public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	//data members
	Tv tvObject;

	// beat array
	static const int MAX_BEATS = 20;
	Beat beatArray[MAX_BEATS];
	int beatArrayCount = 0;

	// hit button array
	static const int MAX_HIT_BUTTON = 4;
	HitButton hitButtonArray[MAX_HIT_BUTTON];

	// hit text array
	static const int MAX_HIT_TEXT = 6;
	HitText hitTextArray[MAX_HIT_TEXT];
	int hitTextArrayCount = 0;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupAssets();
	void setupAudio();
	void setupFontAndText();
	void setupGameplay();
	void setupGUI();
	void initializeBeatArray();
	void initializeHitTextArray();
	void initializeHitButtonArray();

	//check collisions 
	void checkCollisions(int line);
	void hitEvent(int index);

	//variables
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	bool m_startGame; //control starting game
	bool m_exitGame; // control exiting game

	bool keyHeld; // bool for checking key press

	//sound
	sf::SoundBuffer m_bufferDrumHiHat;
	sf::Sound m_drumHiHat;

	sf::SoundBuffer m_bufferDrumHit;
	sf::Sound m_drumHit;

	sf::SoundBuffer m_bufferDrumFat;
	sf::Sound m_drumFat;

	sf::SoundBuffer m_bufferDrumCrash;
	sf::Sound m_drumCrash;

	sf::SoundBuffer m_bufferDrumNobo;
	sf::Sound m_drumNobo;

	//song length (how many beats are in the level)
	const int SONG_LENGTH = 160;
	int beatsSpawned;
	bool endScreen; // is it the end screen (with results)?

	//tempo
	//tempo should be roughly 120bpm, higher when in heat mode
	int tempoCounter;
	int tempoSpeed;

	//score
	const int COMBO_LIMIT = 10;
	int comboCount;

	int scorePoints;
	int scorePointsToAdd;
	int heatMultiplier;

	bool heatMode;

	//counters for good/great/missed hits
	int goodHitCount;
	int greatHitCount;
	int missHitCount;

	//background 
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	//heat mode overlay
	sf::Texture m_heatModeOverlayTexture;
	sf::Sprite m_heatModeOverlaySprite;

	sf::Text m_scoreMessage; // text used for score message on screen
	sf::Text m_comboMessage; // text used for score message on screen

	sf::Text m_startMessage; // text used for starting game
	sf::Text m_endResults; // text used for showing end stats

	//beat lines
	sf::RectangleShape m_beatLine1;
	sf::RectangleShape m_beatLine2;
	sf::RectangleShape m_beatLine3;
	sf::RectangleShape m_beatLine4;

	//inactive overlay
	sf::RectangleShape m_inactiveOverlay;

	//tv frame, what frame the tv is on
	int tvFrame;
	int tvFrameCounter; //controls when to alternate tv frames
	int tvUpdateCounter; //controls how long a tv frame is
};

#endif // !GAME_HPP

