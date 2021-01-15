#pragma once

#include "Button.h"

class MainMenu
{
public:
	MainMenu()
	{
		m_titleFont.loadFromFile("../Resources/Fonts/Electric city.ttf");
		m_titleText.setFont(m_titleFont);
		m_titleText.setStyle(sf::Text::Bold);
		m_titleText.setCharacterSize(128);
		m_titleText.setPosition(300, 20);
		m_titleText.setString("Refense");

		m_copyrightFont.loadFromFile("../Resources/Fonts/unispace.ttf");
		m_copyrightText.setFont(m_copyrightFont);
		m_copyrightText.setCharacterSize(16);
		m_copyrightText.setPosition(850, 690);
		m_copyrightText.setString("copyright: Martin Schenkel (2021)");

		std::string temp = "Start";
		m_startButton.setButtonText(&temp);
		m_startButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_startButton.m_position = sf::Vector2f(100, 300);

		temp = "Settings";
		m_settingButton.setButtonText(&temp);
		m_settingButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_settingButton.m_position = sf::Vector2f(100, 400);

		temp = "Credits";
		m_creditsButton.setButtonText(&temp);
		m_creditsButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_creditsButton.m_position = sf::Vector2f(100, 500);

		temp = "Quit";
		m_quitButton.setButtonText(&temp);
		m_quitButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_quitButton.m_position = sf::Vector2f(100, 600);

	}
	void update(sf::Vector2f a_mousePos)
	{
		m_startButton.update(a_mousePos);
		m_settingButton.update(a_mousePos);
		m_creditsButton.update(a_mousePos);
		m_quitButton.update(a_mousePos);
	}
	void drawTo(sf::RenderTexture* a_texture)
	{
		a_texture->draw(m_titleText);
		a_texture->draw(m_copyrightText);
		m_startButton.drawTo(a_texture);
		m_settingButton.drawTo(a_texture);
		m_creditsButton.drawTo(a_texture);
		m_quitButton.drawTo(a_texture);
	}
	bool shouldTransition()
	{
		return false;
	}

private:

	Button m_startButton;
	Button m_settingButton;
	Button m_creditsButton;
	Button m_quitButton;

	sf::Font m_titleFont; //Todo: animation?
	sf::Text m_titleText;

	sf::Font m_copyrightFont;
	sf::Text m_copyrightText;

};