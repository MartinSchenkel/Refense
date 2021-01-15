#include "Button.h"

Button::Button() 
{
	m_buttonFont.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_buttonText.setFont(m_buttonFont);
}

void Button::setButtonText(std::string* a_text)
{
	m_buttonText.setString(*a_text);
}

void Button::setColor(sf::Color a_color)
{
	for (auto& c : m_fontColor)
	{
		c = a_color;
	}
}

void Button::setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor)
{
	m_fontColor[0] = a_defaultColor;
	m_fontColor[1] = a_hoverColor;
	m_fontColor[2] = a_clickedColor;
}

void Button::setFontSize(int a_size)
{
	for (auto s : m_fontSize)
	{
		s = a_size;
	}
}

void Button::setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize)
{
	m_fontSize[0] = a_defaultSize;
	m_fontSize[1] = a_hoverSize;
	m_fontSize[2] = a_clickedSize;
}

void Button::update(sf::Vector2f a_mousePos)
{
	if (m_buttonText.getGlobalBounds().contains(a_mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_currentState = EClicked;
			if(m_onClickVariable != nullptr)
				*m_onClickVariable = true;
		}
		else m_currentState = EHovered;
	}
	else m_currentState = EDefault;
}

void Button::drawTo(sf::RenderTexture* a_texture)
{
	m_buttonText.setFillColor(m_fontColor[m_currentState]);
	m_buttonText.setCharacterSize(m_fontSize[m_currentState]);
	m_buttonText.setPosition(m_position);

	//draw all the things that should be on the title screen
	a_texture->draw(m_buttonText);
}

void Button::setOnClickVariable(bool* a_variableToChange)
{
	m_onClickVariable = a_variableToChange;
}


sf::Vector2f Button::getSize()
{
	return sf::Vector2f(m_buttonText.getGlobalBounds().width, m_buttonText.getGlobalBounds().height);
}