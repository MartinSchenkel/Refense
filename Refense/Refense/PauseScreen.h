#pragma once

#include <SFML\Graphics.hpp>

#include "Settings.h"
#include "Button.h"

class PauseScreen
{
public:
	PauseScreen()
	{
		m_background.setPosition(0, 0);
		m_background.setSize(sf::Vector2f(2000, 2000));
		m_background.setFillColor(sf::Color(0, 0, 0, 200));

		m_highlight.setPosition(300, 100);
		m_highlight.setSize(sf::Vector2f(600, 400));
		m_highlight.setFillColor(sf::Color(50, 50, 50, 255));

		std::string temp = "Resume Game";
		m_resumeButton.setButtonText(&temp);
		m_resumeButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_resumeButton.m_position = sf::Vector2f(400, 200);

		temp = "Settings";
		m_settingsButton.setButtonText(&temp);
		m_settingsButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_settingsButton.m_position = sf::Vector2f(400, 300);

		temp = "Exit to Main Menu";
		m_backToMainMenuButton.setButtonText(&temp);
		m_backToMainMenuButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_backToMainMenuButton.m_position = sf::Vector2f(400, 400);

	}
	int update(sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown)
	{
		int toReturn = 0;
		if (!isInSettings)
		{
			if (m_resumeButton.update(a_mousePos)) toReturn = 1;
			if (m_settingsButton.update(a_mousePos))
			{
				isInSettings = true;
			}
			if (m_backToMainMenuButton.update(a_mousePos)) toReturn = 3;
		}
		else
		{
			m_settings.update(a_mousePos, a_keyDown);

			if (m_settings.shouldTransition() == 1)
			{
				isInSettings = false;
			}
		}
		return toReturn;
	}
	void drawTo(sf::RenderTexture* a_texture)
	{
		if (!isInSettings)
		{
			a_texture->draw(m_background);
			a_texture->draw(m_highlight);

			m_resumeButton.drawTo(a_texture);
			m_settingsButton.drawTo(a_texture);
			m_backToMainMenuButton.drawTo(a_texture);

			return;
		}
		m_settings.drawTo(a_texture);
	}


	bool isInSettings = false;
private:

	sf::RectangleShape m_background;
	sf::RectangleShape m_highlight;

	Button m_resumeButton;
	Button m_settingsButton;
	Button m_backToMainMenuButton;

	Settings m_settings;

};
