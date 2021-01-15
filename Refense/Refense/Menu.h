#pragma once

#include "MainMenu.h"

enum EMenuState
{
	EMain,
	ESettings,
	ECredits,
};

class Menu
{
public:
	Menu()
	{

	}
	void update(float a_deltaTime, sf::Vector2f a_mousePos)
	{
		switch (m_currentState)
		{
		case(EMain):
			m_mainMenu.update(a_mousePos);
			break;

		case(ESettings):
			break;

		case(ECredits):
			break;

		default:
			break;
		}
	}
	void drawTo(sf::RenderTexture* a_texture)
	{
		switch (m_currentState)
		{
		case(EMain):
			m_mainMenu.drawTo(a_texture);
			break;

		case(ESettings):
			break;

		case(ECredits):
			break;

		default:
			break;
		}
	}
	bool shouldTransition()
	{
		return false;
	}

private:
	MainMenu m_mainMenu;


	EMenuState m_currentState = EMain;

	sf::Font m_TitleFont;

	//todo: background animation

};