#include "Enemies.h"
//Initializers
void Enemies::initEnemy(const sf::RenderWindow& window)
{
	if (this->stage < 5)
	{
		this->shape.setRadius(15.f - (static_cast<float>(stage)) * 2);
		this->hp = 1 + stage;
	}
	else
	{
		this->shape.setRadius(10.f);
		this->hp = 5;
	}
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
	)
	);
}

//Constructors/Destructors
Enemies::Enemies(const sf::RenderWindow& window, int type)
	: type(type)
{
	this->stage = 0;
	this->initEnemy(window);
}

Enemies::~Enemies()
{

}

const sf::CircleShape Enemies::getShape() const
{
	return this->shape;
}

const int& Enemies::getType() const
{
	return this->type;
}

//Functions
void Enemies::update()
{
}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
