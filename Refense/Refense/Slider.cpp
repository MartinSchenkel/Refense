#include "Slider.h"

#include <math.h>

Slider::Slider()
{
	m_font.loadFromFile("../Resources/Fonts/unispace.ttf");

	m_sliderTitle.setString("title");
	m_sliderTitle.setFont(m_font);
	m_valueText.setString(std::to_string(m_value));
	m_valueText.setFont(m_font);
}
Slider::Slider(float a_initialValue)
{
	m_value = a_initialValue;
	
	m_sliderTitle.setString("title");
	m_valueText.setString(std::to_string(m_value));
}
void Slider::setValue(float a_value)
{
	a_value = std::clamp(a_value, 0.0f, 1.0f);

	m_value = a_value;
	m_valueText.setString(std::to_string((int) (m_value * 10)));
}

float Slider::getValue()
{
	return m_value;
}

void Slider::update(sf::Vector2f a_mousePos)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_isBeingDragged = false;
	}

	if (m_sliderHead.getGlobalBounds().contains(a_mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_isBeingDragged = true;
		}
	}

	if (m_isBeingDragged)
	{
		float xMousePos = a_mousePos.x;
		xMousePos = std::clamp(xMousePos, m_sliderBar.getPosition().x, m_sliderBar.getPosition().x + m_sliderBar.getSize().x);

		m_sliderHead.setPosition(xMousePos, m_sliderHead.getPosition().y);

		m_value = (xMousePos - m_sliderBar.getPosition().x) / m_sliderBar.getSize().x;
		m_valueText.setString(std::to_string((int)(m_value * 10)));
	}
}
void Slider::drawTo(sf::RenderTexture* a_texture)
{
	a_texture->draw(m_sliderTitle);
	if(m_showValue) a_texture->draw(m_valueText);

	a_texture->draw(m_sliderBar);
	a_texture->draw(m_sliderHead);
}

void Slider::setPosition(sf::Vector2f a_pos)
{
	m_sliderBar.setPosition(a_pos);

	m_sliderTitle.setPosition(sf::Vector2f(
		a_pos.x + (m_sliderBar.getSize().x / 2) - (m_sliderTitle.getGlobalBounds().width / 2), 
		a_pos.y - 70.0f));

	m_valueText.setPosition(sf::Vector2f(
		a_pos.x + (m_sliderBar.getSize().x) + 50.0f,
		a_pos.y + (m_sliderBar.getSize().y / 2) - (m_valueText.getGlobalBounds().height / 2)));

	m_sliderHead.setPosition(sf::Vector2f(
		a_pos.x + (m_sliderBar.getSize().x * m_value) - (m_sliderHead.getSize().x / 2),
		a_pos.y + (m_sliderBar.getSize().y / 2) - (m_sliderHead.getSize().y / 2)));

}
void Slider::setHeadSize(sf::Vector2f a_size)
{
	m_sliderHead.setSize(a_size);
}
void Slider::setBarSize(sf::Vector2f a_size)
{
	m_sliderBar.setSize(a_size);
}

void Slider::setFont(sf::Font a_font)
{
	m_sliderTitle.setFont(a_font);
	m_valueText.setFont(a_font);
}

void Slider::setBarColor(sf::Color a_color)
{
	m_sliderBar.setFillColor(a_color);
}
void Slider::setHeadColor(sf::Color a_color)
{
	m_sliderHead.setFillColor(a_color);
}
void Slider::setTitleColor(sf::Color a_color)
{
	m_sliderTitle.setFillColor(a_color);
}
void Slider::setValueColor(sf::Color a_color)
{
	m_valueText.setFillColor(a_color);
}
void Slider::setShowValue(bool a_show)
{
	m_showValue = a_show;
}

void Slider::setTitleText(std::string a_title)
{
	m_sliderTitle.setString(a_title);
}