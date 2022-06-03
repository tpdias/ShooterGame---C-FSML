#include "Player.h"

void Player::initVariables()
{
	this->movmentSpeed = 10.f;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movmentSpeed, 0.f);
	}
	//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movmentSpeed, 0.f);
	}
	//Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movmentSpeed);
	}
	//Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movmentSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Position of the player
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	//Left
	if (playerBounds.left <= 0.f)
		this->shape.setPosition(0.f, playerBounds.top);
	//Right	
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	//Top
	if (playerBounds.top <= 0.f)
		this->shape.setPosition(playerBounds.left, 0.f);
	//Bottom	
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();
	
	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
