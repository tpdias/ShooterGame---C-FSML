#include "Bullet.h"


sf::Vector2f Bullet::getDirection(Player player, sf::RenderWindow& window, sf::Mouse mouse)
{
	sf::Vector2f playerCenter, mousePosWindow, aimDir;
	float x, y;
	playerCenter = sf::Vector2f(
		player.getShape().getPosition().x + player.getShape().getGlobalBounds().width,
		player.getShape().getPosition().y + player.getShape().getGlobalBounds().width
	);
	mousePosWindow = sf::Vector2f(mouse.getPosition(window));
	aimDir = mousePosWindow - playerCenter;
	x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	return sf::Vector2f(x, y);
}

void Bullet::updateBullet()
{
	this->shape.move(this->currVelocity);
}

void Bullet::renderBullet(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

const sf::CircleShape& Bullet::getShape() const
{
	return this->shape;
}
