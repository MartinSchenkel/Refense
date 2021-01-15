#include "MainMenu.h"

MainMenu::MainMenu()
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
	m_startButton.setOnClickVariable(&m_startGame);

	temp = "Settings";
	m_settingButton.setButtonText(&temp);
	m_settingButton.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_settingButton.m_position = sf::Vector2f(100, 400);
	m_settingButton.setOnClickVariable(&m_openSettings);

	temp = "Credits";
	m_creditsButton.setButtonText(&temp);
	m_creditsButton.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_creditsButton.m_position = sf::Vector2f(100, 500);
	m_creditsButton.setOnClickVariable(&m_openCredits);

	temp = "Quit";
	m_quitButton.setButtonText(&temp);
	m_quitButton.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_quitButton.m_position = sf::Vector2f(100, 600);
	m_quitButton.setOnClickVariable(&m_quitApplication);

}
void MainMenu::update(sf::Vector2f a_mousePos)
{
	m_startButton.update(a_mousePos);
	m_settingButton.update(a_mousePos);
	m_creditsButton.update(a_mousePos);
	m_quitButton.update(a_mousePos);
}
void MainMenu::drawTo(sf::RenderTexture* a_texture)
{
	a_texture->draw(m_titleText);
	a_texture->draw(m_copyrightText);
	m_startButton.drawTo(a_texture);
	m_settingButton.drawTo(a_texture);
	m_creditsButton.drawTo(a_texture);
	m_quitButton.drawTo(a_texture);
}
int MainMenu::shouldTransition()
{
	if (m_quitApplication)
	{
		m_quitApplication = false;
		return 4;
	}
	else if (m_startGame)
	{
		m_startGame = false;
		return 1;

	}
	else if (m_openSettings)
	{
		m_openSettings = false;
		return 2;

	}
	else if (m_openCredits)
	{
		m_openCredits = false;
		return 3;
	}
	return 0;
}
