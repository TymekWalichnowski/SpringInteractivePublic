/// <summary>
/// @author Tymoteusz Walichnowski
/// @date Febraury-March 2024
/// </summary>

#include "Game.h"
#include <iostream>





/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 650U, 32U }, "Rhythm Game" },
	m_exitGame{false} //when true game will exit
{
	setupAssets(); //call in load functions for game assets
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible

	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}

		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Q == t_event.key.code) //beat hit for top line
	{
		//checking if key is held down so user isn't constantly "spamming" input
		if (keyHeld == false) 
		{
			checkCollisions(1);
			hitButtonArray[0].setActive();
		}
	}

	if (sf::Keyboard::W == t_event.key.code) //beat hit for top line
	{
		//checking if key is held down so user isn't constantly "spamming" input
		if (keyHeld == false)
		{
			checkCollisions(2);
			hitButtonArray[1].setActive();
		}
	}

	if (sf::Keyboard::O == t_event.key.code) //beat hit for top line
	{
		//checking if key is held down so user isn't constantly "spamming" input
		if (keyHeld == false)
		{
			checkCollisions(3);
			hitButtonArray[2].setActive();
		}
	}

	if (sf::Keyboard::P == t_event.key.code) //beat hit for top line
	{
		//checking if key is held down so user isn't constantly "spamming" input
		if (keyHeld == false)
		{
			checkCollisions(4);
			hitButtonArray[3].setActive();
		}
	}

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::Enter == t_event.key.code)
	{
		m_startGame = true;
		endScreen = false;
	}
}

