#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "GameWorld.h"
#include "Timer.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "GameOverScreen.h"
#include "PauseScreen.h"
#include "GameSettings.h"
#include "ParticleSystem.h"
#include "SoundManager.h"


int main()
{

	GameSettings::get().loadSettings();

	enum EGameStates {
		EParticleTest,
		ETitleScreen,
		EMainMenu,
		ELoading,
		EInGame,
		EPaused,
		EGameOver
	};

	EGameStates currentState = ETitleScreen;

	TitleScreen* ts = new TitleScreen();
	Menu mainMenu;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Refense", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(144);
	window.setKeyRepeatEnabled(true);

	std::srand((unsigned int) time(NULL));

	SoundManager::get().setupSounds();

	GameWorld gameWorld;

	GameSettings& k = GameSettings::get();
	Timer& t = Timer::get();
	t.Reset();

	float deltaTime = 0.0f;

	sf::RenderTexture* rt = new sf::RenderTexture();
	rt->create(1280, 720);

	sf::RenderTexture* hud = new sf::RenderTexture();
	rt->create(1280, 720);

	sf::Shader blurShader;
	blurShader.loadFromFile("../Resources/Shaders/fragshader.frag", sf::Shader::Fragment);
	blurShader.setUniform("u_texture", sf::Shader::CurrentTexture);

	sf::CircleShape circle;
	circle.setPosition(250.0f, 250.f);
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	circle.setOutlineColor(sf::Color::Yellow);
	circle.setOutlineThickness(5.0f);
	circle.setRadius(50.0f);

	GameOverScreen* gameOverScreen = new GameOverScreen();
	PauseScreen pauseScreen;

	sf::Vector2f mousePos;

	while (window.isOpen())
	{
		deltaTime = t.getTimePassedInSec();
		//std::cout << std::floor(1/deltaTime) << std::endl;
		t.Reset();

		//handle events
		sf::Event event;

		sf::Keyboard::Key pressedKey = sf::Keyboard::Unknown;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::EventType::KeyPressed)
			{
				pressedKey = event.key.code;

				if (pressedKey == GameSettings::get().m_pause)
				{
					if (currentState == EInGame)
					{
						SoundManager::get().playSound(SoundManager::get().EPause);
						currentState = EPaused;
					}
					else if (currentState == EPaused)
					{
						SoundManager::get().playSound(SoundManager::get().EPause);
						currentState = EInGame;
					}
				}
			}

			if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}

		mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);

		rt->clear();

		int transitionTo = 0;

		switch (currentState)
		{
		case(EParticleTest):
			
			rt->draw(circle);

			break;

		case(ETitleScreen):

			ts->update(deltaTime);
			
			ts->drawTo(rt);

			if (ts->shouldTransition())
			{
				currentState = EMainMenu;
				delete(ts);
			}

			break;

		case(EMainMenu):
			mainMenu.update(deltaTime, mousePos, pressedKey);
			mainMenu.drawTo(rt);
			transitionTo = mainMenu.shouldTransition();

			if (transitionTo == 2) window.close();
			else if (transitionTo == 1)
			{
				currentState = ELoading;
			}

			break;

		case(ELoading):
			currentState = EInGame;
			break;

		case(EInGame):
			transitionTo = gameWorld.update(mousePos, deltaTime); // 0 = dont, 1 = pause, 2 = gameOver

			if (transitionTo == 1)
			{
				currentState = EPaused;
			}
			else if (transitionTo == 2)
			{
				currentState = EGameOver;
				gameOverScreen = new GameOverScreen();
			}

			gameWorld.draw(rt);

			break;

		case(EPaused):
			if(!pauseScreen.isInSettings) gameWorld.draw(rt);

			transitionTo = pauseScreen.update(mousePos, pressedKey);

			if (transitionTo == 1) currentState = EInGame;
			else if (transitionTo == 3)
			{
				WorldStats::get().m_score = 0;
				gameWorld.resetGame();
				currentState = EMainMenu;
			}

			pauseScreen.drawTo(rt);

			break;

		case(EGameOver):
			if (!gameOverScreen->update(deltaTime, mousePos))
			{
				gameOverScreen->drawTo(rt);
			}
			else currentState = EMainMenu;
			break;

		default:
			break;
		}

		window.clear();

		rt->display();

		sf::Sprite s(rt->getTexture());

		if (currentState == EInGame)
		{
			window.draw(s, &blurShader);
			gameWorld.drawHUD(window);
		}
		else window.draw(s);

		window.display();
	}
}