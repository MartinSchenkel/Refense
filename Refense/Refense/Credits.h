#pragma once

#include "Button.h"
#include "TextScroll.h"

class Credits
{
public:
	Credits();
	void update(sf::Vector2f a_mousePos, float a_deltaTime);
	void drawTo(sf::RenderTexture* a_texture);
	int shouldTransition(); //0 = dont transition, 1 = go back

private:

	Button m_backButton;
	sf::RectangleShape m_buttonBackDrop;

	TextScroll m_scrollPane;

	sf::Font m_textFont;
	sf::Text m_title;
	sf::RectangleShape m_titleBackDrop;

	//todo implement Scroll??

	bool m_goBack = false;

};