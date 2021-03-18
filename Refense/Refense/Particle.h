#pragma once

#include "SFML/Graphics.hpp"

class Particle
{
public:
	bool update(float a_deltaTime);
	void drawTo(sf::RenderTexture* a_texture);

	sf::Sprite m_sprite;

	sf::Vector2f m_currentVelocity = sf::Vector2f(0, 0);
	float m_remainingLifeTime = 10;
	sf::Color m_finalColor = sf::Color(255, 255, 255, 0);
	sf::Vector2f m_finalScale = sf::Vector2f(1, 1);
};