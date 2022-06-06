#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"
#include "MeleeEnemies.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;
	
	//std::vector<SwagBall> swagBalls;
	//float spawnTimerMax;
	//float spawnTimer;
	//int maxSwagBalls;
	
	//Melee Enemies
	float spawnTimerMaxME;
	float spawnTimerME;	
	std::vector<MeleeEnemies> meleeEnemies;
	float maxME;

	//Ranged Enemies

	//Summoner Enemies
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();


public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers
	
	//Functions
	const bool running() const;
	void pollEvents();
	
	void spawnEnemies();
	//void spawnSwagBalls();
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();

};

