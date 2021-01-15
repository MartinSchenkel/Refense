#pragma once

#include "Button.h"

class MainMenu
{
public:
	MainMenu();
	void update(sf::Vector2f a_mousePos);
	void drawTo(sf::RenderTexture* a_texture);
	int shouldTransition(); //0 = dont transition, 1 = StartGame, 2 = Settings, 3 = Credits, 4 = Quit Game

private:

	Button m_startButton;
	Button m_settingButton;
	Button m_creditsButton;
	Button m_quitButton;

	sf::Font m_titleFont; //Todo: animation?
	sf::Text m_titleText;

	sf::Font m_copyrightFont;
	sf::Text m_copyrightText;

	bool m_startGame = false;
	bool m_openSettings = false;
	bool m_openCredits = false;
	bool m_quitApplication = false;

};