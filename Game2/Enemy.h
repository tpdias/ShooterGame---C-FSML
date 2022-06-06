#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
	sf::CircleShape shape;
	int stage;
	int hp;
	float movSpeed;
	void initMeleeEnemy();
public:
	//Constructors
	Enemy();
	virtual ~Enemy();
};

