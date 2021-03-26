#include "Checkbox.h"

Checkbox::Checkbox()
{
	m_buttonFont.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_buttonText.setFont(m_buttonFont);
}

void Checkbox::setCurrentValue(bool a_value)
{
	m_currentValue = a_value;
}

bool Checkbox::getCurrentValue()
{
	return m_currentValue;
}

void Checkbox::setButtonText(std::string* a_text)
{
	m_buttonDescription = *a_text;

	if (m_currentValue)
	{
		m_buttonText.setString(m_buttonDescription + " On");
		return;
	}

	m_buttonText.setString(m_buttonDescription + " Off");
}

void Checkbox::setColor(sf::Color a_color)
{
	for (auto& c : m_fontColor)
	{
		c = a_color;
	}
}

void Checkbox::setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor)
{
	m_fontColor[0] = a_defaultColor;
	m_fontColor[1] = a_hoverColor;
	m_fontColor[2] = a_clickedColor;
}

void Checkbox::setFontSize(int a_size)
{
	for (auto s : m_fontSize)
	{
		s = a_size;
	}
}

void Checkbox::setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize)
{
	m_fontSize[0] = a_defaultSize;
	m_fontSize[1] = a_hoverSize;
	m_fontSize[2] = a_clickedSize;
}

void Checkbox::update(sf::Vector2f a_mousePos)
{
	if (m_buttonText.getGlobalBounds().contains(a_mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_currentState != EClicked)
			{
				m_currentState = EClicked;

				m_soundplayer.playSound(m_soundplayer.EButton);

				m_currentValue = !m_currentValue;

				if (m_currentValue)
				{
					m_buttonText.setString(m_buttonDescription + "On");
				}
				else m_buttonText.setString(m_buttonDescription + "Off");

			}			
		}
		else m_currentState = EHovered;
	}
	else m_currentState = EDefault;
}

void Checkbox::drawTo(sf::RenderTexture* a_texture)
{
	m_buttonText.setFillColor(m_fontColor[m_currentState]);
	m_buttonText.setCharacterSize(m_fontSize[m_currentState]);
	m_buttonText.setPosition(m_position);

	//draw all the things that should be on the title screen
	a_texture->draw(m_buttonText);
}

sf::Vector2f Checkbox::getSize()
{
	return sf::Vector2f(m_buttonText.getGlobalBounds().width, m_buttonText.getGlobalBounds().height);
}