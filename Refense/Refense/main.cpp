#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "GameWorld.h"
#include "Timer.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "GameSettings.h"


int main()
{
	sf::Music m_backgroundMusic;
	m_backgroundMusic.openFromFile("../Resources/Audio/RefenseV2.wav");
	m_backgroundMusic.setLoop(true);
	m_backgroundMusic.play();

	GameSettings::get().m_backgroundMusic = &m_backgroundMusic;

	enum EGameStates {
		ETitleScreen,
		EMainMenu,
		ELoading,
		EInGame,
		EPaused,
		EGameOver
	};

	const std::string FRAG_SHADER =
		"#version 130\n\
		\
		uniform sampler2D texture; \
		uniform float blur_radius = 0.001f; \
		\
		void main() \
		{ \
			vec2 offx = vec2(blur_radius, 0.0);\
			vec2 offy = vec2(0.0, blur_radius);\
		\
			vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)      * 30.0 + \
				texture2D(texture, gl_TexCoord[0].xy - offx)        * 5.0 + \
				texture2D(texture, gl_TexCoord[0].xy + offx)        * 5.0 + \
				texture2D(texture, gl_TexCoord[0].xy - offy)        * 5.0 + \
				texture2D(texture, gl_TexCoord[0].xy + offy)        * 5.0 + \
				texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 + \
				texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 + \
				texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 + \
				texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0; \
		 \
			gl_FragColor = gl_Color * (pixel / 2.0); \
		} \
		";

	EGameStates currentState = ETitleScreen;

	TitleScreen* ts = new TitleScreen();
	Menu mainMenu;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Refense");
	window.setFramerateLimit(144);

	window.setKeyRepeatEnabled(true);

	std::srand((unsigned int) time(NULL));

	GameWorld gameWorld;

	GameSettings& k = GameSettings::get();
	Timer& t = Timer::get();
	t.Reset();

	float deltaTime = 0.0f;

	sf::RenderTexture* rt = new sf::RenderTexture();
	rt->create(1920, 1080);

	sf::Shader blurShader;
	blurShader.loadFromMemory(FRAG_SHADER, sf::Shader::Fragment);
	//set up the 'texture' variable in the shader
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);

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
			}
		}

		rt->clear();

		int transitionTo = 0;

		switch (currentState)
		{
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
			mainMenu.update(deltaTime, (sf::Vector2f) sf::Mouse::getPosition(window), pressedKey);
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
			transitionTo = gameWorld.update((sf::Vector2f) sf::Mouse::getPosition(window), deltaTime); // 0 = dont, 1 = pause, 2 = gameOver

			if (transitionTo == 1)
			{
				currentState = EPaused;
			}
			else if (transitionTo == 2)
			{
				currentState = EGameOver;
			}

			gameWorld.draw(rt);

			break;

		case(EPaused):
			gameWorld.draw(rt);

			if (sf::Keyboard::isKeyPressed(GameSettings::get().m_pause))
			{
				currentState = EInGame;
			}

			break;

		case(EGameOver):
			currentState = EMainMenu;
			break;

		default:
			break;
		}

		rt->display();

		window.clear();

		sf::Sprite s(rt->getTexture());

		if(currentState == EInGame) window.draw(s, &blurShader);
		else window.draw(s);

		window.display();
	}
}