#include "KeyBindInput.h"

KeyBindInput::KeyBindInput()
{
	m_font.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_descriptionText.setFont(m_font);
	m_bindText.setFont(m_font);
}

sf::Keyboard::Key KeyBindInput::getBind()
{
	return m_currentBind;
}

void KeyBindInput::setDescriptionPosition(sf::Vector2f a_pos)
{
	m_descriptionText.setPosition(a_pos);
}

void KeyBindInput::setBindPosition(sf::Vector2f a_pos)
{
	m_bindText.setPosition(a_pos);
}

void KeyBindInput::setDescriptionText(std::string* a_text)
{
	m_descriptionText.setString(*a_text);
}

void KeyBindInput::setColor(sf::Color a_color)
{
	for (auto& c : m_fontColor)
	{
		c = a_color;
	}
}

void KeyBindInput::setColors(sf::Color a_defaultColor, sf::Color a_hoverColor, sf::Color a_clickedColor)
{
	m_fontColor[0] = a_defaultColor;
	m_fontColor[1] = a_hoverColor;
	m_fontColor[2] = a_clickedColor;
}

void KeyBindInput::setFontSize(int a_size)
{
	for (auto s : m_fontSize)
	{
		s = a_size;
	}
}

void KeyBindInput::setSizes(int a_defaultSize, int a_hoverSize, int a_clickedSize)
{
	m_fontSize[0] = a_defaultSize;
	m_fontSize[1] = a_hoverSize;
	m_fontSize[2] = a_clickedSize;
}

void KeyBindInput::update(sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown)
{
	if (m_bindText.getGlobalBounds().contains(a_mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_currentState = EClicked;
			m_bindText.setString("");
			m_waitingForInput = true;
		}
		else m_currentState = EHovered;
	}
	else m_currentState = EDefault;

	m_descriptionText.setFillColor(m_fontColor[m_currentState]);
	m_descriptionText.setCharacterSize(m_fontSize[m_currentState]);

	m_bindText.setFillColor(m_fontColor[m_currentState]);
	m_bindText.setCharacterSize(m_fontSize[m_currentState]);

	if (m_waitingForInput)
	{
		if (a_keyDown != sf::Keyboard::Unknown)
		{
			m_currentBind = a_keyDown;
			m_bindText.setString(GameSettings::get().fromKtoS(m_currentBind));

			m_waitingForInput = false;
		}
	}
}


void KeyBindInput::reset()
{
	m_waitingForInput = false;
	m_bindText.setString(GameSettings::get().fromKtoS(m_currentBind));
}


void KeyBindInput::drawTo(sf::RenderTexture* a_texture)
{

	a_texture->draw(m_bindText);
	a_texture->draw(m_descriptionText);
}

void KeyBindInput::setBind(sf::Keyboard::Key a_bind)
{
	m_currentBind = a_bind;

	m_bindText.setString(GameSettings::get().fromKtoS(m_currentBind));
}