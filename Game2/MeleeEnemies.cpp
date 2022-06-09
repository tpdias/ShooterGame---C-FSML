#include "MeleeEnemies.h"


//Initializers
void MeleeEnemies::initMeleeEnemy(const sf::RenderWindow& window, Player player, int stage)
{
	this->shape.setRadius(10.f + stage);
	this->hp = 5 + stage;
	this->movSpeed = 3.f + stage/5;
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(randomPosition(window, player));
	this->damage = 1 + stage/5;
}

//Constructors/Destructors
MeleeEnemies::MeleeEnemies(const sf::RenderWindow& window, Player player, int stage)
{
	this->initMeleeEnemy(window, player, stage);
}

MeleeEnemies::~MeleeEnemies()
{

}


int MeleeEnemies::getHp()
{
	return this->hp;
}

int MeleeEnemies::getDamage()
{
	return this->damage;
}

const sf::CircleShape MeleeEnemies::getShape() const
{
	return this->shape;
}


void MeleeEnemies::takeDamage()
{
	this->hp--;
}

void MeleeEnemies::explode()
{
	//Explode animation, particles all around
}

void MeleeEnemies::collisionMove(sf::CircleShape secondEnemy)
{
	if ((this->shape.getPosition().x - secondEnemy.getPosition().x) >= 0)
	{
		if ((this->shape.getPosition().y - secondEnemy.getPosition().y) >= 0)
		{
			this->shape.move(2.f, 2.f);
			secondEnemy.move(-2.f, -2.f);
		}
		else {
			this->shape.move(2.f, -2.f);
			secondEnemy.move(-2.f, 2.f);
		}
	}
	else {
		if ((this->shape.getPosition().y - secondEnemy.getPosition().y) >= 0)
		{
			this->shape.move(-2.f, 2.f);
			secondEnemy.move(2.f, -2.f);
		}
		else {
			this->shape.move(-2.f, -2.f);
			secondEnemy.move(2.f, 2.f);
		}
	}
}

sf::Vector2f MeleeEnemies::randomPosition(const sf::RenderWindow& window, Player player)
{
	float x = player.getShape().getPosition().x, y = player.getShape().getPosition().y, i = 0.f;
	while (x >= (player.getShape().getPosition().x - 200.f) && x <= (player.getShape().getPosition().x + 200.f))
		x = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	while (y >= (player.getShape().getPosition().y - 200.f) && y <= (player.getShape().getPosition().y + 200.f))
		y = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);
	return sf::Vector2f(x, y);
}


//Functions

sf::Vector2f MeleeEnemies::enemyDirection(Player player)
{
	sf::Vector2f direction, enemyPos, playerPos; 
	float x, y;
	playerPos = sf::Vector2f(player.getShape().getPosition().x + player.getShape().getGlobalBounds().width, player.getShape().getPosition().y + player.getShape().getGlobalBounds().width);
	enemyPos = sf::Vector2f(this->shape.getPosition());
	direction = playerPos - enemyPos;
	x = direction.x / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	y = direction.y / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	return sf::Vector2f(x, y);
}

void MeleeEnemies::update(Player player)
{
	this->shape.move(enemyDirection(player));
}

void MeleeEnemies::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
