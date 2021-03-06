#pragma once

#include "SFML/Graphics.hpp"

#include "SoundManager.h"

class Checkbox
{
	enum EButtonState
	{
		EDefault,
		EHovered,
		EClicked
	};
public:
	Checkbox();

	void setButtonText(std::string* a_text);

	void setColor(sf::Color a_color);

	void setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor);

	void setFontSize(int a_size);

	void setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize);

	void setOnClickVariable(bool* a_variableToChange);

	void update(sf::Vector2f a_mousePos);

	void drawTo(sf::RenderTexture* a_texture);

	void setCurrentValue(bool a_value);
	bool getCurrentValue();

	sf::Vector2f getSize();

	sf::Vector2f m_position;

private:

	EButtonState m_currentState = EDefault;

	sf::Font m_buttonFont;
	sf::Text m_buttonText;

	std::string m_buttonDescription = "";

	sf::Color m_fontColor[3];
	int m_fontSize[3] = { 30, 30, 30 };

	bool m_currentValue;

	SoundManager& m_soundplayer = SoundManager::get();
};