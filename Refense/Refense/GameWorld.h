#pragma once

#include "SFML/Graphics.hpp"
#include "GameSettings.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "ParticleSystem.h"

class GameWorld
{
public:
	GameWorld();

	int update(sf::Vector2f a_mousePos, float a_deltaTime); //0 = dont transition, 1 = pause game, 2 = end game
	void draw(sf::RenderTexture* a_renderTexture);

private:
	void addReflectParticleModule(sf::Color a_color, bool a_left);

	const GameSettings& GAME_SETTINGS = GameSettings::get();
	
	void spawnEnemies(float a_deltaTime);

	int m_maxEnemies = 3;
	float m_spawnCoolDown = 1.0f;
	float m_timeSinceLastSpawn = 0.0f;

	Player m_player;
	std::vector<Enemy> m_enemies;
	std::vector<Projectile> m_projectiles;

	bool m_reflected1 = false, m_reflected2 = false, m_reflected3 = false;
	bool m_reflected1Wrong = false, m_reflected2Wrong = false, m_reflected3Wrong = false;

	ParticleSystem m_reflectParticles = ParticleSystem(2.0f);
};
