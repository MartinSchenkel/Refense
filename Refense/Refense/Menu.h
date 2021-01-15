#pragma once

#include "MainMenu.h"
#include "Credits.h"
#include "Settings.h"

class Menu
{
	enum EMenuState
	{
		EMain,
		ESettings,
		ECredits,
	};

public:
	Menu();
	void update(float a_deltaTime, sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown);
	void drawTo(sf::RenderTexture* a_texture);
	int shouldTransition(); //0 = dont transition, 1 = transition, 2 = Close Application

private:
	MainMenu m_mainMenu;
	Settings m_settings;
	Credits m_credits;

	EMenuState m_currentState = EMain;

	sf::Font m_TitleFont;

	//todo: background animation

};