void Game::processKeyReleases(sf::Event t_event)
{
	if (sf::Keyboard::Q == t_event.key.code)
	{
		keyHeld = false;
	}

	if (sf::Keyboard::W == t_event.key.code)
	{
		keyHeld = false;
	}

	if (sf::Keyboard::O == t_event.key.code)
	{
		keyHeld = false;
	}

	if (sf::Keyboard::P == t_event.key.code)
	{
		keyHeld = false;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	//game only updates if it has been started
	if (m_startGame == true)
	{
		//moving beat
		for (int index = 0; index < MAX_BEATS; index++)
		{

			beatArray[index].move();


			//missing beat
			if (beatArray[index].getXPosition() <= -35)
			{
				//spawns a new hit text on miss
				hitTextArray[hitTextArrayCount].spawn(beatArray[index].getPosition());
				hitTextArrayCount++;

				//resets combo count and heat mode, adds to missed hits
				comboCount = 0;
				tempoSpeed = 30;
				heatMultiplier = 1;
				heatMode = false;
				missHitCount++;
				tvObject.setEmotion(2);
				tvObject.sayDialogue(3);
			}

		}
		//moving hit text
		for (int index = 0; index < MAX_HIT_TEXT; index++)
		{
			hitTextArray[index].move();
		}

		//playing button animations
		for (int index = 0; index < MAX_HIT_BUTTON; index++)
		{
			hitButtonArray[index].playAnimation();
		}

		m_scoreMessage.setString("Score: " + std::to_string(scorePoints));
		m_comboMessage.setString("Combo: " + std::to_string(comboCount));
		tempoCounter++;

		//tempo, performs actions every half a second
		if (tempoCounter >= tempoSpeed)
		{
			//spawn new beat (stops spawning when song is nearing end)
			if (beatsSpawned < SONG_LENGTH - 20)
			{
				beatArray[beatArrayCount].spawn();
				beatArrayCount++;
			}
			
			m_drumHiHat.play();
			tempoCounter = 0;

			//counts how many beats have been spawned
			beatsSpawned++;
		}

		//resetting array counts if full
		if (beatArrayCount == MAX_BEATS)
		{
			beatArrayCount = 0;
		}
		if (hitTextArrayCount == MAX_HIT_TEXT)
		{
			hitTextArrayCount = 0;
		}

		//ends the game when song limit reached
		if (beatsSpawned == SONG_LENGTH)
		{
			m_startGame = false;
			endScreen = true;
			m_endResults.setString(" Song Over! \n Total Score: " + std::to_string(scorePoints) + "\n Great Hits: " + std::to_string(greatHitCount) + 
				"\n Good Hits: " + std::to_string(goodHitCount) + "\n Misses: " + std::to_string(missHitCount));
			tvObject.setEmotion(1);
			setupAssets();
		}
	}


	//tv updates
	tvUpdateCounter++;
	if (tvUpdateCounter >= 10)
	{
		tvObject.changeFrame(tvFrame);

		if (tvFrameCounter == 1)
		{
			tvFrame = 1;
		}
		else
		{
			tvFrame = 2;
			tvFrameCounter = 0;
		}
		tvFrameCounter++;
		tvUpdateCounter = 0;
	}
	//exiting game
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	//drawing background
	m_window.draw(m_backgroundSprite);

	//drawing gui
	m_window.draw(m_beatLine1);
	m_window.draw(m_beatLine2);
	m_window.draw(m_beatLine3);
	m_window.draw(m_beatLine4);

	//draw score messages
	m_window.draw(m_scoreMessage);
	m_window.draw(m_comboMessage);

	//draw heat mode overlay if it's on
	if (heatMode == true)
	{
		m_window.draw(m_heatModeOverlaySprite);
	}

	//drawing gameplay elements
	for (int index = 0; index < MAX_HIT_BUTTON; index++) //drawing hit Button array
	{
		m_window.draw(hitButtonArray[index].getBody());
	}

	for (int index = 0; index < MAX_BEATS; index++) //drawing beat array
	{
		m_window.draw(beatArray[index].getBody());
	}

	for (int index = 0; index < MAX_HIT_TEXT; index++) //drawing hit text array
	{
		m_window.draw(hitTextArray[index].getBody());
	}

	//draw start text and inactive overlay if game is not active
	if (m_startGame == false)
	{
		m_window.draw(m_inactiveOverlay);
		m_window.draw(m_startMessage);
	}

	//draw end results if game is over
	if (endScreen == true)
	{
		m_window.draw(m_endResults);
	}

	//drawing tv
	m_window.draw(tvObject.getBody());

	//drawing elements
	m_window.display();
}

/// <summary>
/// calls functions to set up and load assets within the game
/// </summary>
void Game::setupAssets()
{
	//loading and setting up background
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\Background1.PNG")) 
	{
		std::cout << "problem loading background";
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);

	//setting up 
	setupGameplay(); //sets up gameplay variables
	setupAudio(); //loading and setting up audio
	setupFontAndText(); // loading and setting up font
	setupGUI(); // loading and setting up GUI elements
	initializeBeatArray(); //sets up all beats to be used
	initializeHitTextArray(); //sets up all hit text to be used
	initializeHitButtonArray(); //sets up all hit buttons to be used
	tvObject.sayDialogue(1);
}

void Game::setupAudio()
{
	m_bufferDrumHiHat.loadFromFile("ASSETS\\SOUNDS\\DrumHiHat1.wav");
	m_drumHiHat.setBuffer(m_bufferDrumHiHat);

	m_bufferDrumHit.loadFromFile("ASSETS\\SOUNDS\\DrumHit1.wav");
	m_drumHit.setBuffer(m_bufferDrumHit);

	m_bufferDrumFat.loadFromFile("ASSETS\\SOUNDS\\DrumFat1.wav");
	m_drumFat.setBuffer(m_bufferDrumFat);

	m_bufferDrumCrash.loadFromFile("ASSETS\\SOUNDS\\DrumCrash1.wav");
	m_drumCrash.setBuffer(m_bufferDrumCrash);

	m_bufferDrumNobo.loadFromFile("ASSETS\\SOUNDS\\NoboDrum1.wav");
	m_drumNobo.setBuffer(m_bufferDrumNobo);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_scoreMessage.setFont(m_ArialBlackfont);
	m_scoreMessage.setString("Score: " + std::to_string(scorePoints));
	m_scoreMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_scoreMessage.setPosition(40.0f, 40.0f);
	m_scoreMessage.setCharacterSize(80U);
	m_scoreMessage.setOutlineColor(sf::Color::Red);
	m_scoreMessage.setFillColor(sf::Color::Black);
	m_scoreMessage.setOutlineThickness(3.0f);

	m_comboMessage.setFont(m_ArialBlackfont);
	m_comboMessage.setString("Combo: " + std::to_string(comboCount));
	m_comboMessage.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_comboMessage.setPosition(40.0f, 160.0f);
	m_comboMessage.setCharacterSize(50U);
	m_comboMessage.setOutlineColor(sf::Color::Red);
	m_comboMessage.setFillColor(sf::Color::Black);
	m_comboMessage.setOutlineThickness(3.0f);

	m_startMessage.setFont(m_ArialBlackfont);
	m_startMessage.setString("Press Enter to Start Game \n        or Esc to Exit!");
	m_startMessage.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_startMessage.setPosition(130.0f, 460.0f);
	m_startMessage.setCharacterSize(50U);
	m_startMessage.setOutlineColor(sf::Color::White);
	m_startMessage.setFillColor(sf::Color::Black);
	m_startMessage.setOutlineThickness(3.0f);


	m_endResults.setFont(m_ArialBlackfont);
	m_endResults.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_endResults.setPosition(30.0f, 30.0f);
	m_endResults.setCharacterSize(30U);
	m_endResults.setOutlineColor(sf::Color::White);
	m_endResults.setFillColor(sf::Color::Black);
	m_endResults.setOutlineThickness(3.0f);

}

void Game::setupGameplay()
{
	m_startGame = false;
	keyHeld = false;
	heatMode = false;
	tempoSpeed = 30;
	tempoCounter = 0;
	scorePoints = 0;
	comboCount = 0;
	beatsSpawned = 0;
	goodHitCount = 0;
	greatHitCount = 0;
	missHitCount = 0;
	heatMultiplier = 1;
	tvFrame = 1;
	tvFrameCounter = 0;
	tvUpdateCounter = 0;
}

/// <summary>
/// loads GUI elements of game
/// </summary>
void Game::setupGUI()
{
	//setting up beat lines
	m_beatLine1.setFillColor(sf::Color{205, 221, 226, 255});
	m_beatLine1.setSize(sf::Vector2f{1000.0f, 5.0f});
	m_beatLine1.setPosition(0.0f, 300.0f);

	m_beatLine2.setFillColor(sf::Color{200, 255, 213, 255});
	m_beatLine2.setSize(sf::Vector2f{ 1000.0f, 5.0f });
	m_beatLine2.setPosition(0.0f, 400.0f);

	m_beatLine3.setFillColor(sf::Color{228, 203, 203, 255});
	m_beatLine3.setSize(sf::Vector2f{ 1000.0f, 5.0f });
	m_beatLine3.setPosition(0.0f, 500.0f);

	m_beatLine4.setFillColor(sf::Color{245, 243, 204, 255});
	m_beatLine4.setSize(sf::Vector2f{ 1000.0f, 5.0f });
	m_beatLine4.setPosition(0.0f, 600.0f);

	//setting up heat mode overlay
	if (!m_heatModeOverlayTexture.loadFromFile("ASSETS\\IMAGES\\HeatModeOverlay2.PNG"))
	{
		std::cout << "problem loading heat mode overlay";
	}
	m_heatModeOverlaySprite.setTexture(m_heatModeOverlayTexture);

	//setting up inactive overlay
	m_inactiveOverlay.setSize(sf::Vector2f{1600.0f,650.0f});
	m_inactiveOverlay.setFillColor(sf::Color{0,0,0,200});
	m_inactiveOverlay.setPosition(0.0f, 0.0f);
}

/// <summary>
/// initializes beat array
/// </summary>
void Game::initializeBeatArray()
{
	for (int index = 0; index < MAX_BEATS; index++) //initializing beat array
	{
		beatArray[index].setPosition(1090.0f, 300.0f); //initalized off-screen
	}
}

/// <summary>
/// initializes hit text array
/// </summary>
void Game::initializeHitTextArray()
{
	for (int index = 0; index < MAX_HIT_TEXT; index++) //initializing beat array
	{
		hitTextArray[index].setPosition(65.0f, 700.0f); //initialized off-screen
	}
}

/// <summary>
/// initalizes hit button array
/// </summary>
void Game::initializeHitButtonArray()
{
	for (int index = 0; index < MAX_HIT_BUTTON; index++) //initializing beat array
	{
		hitButtonArray[index].setupButton(index); 
	}
}

void Game::checkCollisions(int t_line) //checks if beat is close to hit zone, scores points and resets if so
{
	for (int index = 0; index < MAX_BEATS; index++)
	{
		// checks if on line 1
		if (beatArray[index].getYPosition() == 300.0f && t_line == 1)
		{
			// good timing line 1
			if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 15.0f) 
			{
				scorePointsToAdd = 50;
				goodHitCount++;

				// great timing line 1
				if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 40.0f)
				{
					scorePointsToAdd = 100;
					goodHitCount--;
					greatHitCount++;

				}
				hitEvent(index);
				m_drumHit.play();
				beatArray[index].reset();
			}
		}

		// checks if on line 2
		else if (beatArray[index].getYPosition() == 400.0f && t_line == 2)
		{
			// good timing line 2
			if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 15.0f)
			{
				scorePointsToAdd = 50;
				goodHitCount++;

				// great timing line 2
				if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 40.0f)
				{
					scorePointsToAdd = 100;
					goodHitCount--;
					greatHitCount++;
				}
				hitEvent(index);
				m_drumFat.play();
				beatArray[index].reset();
			}
		}

		// checks if on line 3
		else if (beatArray[index].getYPosition() == 500.0f && t_line == 3)
		{
			// good timing line 3
			if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 15.0f)
			{
				scorePointsToAdd = 50;
				goodHitCount++;

				// great timing line 3
				if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 40.0f)
				{
					scorePointsToAdd = 100;
					goodHitCount--;
					greatHitCount++;
				}
				hitEvent(index);
				m_drumCrash.play();
				beatArray[index].reset();
			}
		}

		// checks if on line 4
		else if (beatArray[index].getYPosition() == 600.0f && t_line == 4)
		{
			// good timing line 4
			if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 15.0f)
			{
				scorePointsToAdd = 50;
				goodHitCount++;

				// great timing line 4
				if (beatArray[index].getXPosition() < 100.0f && beatArray[index].getXPosition() > 40.0f)
				{
					scorePointsToAdd = 100;
					goodHitCount--;
					greatHitCount++;
				}
				hitEvent(index);
				m_drumNobo.play();
				beatArray[index].reset();
			}
		}
	}

	keyHeld = true; //key will be held down until player releases
}

void Game::hitEvent(int index)
{
	//spawn hit text
	hitTextArray[hitTextArrayCount].spawn(beatArray[index].getPosition()); 
	hitTextArrayCount++;

	//adds to combo count and score
	comboCount++;

	//enabling heat mode if over threshold
	if (comboCount >= COMBO_LIMIT)
	{
		heatMode = true;
		heatMultiplier = 2;
		tempoSpeed = 20;
		tvObject.setEmotion(4);
		if (tvObject.getInterrupt() == true)
		{
			tvObject.sayDialogue(2);
		}
	}

	//setting tv emotion
	if (heatMode == false)
	{
		tvObject.setEmotion(3);
	}

	//calculating score
	scorePointsToAdd = scorePointsToAdd * heatMultiplier;
	scorePoints = scorePoints + scorePointsToAdd;
}
