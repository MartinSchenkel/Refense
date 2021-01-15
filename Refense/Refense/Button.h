#pragma once

#include "SFML/Graphics.hpp"


enum EButtonState
{
	EDefault,
	EHovered,
	EClicked
};

class Button
{
public:
	Button() 
	{
		m_buttonFont.loadFromFile("../Resources/Fonts/unispace.ttf");
		m_buttonText.setFont(m_buttonFont);
	}

	void setButtonText(std::string* a_text)
	{
		m_buttonText.setString(*a_text);
	}

	void setColor(sf::Color a_color)
	{
		for (auto& c : m_fontColor)
		{
			c = a_color;
		}
	}

	void setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor)
	{
		m_fontColor[0] = a_defaultColor;
		m_fontColor[1] = a_hoverColor;
		m_fontColor[2] = a_clickedColor;
	}

	void setFontSize(int a_size)
	{
		for (auto s : m_fontSize)
		{
			s = a_size;
		}
	}

	void setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize)
	{
		m_fontSize[0] = a_defaultSize;
		m_fontSize[1] = a_hoverSize;
		m_fontSize[2] = a_clickedSize;
	}

	void update(sf::Vector2f a_mousePos)
	{
		if (m_buttonText.getGlobalBounds().contains(a_mousePos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) currentState = EClicked;
			else currentState = EHovered;
		}
		else currentState = EDefault;
	}

	void drawTo(sf::RenderTexture* a_texture)
	{
		m_buttonText.setFillColor(m_fontColor[currentState]);
		m_buttonText.setCharacterSize(m_fontSize[currentState]);
		m_buttonText.setPosition(m_position);

		//draw all the things that should be on the title screen
		a_texture->draw(m_buttonText);
	}

	sf::Vector2f m_position;

private:

	EButtonState currentState = EDefault;

	sf::Font m_buttonFont;
	sf::Text m_buttonText;

	sf::Color m_fontColor[3];
	int m_fontSize[3] = { 30, 30, 30 };

};