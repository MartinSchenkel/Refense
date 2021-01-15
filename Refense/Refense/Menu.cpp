#include "Menu.h"


Menu::Menu()
{

}
void Menu::update(float a_deltaTime, sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown)
{
	switch (m_currentState)
	{
	case(EMain):
		m_mainMenu.update(a_mousePos);
		break;

	case(ESettings):
		m_settings.update(a_mousePos, a_keyDown);
		break;

	case(ECredits):
		m_credits.update(a_mousePos, a_deltaTime);
		break;

	default:
		break;
	}
}
void Menu::drawTo(sf::RenderTexture* a_texture)
{
	switch (m_currentState)
	{
	case(EMain):
		m_mainMenu.drawTo(a_texture);
		break;

	case(ESettings):
		m_settings.drawTo(a_texture);
		break;

	case(ECredits):
		m_credits.drawTo(a_texture);
		break;

	default:
		break;
	}
}
int Menu::shouldTransition()
{
	int transitionResult = 0;
	switch (m_currentState)
	{
	case(EMain):
		
		transitionResult = m_mainMenu.shouldTransition();

		if (transitionResult == 1) return 1;
		else if (transitionResult == 2) m_currentState = ESettings;
		else if (transitionResult == 3) m_currentState = ECredits;
		else if (transitionResult == 4) return 2;

		break;

	case(ESettings):
		transitionResult = m_settings.shouldTransition();

		if (transitionResult == 1) m_currentState = EMain;
		break;

	case(ECredits):
		transitionResult = m_credits.shouldTransition();

		if (transitionResult == 1) m_currentState = EMain;
		break;

	default:
		break;
	}

	return 0;
}