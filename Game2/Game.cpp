#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;

	//Melee enemies
	this->spawnTimerMaxME = 30.f;
	this->spawnTimerME = this->spawnTimerMaxME;
	this->maxME = 10;
	//Bullets
	this->attackSpeedMax = 10.f;
	this->attackSpeed = this->attackSpeedMax;

	this->levelUp = false;

	this->points = 0;

	//Setando o timer de aumento de n�vel 1 min
	this->xp4NextLevel = 60000;
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

void Game::initLvlText()
{
	//Gui text lvl up init
	this->upgrade1.setFont(this->font);
	this->upgrade1.setFillColor(sf::Color::Blue);
	this->upgrade1.setCharacterSize(16);
	this->upgrade1.setPosition(sf::Vector2f(this->window->getSize().x / 3, this->window->getSize().y/4));
	this->upgrade1.setString("aaa");

	this->upgrade2.setFont(this->font);
	this->upgrade2.setFillColor(sf::Color::Cyan);
	this->upgrade2.setPosition(sf::Vector2f(this->window->getSize().x / 3, 2 * this->window->getSize().y / 4));
	this->upgrade2.setCharacterSize(16);
	this->upgrade2.setString("bbb");

	this->upgrade3.setFont(this->font);
	this->upgrade3.setFillColor(sf::Color::Green);
	this->upgrade3.setPosition(sf::Vector2f(this->window->getSize().x / 3, 3 * this->window->getSize().y / 4));
	this->upgrade3.setCharacterSize(16);
	this->upgrade3.setString("ccc");
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initLvlText();
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

void Game::setTimerStart(int timeInSeconds)
{
	this->start = timeInSeconds;
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
			this->meleeEnemies.push_back(MeleeEnemies(*this->window, this->player, this->stage));
			this->spawnTimerME = 0.f;
		}
	}
}

void Game::spawnXp(int index)
{
	int posX = this->meleeEnemies[index].getShape().getPosition().x + this->meleeEnemies[index].getShape().getRadius();
	int posY = this->meleeEnemies[index].getShape().getPosition().y + this->meleeEnemies[index].getShape().getRadius();
	sf::Vector2f position(posX, posY);
	this->experience.push_back(Experience(*this->window, this->stage, position));
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}


void Game::updateLevel()
{
	//this->player.gainHealth(this->player.getHpMax());
	//this->player.levelUp();	
}

void Game::updateCollision()
{
	playerCollision();
	
	enemyCollision();
	
	bulletCollision();
	
	xpCollision();
}

void Game::xpCollision()
{
	for (size_t i = 0; i < this->experience.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->experience[i].getShape().getGlobalBounds()))
		{
			this->points++;
			if (this->points % 2 == 0)
				//this->updateLevel();  --- change later
				this->levelUp = true;
			this->experience.erase(this->experience.begin() + i);
		}
	}
}

void Game::playerCollision() 
{
	//Check the collision with the player
	for (size_t i = 0; i < this->meleeEnemies.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->meleeEnemies[i].getShape().getGlobalBounds()))
		{
			this->player.takeDamage(this->meleeEnemies[i].getDamage());

			//Remove the ball
			this->meleeEnemies[i].explode();
			this->meleeEnemies.erase(this->meleeEnemies.begin() + i);
		}
	}
}

void Game::enemyCollision()
{
	//Check the collision Enemies with the Enemies
	for (size_t i = 0; i < this->meleeEnemies.size(); i++)
	{
		//Check the collision Enemies with the Enemies
		for (int j = 0; j < this->meleeEnemies.size(); j++)
		{
			if ((this->meleeEnemies[i].getShape().getGlobalBounds().intersects(this->meleeEnemies[j].getShape().getGlobalBounds())) && (i != j))
			{
				this->meleeEnemies[i].collisionMove(this->meleeEnemies[j].getShape());
			}
		}
	}
}

void Game::bulletCollision()
{
	//Check the collision bullets with the enemies
	for (size_t i = 0; i < this->meleeEnemies.size(); i++)
	{
		for (size_t j = 0; j < this->bullets.size(); j++)
		{
			if (this->bullets[j].getShape().getGlobalBounds().intersects(this->meleeEnemies[i].getShape().getGlobalBounds()))
			{
				//Collision = enemie loses hp and player gets points
				this->meleeEnemies[i].takeDamage();
				if (this->meleeEnemies[i].getHp() <= 0)
				{
					//Drops XP and gives points
					this->spawnXp(i);

					//Remove the enemie
					this->meleeEnemies[i].explode();
					this->meleeEnemies.erase(this->meleeEnemies.begin() + i);

					//Remove the bullet
					this->bullets.erase(this->bullets.begin() + j);
				}
			}
		}
	}
}
void Game::updateGui()
{
	std::stringstream ss;

	ss << "- Points: " << this->points << "\n"
		<< "- Health: " << this->player.getHp() << "/" << this->player.getHpMax() << "\n"
		<< "- Time: " << static_cast<int>((clock() - this->start)/1000) << " s\n";

	this->guiText.setString(ss.str());
}

void Game::updateLvlGui()
{
	std::stringstream ss;

	ss << "Increase X in Y% \n";

	this->upgrade1.setString(ss.str());
	this->upgrade2.setString(ss.str());
	this->upgrade3.setString(ss.str());
}

void Game::update()
{
	//Timer - increases stage after 60s
	if (clock() - this->start > xp4NextLevel) {
		stage++;
		maxME *= 2;
	}

	this->pollEvents();

	if (this->endGame == false)
	{
		if (this->levelUp)
		{	
			//Precisa parar o timer depois
			this->updateLvlGui();
			//Enqnto n�o escolhe 
			if (mouse.isButtonPressed(mouse.Left))
			{
				this->hideLvlGui();
				this->levelUp = false;
				this->renderLvlGui(this->window);
			}
		}
		else
		{
			this->spawnEnemies();//acho que isso pode mudar !! checar se spawna antes de entrar na funcao?
			//Colocar esses fors dentro das fun��es de updates, n faz sentido ficar aqui
			for (size_t i = 0; i < this->meleeEnemies.size(); i++)
				meleeEnemies[i].update(player);

			for (size_t i = 0; i < this->bullets.size(); i++)
			{
				if (bullets[i].getShape().getPosition().x > this->window->getSize().x ||
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
}


void Game::hideLvlGui()
{
	this->upgrade1.setString("");
	this->upgrade2.setString("");
	this->upgrade3.setString("");
}

void Game::renderLvlGui(sf::RenderTarget* target)
{
	target->draw(this->upgrade1);
	target->draw(this->upgrade2);
	target->draw(this->upgrade3);
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
	for (auto i : this->experience)
	{
		i.render(*this->window);
	}
	for (auto i : this->meleeEnemies)
	{
		i.render(*this->window);
	}
	//Render gui
	this->renderGui(this->window);
	//Render lvl up
	if(this->levelUp)
		this->renderLvlGui(this->window);
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
