#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>

enum EnemiesType { Melee, Ranged };

class Enemies
{
private:
	sf::CircleShape shape;
	int type;
	int stage;
	int hp;

	void initEnemy(const sf::RenderWindow& window);

public:
	//Constructors
	Enemies(const sf::RenderWindow& window, int type);
	virtual ~Enemies();
	//Accessors
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

