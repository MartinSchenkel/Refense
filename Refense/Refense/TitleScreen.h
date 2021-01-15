#pragma once

#include <SFML\Graphics.hpp>

class TitleScreen
{
public:
	TitleScreen() 
	{
		m_logoTexture.loadFromFile("../Resources/Logos/SFML_Logo.png");
		m_sfmlLogo.setTexture(m_logoTexture);
		m_sfmlLogo.setPosition(300, 280);


		m_poweredByFont.loadFromFile("../Resources/Fonts/unispace bold.ttf");
		m_poweredByText.setFont(m_poweredByFont);
		m_poweredByText.setString("Powered By");
		m_poweredByText.setPosition(500, 200);

	}
	void update(float a_deltaTime)
	{
		m_duration -= a_deltaTime;
	}
	void drawTo(sf::RenderTexture* a_texture)
	{
		//draw all the things that should be on the title screen
		a_texture->draw(m_sfmlLogo);
		a_texture->draw(m_poweredByText);
	}
	bool shouldTransition()
	{
		return m_duration <= 0.0f;
	}

private:

	float m_duration = 2.0f;

	sf::Font m_poweredByFont;
	sf::Text m_poweredByText;

	sf::Texture m_logoTexture;
	sf::Sprite m_sfmlLogo;

	//todo maybe add fade in/out

};