#include "MeleeEnemies.h"
//Initializers
void MeleeEnemies::initMeleeEnemy(const sf::RenderWindow& window, sf::RectangleShape player)
{
	this->stage = 0; //depois arrumar a parte do stage

	this->shape.setRadius(10.f);
	this->hp = 5;
	this->movSpeed = 3.f;
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(randomPosition(window, player));
	this->spawned = true;

}

//Constructors/Destructors
MeleeEnemies::MeleeEnemies(const sf::RenderWindow& window, sf::RectangleShape player)
{
	this->initMeleeEnemy(window, player);
}

MeleeEnemies::~MeleeEnemies()
{

}

bool MeleeEnemies::isAlive()
{
	return this->spawned;
}

const sf::CircleShape MeleeEnemies::getShape() const
{
	return this->shape;
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

sf::Vector2f MeleeEnemies::randomPosition(const sf::RenderWindow& window, sf::RectangleShape player)
{
	float x = player.getPosition().x, y = player.getPosition().y, i = 0.f;
	while (x >= (player.getPosition().x - 200.f) && x <= (player.getPosition().x + 200.f)) 
		x = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	while (y >= (player.getPosition().y - 200.f) && y <= (player.getPosition().y + 200.f))
		y = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);
	return sf::Vector2f(x, y);
}


//Functions

sf::Vector2f MeleeEnemies::enemyDirection(sf::RectangleShape player)
{
	float x, y;
	if (this->shape.getPosition().x > player.getPosition().x)
		x = -(this->shape.getPosition().x - player.getPosition().x);
	else
		x = player.getPosition().x - this->shape.getPosition().x;
	if (this->shape.getPosition().y > player.getPosition().y)
		y = -(this->shape.getPosition().y - player.getPosition().y);
	else
		y = player.getPosition().y - this->shape.getPosition().y;

	while (sqrt(pow(x, 2) + pow(y, 2)) >= this->movSpeed)
	{
		x /= this->movSpeed;
		y /= this->movSpeed;
	}
	return sf::Vector2f(x, y);
}

void MeleeEnemies::update(sf::RectangleShape player)
{
	this->shape.move(enemyDirection(player));
}

void MeleeEnemies::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
