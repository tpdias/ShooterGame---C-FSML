#pragma once

#include "Player.h"
#include "Enemy.h"
#include <math.h>
#include <iostream>


class MeleeEnemies : public Enemy
{
private:
	sf::CircleShape shape;
	int hp;
	float movSpeed;
	int damage;

	void initMeleeEnemy(const sf::RenderWindow& window, Player player, int stage);

public:
	//Constructors
	MeleeEnemies(const sf::RenderWindow& window, Player player, int stage);
	virtual ~MeleeEnemies();
	//Accessors
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

