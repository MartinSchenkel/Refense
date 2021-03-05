#pragma once

#include "SFML/Graphics.hpp"
#include "ParticleModule.h"

#include <vector>

class ParticleSystem
{
public: 
	ParticleSystem(float a_lifeTime = 0.0f);

	void update(float a_deltaTime, sf::Vector2f a_newPos);
	void drawTo(sf::RenderTexture* a_texture);


	std::vector<ParticleModule*> m_modules;	
	sf::Vector2f m_position = sf::Vector2f(100, 100);
	sf::Vector2f m_initialVelocity = sf::Vector2f(0, 0);
	sf::Vector2f m_gravity = sf::Vector2f(0, 0);
	bool m_loops = true;
	float m_lifeTime = 0.0f; // 0 and smaller = infinite

private:
	float m_restLifeTime = 0.0f;

};
