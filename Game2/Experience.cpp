#include "Experience.h"

Experience::Experience(const sf::RenderWindow& window, int value, sf::Vector2f pos)
{
	this->initExperience(window, value, pos);
}

void Experience::initExperience(const sf::RenderWindow& window, int value, sf::Vector2f pos)
{
	this->value = value;
	this->shape.setRadius(3.f);
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setPosition(pos);
}
Experience::~Experience()
{
}

int Experience::getValue()
{
	return this->value;
}

const sf::CircleShape& Experience::getShape() const
{
	return this->shape;
}

void Experience::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}