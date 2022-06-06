#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>



class MeleeEnemies
{
private:
	sf::CircleShape shape;
	int type;
	int stage;
	int hp;
	float movSpeed;

	void initMeleeEnemy(const sf::RenderWindow& window, sf::RectangleShape player);

public:
	//Constructors
	MeleeEnemies(const sf::RenderWindow& window, sf::RectangleShape player);
	virtual ~MeleeEnemies();
	//Accessors
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	sf::Vector2f randomPosition(const sf::RenderWindow& window, sf::RectangleShape player);
	void update();
	void render(sf::RenderTarget& target);
};

