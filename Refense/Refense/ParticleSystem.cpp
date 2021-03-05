#pragma once

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(float a_lifeTime)
{
	m_lifeTime = a_lifeTime;
	m_restLifeTime = a_lifeTime;
}

void ParticleSystem::update(float a_deltaTime, sf::Vector2f a_newPos)
{
	m_position = a_newPos;

	if (m_restLifeTime != 0)
	{
		if (m_restLifeTime <= a_deltaTime)
		{
			m_modules.clear();

			if (m_loops) m_restLifeTime = m_lifeTime;
		}
		else m_restLifeTime -= a_deltaTime;
	}

	// TODO change own position depending on velocity and gravity

	for (auto m : m_modules)
	{
		m->update(a_deltaTime, m_position);
	}
}

void ParticleSystem::drawTo(sf::RenderTexture* a_texture)
{
	for (auto m : m_modules)
	{
		m->drawTo(a_texture);
	}
}