#pragma once

#include "Enemy.h"
#include <math.h>
#include <iostream>

class MeleeEnemies : public Enemy
{
private:
	sf::CircleShape shape;
	int stage;
	int hp;
	float movSpeed;
	bool spawned;

	void initMeleeEnemy(const sf::RenderWindow& window, sf::RectangleShape player);

public:
	//Constructors
	MeleeEnemies(const sf::RenderWindow& window, sf::RectangleShape player);
	virtual ~MeleeEnemies();
	//Accessors
	bool isAlive();
	const sf::CircleShape getShape() const;

	//Functions
	void explode();
	void collisionMove(sf::CircleShape secondEnemy);
	sf::Vector2f randomPosition(const sf::RenderWindow& window, sf::RectangleShape player);
	sf::Vector2f enemyDirection(sf::RectangleShape player);
	void update(sf::RectangleShape player);
	void render(sf::RenderTarget& target);
};

