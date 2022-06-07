#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

class Bullet
{
private:
	sf::Vector2f getDirection(Player player, sf::RenderWindow& window, sf::Mouse mouse);
public:
	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

	//Constructor
	Bullet(Player player, sf::RenderWindow& window, sf::Mouse mouse, float radius = 3.f)
		: currVelocity(0.f, 0.f), maxSpeed(5.f)
	{
		this->shape.setPosition(player.getShape().getPosition());
		this->currVelocity = this->getDirection(player, window, mouse) * this->maxSpeed;
		this->shape.setRadius(radius);
		this->shape.setFillColor(sf::Color::Magenta);
	}
	//Accessors
	const sf::CircleShape& getShape() const;
	//Functions
	void updateBullet();
	void renderBullet(sf::RenderTarget* target);
};
