#include "MeleeEnemies.h"
//Initializers
void MeleeEnemies::initMeleeEnemy(const sf::RenderWindow& window, sf::RectangleShape player)
{
	if (this->stage < 5)
	{
		this->shape.setRadius(15.f - (static_cast<float>(stage)) * 2);
		this->hp = 1;
	}
	else
	{
		this->shape.setRadius(10.f);
		this->hp = 5;
		this->movSpeed = 3.f;
	}
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(randomPosition(window, player));
	/*
	* Old random generator
	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
	)
	);
	*/
}

//Constructors/Destructors
MeleeEnemies::MeleeEnemies(const sf::RenderWindow& window, sf::RectangleShape player)
{
	this->stage = 0;
	this->initMeleeEnemy(window, player);
}

MeleeEnemies::~MeleeEnemies()
{

}

const sf::CircleShape MeleeEnemies::getShape() const
{
	return this->shape;
}

const int& MeleeEnemies::getType() const
{
	return this->type;
}

sf::Vector2f MeleeEnemies::randomPosition(const sf::RenderWindow& window, sf::RectangleShape player)
{
	float x = player.getPosition().x, y = player.getPosition().y, i = 0.f;
	while (x >= (player.getPosition().x - 50.f) && x <= (player.getPosition().x + 50.f)) 
		x = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
	while (y >= (player.getPosition().y - 50.f) && y <= (player.getPosition().y + 50.f))
		y = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);
	return sf::Vector2f(x, y);
}

//Functions
void MeleeEnemies::update()
{
}

void MeleeEnemies::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
