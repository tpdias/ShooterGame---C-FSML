#include "Player.h"

void Player::initVariables()
{
	this->movmentSpeed = 5.f;
	this->hpMax = 10;
	this->hp = hpMax;
	this->level = 0;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setSize(sf::Vector2f(25.f, 25.f));
	this->shape.setPosition(
		400.f - this->shape.getGlobalBounds().width,
		300.f - this->shape.getGlobalBounds().height
	);
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
//Accessors
const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}
const float Player::getLvl()
{
	return this->level;
}
void Player::levelUp()
{
	this->hpMax += 1;
	this->movmentSpeed += 0.2f;
	this->level++;
}
//Functions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
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
	}/*
	//shooting
	float x = 0.f, y = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		y = -1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		y = +1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		x = -1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		x = +1.f;
	if (x != 0 || y != 0)
		this->shoot(sf::Vector2f(x, y));*/
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right	
	else if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom	
	else if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
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

