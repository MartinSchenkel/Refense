#pragma once

#include <vector>

#include "SFML\Graphics.hpp"

enum ETextLayout
{
	ELeftBound,
	ERightBound,
	ECentered
};

class TextScroll
{
public:
	TextScroll();
	void update(float a_deltaTime);
	void drawTo(sf::RenderTexture* a_texture);
	void reset();

	void addText(std::string a_newLine);
	void setFont(sf::Font a_font);
	void setFontSize(int a_fontSize);
	void setInitialPosition(sf::Vector2f a_pos);
	void setScrollDirection(sf::Vector2f a_dir);
	void setGapSize(sf::Vector2f a_size);
	void setScrollDelay(float a_delay);
	void setScrollSpeed(float a_speed);
	void setTextLayout(ETextLayout a_layout);

private:
	std::vector<sf::Text> m_textLines;
	sf::Font m_font;
	int m_fontSize = 20;

	sf::Vector2f m_initialPosition;
	sf::Vector2f m_scrollDirection = sf::Vector2f(0, -1);
	sf::Vector2f m_gapSize = sf::Vector2f(0, 50.0f);
	float m_scrollDelay = 0.0f, m_alreadyDelayedBy = 0.0f;
	float m_scrollSpeed = 60.0f;

	ETextLayout m_currentLayout = ECentered;

	//TODO Maybe add "pause" and "copy line" functionality
};