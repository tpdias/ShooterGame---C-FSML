#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;

	//Swag balls
	/*
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	*/
	//Melee enemies
	this->spawnTimerMaxME = 30.f;
	this->spawnTimerME = this->spawnTimerMaxME;
	this->maxME = 10;
	//Bullets
	this->attackSpeedMax = 100.f;
	this->attackSpeed = this->attackSpeedMax;

	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Poppins-Regular.ttf"))
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD Poppins-Regular.ttf" << "\n";
}

void Game::initText()
{
	//Gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(16);
	this->guiText.setString("");

	//End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(40);
	this->endGameText.setPosition(sf::Vector2f(20, 300));
	this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}


//Functions
const bool Game::running() const
{
	return this->window->isOpen() /*&& this->endGame == false*/;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
	if (mouse.isButtonPressed(mouse.Left))
	{
		this->shoot(player);
	}
	else
		this->attackSpeed += 1.f;
}


void Game::spawnEnemies()
{
	//Timer
	if (this->spawnTimerME < this->spawnTimerMaxME)
		this->spawnTimerME += 1.f;
	else
	{
		if (this->meleeEnemies.size() < this->maxME)
		{
			this->meleeEnemies.push_back(MeleeEnemies(*this->window, this->player.getShape()));
			this->spawnTimerME = 0.f;
		}
	}
}
/*
void Game::spawnSwagBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue < 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;
	else
		type = SwagBallTypes::DEFAULT;
	return type;
}
*/
void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	//Check the collision with the player
	for (size_t i = 0; i < this->meleeEnemies.size(); i ++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->meleeEnemies[i].getShape().getGlobalBounds()))
		{
			this->player.takeDamage(1);
	
			//Remove the ball
			this->meleeEnemies[i].explode();
			this->meleeEnemies.erase(this->meleeEnemies.begin() + i);
		}
		//Check the collision with the Enemies
		for (int j = 0; j < this->meleeEnemies.size(); j++)
		{
			if ((this->meleeEnemies[i].getShape().getGlobalBounds().intersects(this->meleeEnemies[j].getShape().getGlobalBounds())) && (i != j))
			{
				this->meleeEnemies[i].collisionMove(this->meleeEnemies[j].getShape());
			}
		}
	}
	
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "- Points: " << this->points << "\n"
		<< "- Health: " << this->player.getHp() << "/" << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		
		//this->spawnSwagBalls();
		this->spawnEnemies();
		for (size_t i = 0; i < this->meleeEnemies.size(); i++)
		{
			if(meleeEnemies[i].isAlive())  // Pq fiz isso????
				meleeEnemies[i].update(player.getShape());
		}
		for (size_t i = 0; i < this->bullets.size(); i++)
		{
			if(bullets[i].getShape().getPosition().x > this->window->getSize().x ||
				bullets[i].getShape().getPosition().x < 0 ||
				bullets[i].getShape().getPosition().y > this->window->getSize().y ||
				bullets[i].getShape().getPosition().y < 0)
				this->bullets.erase(this->bullets.begin() + i);
			else
				bullets[i].updateBullet();
		}
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//Render
	this->player.render(this->window);
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].renderBullet(this->window);
	}
	/*
	for (auto i : this->swagBalls)
	{
		i.render(*this->window);
	}*/
	for (auto i : this->meleeEnemies)
	{
		i.render(*this->window);
	}
	//Render gui
	this->renderGui(this->window);
	//Render end text
	if (this->endGame)
		this->window->draw(this->endGameText);
	this->window->display();
}

void Game::shoot(Player player)
{
	//Timer
	if (this->attackSpeed < this->attackSpeedMax)
		this->attackSpeed += 1.f;
	else
	{
		this->bullets.push_back(Bullet(player, *this->window, this->mouse));
		this->attackSpeed = 0.f;
	}
}
