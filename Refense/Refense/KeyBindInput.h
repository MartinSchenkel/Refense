#pragma once

#include "SFML/Graphics.hpp"
#include "Button.h"

class KeyBindInput
{
	enum EButtonState
	{
		EDefault,
		EHovered,
		EClicked
	};
public:
	KeyBindInput();

	sf::Keyboard::Key getBind();

	void setDescriptionPosition(sf::Vector2f a_pos);
	void setBindPosition(sf::Vector2f a_pos);

	void setDescriptionText(std::string* a_text);
	void setColor(sf::Color a_color);
	void setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor);
	void setFontSize(int a_size);
	void setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize);
	void setBind(sf::Keyboard::Key a_bind);

	void update(sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown);
	void reset();
	void drawTo(sf::RenderTexture* a_texture);


private:
	EButtonState m_currentState = EDefault;

	sf::Font m_font;
	sf::Text m_descriptionText;
	sf::Text m_bindText;

	sf::Color m_fontColor[3];
	int m_fontSize[3] = { 20, 22, 22 };

	sf::Keyboard::Key m_currentBind;

	bool m_waitingForInput = false;
};