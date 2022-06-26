#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <ctime>

#include "Player.h"
#include "SwagBall.h"
#include "MeleeEnemies.h"
#include "Bullet.h"
#include "Experience.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Mouse mouse;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;
	bool levelUp;

	int points;

	//Timer
	clock_t start;
	int xp4NextLevel;
	int stage;

	//Fonts
	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	//Level Up
	sf::Text upgrade1;
	sf::Text upgrade2;
	sf::Text upgrade3;

	//Bullets 
	float attackSpeedMax;
	float attackSpeed;
	std::vector<Bullet> bullets;

	//Experience
	std::vector<Experience> experience;

	//Melee Enemies
	float spawnTimerMaxME;
	float spawnTimerME;	
	std::vector<MeleeEnemies> meleeEnemies;
	float maxME;

	//Ranged Enemies

	//Summoner Enemies

	//Initiators
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initLvlText();

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
	void shoot(Player player);
	void playerCollision();
	void enemyCollision();
	void bulletCollision();
	void xpCollision();
	

	//Setters
	void setTimerStart(int timeInSeconds);

	void spawnEnemies();
	void spawnXp(int index);
	void updatePlayer();
	
	//Game dificulty and playerXp
	void updateLevel();
	void updateLvlGui();
	void hideLvlGui();
	void updateCollision();
	void updateGui();
	void update();

	void renderLvlGui(sf::RenderTarget* target);
	void renderGui(sf::RenderTarget* target);
	void render();

	
};

