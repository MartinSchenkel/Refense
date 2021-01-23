#pragma once

#include "SFML\Graphics.hpp"

class Slider
{
public:
	Slider();
	Slider(float a_initialValue);
	void setValue(float a_value);
	float getValue();

	void update(sf::Vector2f a_mousePos);
	void drawTo(sf::RenderTexture* a_texture);

	void setPosition(sf::Vector2f a_pos);
	void setHeadSize(sf::Vector2f a_size);
	void setBarSize(sf::Vector2f a_size);

	void setFont(sf::Font a_font);

	void setBarColor(sf::Color a_color);
	void setHeadColor(sf::Color a_color);
	void setTitleColor(sf::Color a_color);
	void setValueColor(sf::Color a_color);
	void setShowValue(bool a_show);

	void setTitleText(std::string a_title);

private:
	
	float m_value = 1.0f;

	sf::RectangleShape m_sliderBar;
	sf::RectangleShape m_sliderHead;
	sf::Text m_sliderTitle;
	sf::Font m_font;
	bool m_showValue = true;
	sf::Text m_valueText;

	bool m_isBeingDragged = false;
};