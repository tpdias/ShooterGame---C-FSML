#pragma once

#include "Player.h"
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
	int damage;

	void initMeleeEnemy(const sf::RenderWindow& window, Player player);

public:
	//Constructors
	MeleeEnemies(const sf::RenderWindow& window, Player player);
	virtual ~MeleeEnemies();
	//Accessors
	bool isAlive();
	int getHp();
	int getDamage();
	const sf::CircleShape getShape() const;

	//Functions
	void takeDamage();
	void explode();
	void collisionMove(sf::CircleShape secondEnemy);
	sf::Vector2f randomPosition(const sf::RenderWindow& window, Player player);
	sf::Vector2f enemyDirection(Player player);
	void update(Player player);
	void render(sf::RenderTarget& target);
};

