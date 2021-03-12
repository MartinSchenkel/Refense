#pragma once

#include <vector>

#include "SFML\Graphics.hpp"

class HUD
{
public:
	HUD();
	void drawTo(sf::RenderWindow& a_window, int a_playerhealth);

private:

	sf::Font m_UIFont;
	sf::Text m_scoreUI;
	
	sf::Texture m_healthUITexture;
	sf::Sprite m_healthUI[3];
};