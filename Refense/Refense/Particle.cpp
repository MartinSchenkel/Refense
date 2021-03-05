#include "Particle.h"

#include <iostream>
#include <cmath>

bool Particle::update(float a_deltaTime)
{
	m_remainingLifeTime -= a_deltaTime;

	if (m_remainingLifeTime <= 0)
	{
		return false;
	}
	float alpha = a_deltaTime / m_remainingLifeTime; //alpha for lerps

	//velocity
	m_sprite.move(m_currentVelocity * a_deltaTime);

	//size
	float xScaleDifference = m_finalScale.x - m_sprite.getScale().x;
	float yScaleDifference = m_finalScale.y - m_sprite.getScale().y;

	m_sprite.setScale(m_sprite.getScale().x + alpha * xScaleDifference, m_sprite.getScale().y + alpha * yScaleDifference); //lerp so that by the end of the lifetime the desired size is reached

	//color
	float redDifference = m_finalColor.r - m_sprite.getColor().r;
	float greenDifference = m_finalColor.g - m_sprite.getColor().g;
	float blueDifference = m_finalColor.b - m_sprite.getColor().b;
	float alphaDifference = m_finalColor.a - m_sprite.getColor().a;

	sf::Color c(redDifference * alpha, greenDifference * alpha, blueDifference * alpha, alphaDifference * alpha);

	m_sprite.setColor(m_sprite.getColor() + c);

	return true;
}

void Particle::drawTo(sf::RenderTexture* a_texture)
{
	a_texture->draw(m_sprite);
}