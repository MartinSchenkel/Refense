#include "ParticleModule.h"

#include <iostream>

ParticleModule::ParticleModule(std::string a_path)
{
	m_particleTexture.loadFromFile(a_path);
	m_currentSpawnCoolDown = getRandomFloatinRange(m_spawnCoolDown.x, m_spawnCoolDown.y);
}

void ParticleModule::setTexturePath(std::string a_path)
{
	m_particleTexture.loadFromFile(a_path);
}

void ParticleModule::update(float a_deltaTime, sf::Vector2f a_systemPosition)
{
	m_currentSpawnCoolDown = m_currentSpawnCoolDown - a_deltaTime;
	if (m_currentSpawnCoolDown <= 0)
	{
		spawnParticles(a_systemPosition + m_offset);
		m_currentSpawnCoolDown = getRandomFloatinRange(m_spawnCoolDown.x, m_spawnCoolDown.y);
	}

	for (int i = 0; i < m_particles.size(); i++)
	{
		if (m_gravityType == EDirection)
		{
			m_particles[i]->m_currentVelocity -= m_gravity;
		}
		else if (m_gravityType == EToPoint)
		{

			sf::Vector2f pulltowards = a_systemPosition + m_offset + m_gravityPoint;

			sf::Vector2f dir = pulltowards - m_particles[i]->m_sprite.getPosition();

			dir.x /= (dir.x * dir.x) + (dir.y * dir.y);
			dir.y /= (dir.x * dir.x) + (dir.y * dir.y);

			m_particles[i]->m_currentVelocity += m_gravity.x * dir;
		}
		else if (m_gravityType == EAwayFromPoint)
		{

			sf::Vector2f goawayfrom = a_systemPosition + m_offset + m_gravityPoint;

			sf::Vector2f dir = m_particles[i]->m_sprite.getPosition() - goawayfrom;

			dir.x /= (dir.x * dir.x) + (dir.y * dir.y);
			dir.y /= (dir.x * dir.x) + (dir.y * dir.y);

			m_particles[i]->m_currentVelocity += m_gravity.x * dir;
		}

		if (!m_particles[i]->update(a_deltaTime)) //if the particle is dead
		{
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
			i--;
		}
	}
}

void ParticleModule::drawTo(sf::RenderTexture* a_texture)
{
	sf::Sprite s;
	s.setTexture(m_particleTexture);
	
	for (auto p : m_particles)
	{
		p->drawTo(a_texture);

	}
}

float ParticleModule::getRandomFloatinRange(float a_min, float a_max)
{
	return a_min + ((float)std::rand() / (float)RAND_MAX * (a_max- a_min));
}

void ParticleModule::spawnParticles(sf::Vector2f a_spawnPos)
{
	int batchSize = m_batchSize.x + (std::rand() % m_batchSize.y);

	for (int i = 0; i < batchSize; i++)
	{
		if (m_maxNumberOfParticles <= m_particles.size()) return;
		Particle* newParticle = new Particle();

		//Position
		float xOffset = getRandomFloatinRange(m_xSpawnOffset.x, m_xSpawnOffset.y);
		float yOffset = getRandomFloatinRange(m_ySpawnOffset.x, m_ySpawnOffset.y);
		newParticle->m_sprite.setPosition(a_spawnPos.x + xOffset, a_spawnPos.y + yOffset);
		
		//Scale
		float xScale = getRandomFloatinRange(m_initialXSize.x, m_initialXSize.y);
		float yScale = getRandomFloatinRange(m_initialYSize.x, m_initialYSize.y);
		newParticle->m_sprite.setScale(xScale, yScale);

		xScale = getRandomFloatinRange(m_finalXSize.x, m_finalXSize.y);
		yScale = getRandomFloatinRange(m_finalYSize.x, m_finalYSize.y);
		newParticle->m_finalScale = sf::Vector2f(xScale, yScale);

		//TaintColor
		float r = getRandomFloatinRange(m_initialColor.first.r, m_initialColor.second.r);
		float g = getRandomFloatinRange(m_initialColor.first.g, m_initialColor.second.g);
		float b = getRandomFloatinRange(m_initialColor.first.b, m_initialColor.second.b);
		float a = getRandomFloatinRange(m_initialColor.first.a, m_initialColor.second.a);

		newParticle->m_sprite.setColor(sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)a));

		r = getRandomFloatinRange(m_finalColor.first.r, m_finalColor.second.r);
		g = getRandomFloatinRange(m_finalColor.first.g, m_finalColor.second.g);
		b = getRandomFloatinRange(m_finalColor.first.b, m_finalColor.second.b);
		a = getRandomFloatinRange(m_finalColor.first.a, m_finalColor.second.a);

		newParticle->m_finalColor = sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)a);

		//LifeTime
		newParticle->m_remainingLifeTime = getRandomFloatinRange(m_lifeTime.x, m_lifeTime.y);

		//Velocity
		float xVelocity = getRandomFloatinRange(m_initialXVelocity.x, m_initialXVelocity.y);
		float yVelocity = getRandomFloatinRange(m_initialYVelocity.x, m_initialYVelocity.y);
		newParticle->m_currentVelocity = sf::Vector2f(xVelocity, yVelocity);
		
		newParticle->m_sprite.setTexture(m_particleTexture);
		m_particles.push_back(newParticle);
	}
}