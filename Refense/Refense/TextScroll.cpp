#include "TextScroll.h"

TextScroll::TextScroll()
{

}
void TextScroll::update(float a_deltaTime)
{
	if (m_scrollDelay < m_alreadyDelayedBy)
	{
		for (size_t i = 0; i < m_textLines.size(); i++)
		{
			m_textLines[i].setPosition(m_textLines[i].getPosition().x + (m_scrollDirection.x * m_scrollSpeed * a_deltaTime), m_textLines[i].getPosition().y + (m_scrollDirection.y * m_scrollSpeed * a_deltaTime));
		}
	}
	else 
	{
		m_alreadyDelayedBy += a_deltaTime;
	}
}
void TextScroll::drawTo(sf::RenderTexture* a_texture)
{
	for (size_t i = 0; i < m_textLines.size(); i++)
	{
		a_texture->draw(m_textLines[i]);
	}
}
void TextScroll::reset()
{
	m_alreadyDelayedBy = 0.0f;

	for (int i = 0; i < m_textLines.size(); i++)
	{
		if (m_currentLayout == ELeftBound)
		{
			m_textLines[i].setPosition(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
		}
		else if (m_currentLayout == ECentered)
		{
			sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
			tempPos = sf::Vector2f(tempPos.x - m_textLines[i].getGlobalBounds().width / 2, tempPos.y - m_textLines[i].getGlobalBounds().height / 2);
			m_textLines[i].setPosition(tempPos);
		}
		else if (m_currentLayout == ERightBound)
		{
			sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
			tempPos = sf::Vector2f(tempPos.x - m_textLines[i].getGlobalBounds().width, tempPos.y - m_textLines[i].getGlobalBounds().height);
			m_textLines[i].setPosition(tempPos);
		}
	}
}

void TextScroll::addText(std::string a_newLine)
{
	sf::Text tempText;
	tempText.setString(a_newLine);
	tempText.setCharacterSize(m_fontSize);
	tempText.setFont(m_font);

	if (m_currentLayout == ELeftBound)
	{
		tempText.setPosition(m_initialPosition.x + (m_gapSize.x * (int)m_textLines.size()), m_initialPosition.y + (m_gapSize.y * (int)m_textLines.size()));
	}
	else if (m_currentLayout == ECentered)
	{
		sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * (int)m_textLines.size()), m_initialPosition.y + (m_gapSize.y * (int)m_textLines.size()));
		tempPos = sf::Vector2f(tempPos.x - tempText.getGlobalBounds().width / 2, tempPos.y - tempText.getGlobalBounds().height / 2);
		tempText.setPosition(tempPos);
	}
	else if (m_currentLayout == ERightBound)
	{
		sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * (int)m_textLines.size()), m_initialPosition.y + (m_gapSize.y * (int)m_textLines.size()));
		tempPos = sf::Vector2f(tempPos.x - tempText.getGlobalBounds().width, tempPos.y - tempText.getGlobalBounds().height);
		tempText.setPosition(tempPos);
	}

	m_textLines.push_back(tempText);
}
void TextScroll::setFont(sf::Font a_font)
{
	m_font = a_font;

	for (size_t i = 0; i < m_textLines.size(); i++)
	{
		m_textLines[i].setFont(m_font);
	}
}
void TextScroll::setFontSize(int a_fontSize)
{
	m_fontSize = a_fontSize;

	for (size_t i = 0; i < m_textLines.size(); i++)
	{
		m_textLines[i].setCharacterSize(m_fontSize);
	}
}
void TextScroll::setInitialPosition(sf::Vector2f a_pos)
{
	m_initialPosition = a_pos;

	for (int i = 0; i < m_textLines.size(); i++)
	{
		if (m_currentLayout == ELeftBound)
		{
			m_textLines[i].setPosition(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
		}
		else if (m_currentLayout == ECentered)
		{
			sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
			tempPos = sf::Vector2f(tempPos.x - m_textLines[i].getGlobalBounds().width / 2, tempPos.y - m_textLines[i].getGlobalBounds().height / 2);
			m_textLines[i].setPosition(tempPos);
		}
		else if (m_currentLayout == ERightBound)
		{
			sf::Vector2f tempPos = sf::Vector2f(m_initialPosition.x + (m_gapSize.x * i), m_initialPosition.y + (m_gapSize.y * i));
			tempPos = sf::Vector2f(tempPos.x - m_textLines[i].getGlobalBounds().width, tempPos.y - m_textLines[i].getGlobalBounds().height);
			m_textLines[i].setPosition(tempPos);
		}
	}
}
void TextScroll::setScrollDirection(sf::Vector2f a_dir)
{
	m_scrollDirection = a_dir;
}
void TextScroll::setGapSize(sf::Vector2f a_size)
{
	m_gapSize = a_size;
}
void TextScroll::setScrollDelay(float a_delay)
{
	m_scrollDelay = a_delay;
}
void TextScroll::setScrollSpeed(float a_speed)
{
	m_scrollSpeed = a_speed;
}
void TextScroll::setTextLayout(ETextLayout a_layout)
{
	m_currentLayout = a_layout;
}