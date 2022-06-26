#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Experience
{
private:
	int value;
	sf::CircleShape shape;
	void initExperience(const sf::RenderWindow& window, int value, sf::Vector2f pos);
public:
	//Constructors
	Experience(const sf::RenderWindow& window, int value, sf::Vector2f pos);
	virtual ~Experience();
	//Accessors
	int getValue();
	const sf::CircleShape& getShape() const;
	//Render
	void render(sf::RenderTarget& target);
};

