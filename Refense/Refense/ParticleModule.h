#pragma once

#include "SFML/Graphics.hpp"
#include "Particle.h"

#include <vector>

class ParticleModule
{
public:
	enum EGravityType {
		ENone,
		EDirection,
		EToPoint,
		EAwayFromPoint
	};


	ParticleModule(std::string a_path);

	void update(float a_deltaTime, sf::Vector2f a_systemPosition);
	void drawTo(sf::RenderTexture* a_texture);
	void setTexturePath(std::string a_path);

	std::string m_texturepath = "../Resources/Textures/Particles/triangle.png";
	sf::Texture m_particleTexture;

	std::vector<Particle*> m_particles;
	int m_maxNumberOfParticles = 60;

	sf::Vector2f m_offset = sf::Vector2f(0, 0); //Offset from the center of the system
	sf::Vector2u m_batchSize = sf::Vector2u(60, 60); //Minimum Batch Size and Maximum Batch Size when particles spawn
	sf::Vector2f m_spawnCoolDown = sf::Vector2f(0.01f, 0.02f); //Minimum and maximum cooldown between spawns
	sf::Vector2f m_lifeTime = sf::Vector2f(1, 2); //min and max lifetime of particles
	bool loops = true;

	sf::Vector2f m_xSpawnOffset = sf::Vector2f(-50, 50);
	sf::Vector2f m_ySpawnOffset = sf::Vector2f(-50, 50);

	std::pair<sf::Color, sf::Color> m_initialColor = std::make_pair<sf::Color, sf::Color>(sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
	std::pair<sf::Color, sf::Color> m_finalColor = std::make_pair<sf::Color, sf::Color>(sf::Color(80, 80, 80, 80), sf::Color(80, 80, 80, 255));

	sf::Vector2f m_initialXSize = sf::Vector2f(0.7f, 1.3f);
	sf::Vector2f m_initialYSize = sf::Vector2f(0.7f, 1.4f);
	sf::Vector2f m_finalXSize = sf::Vector2f(0.2f, 0.4f);
	sf::Vector2f m_finalYSize = sf::Vector2f(0.2f, 0.4f);

	sf::Vector2f m_initialXVelocity = sf::Vector2f(-10, 10);
	sf::Vector2f m_initialYVelocity = sf::Vector2f(-10, 10);

	EGravityType m_gravityType = ENone;
	sf::Vector2f m_gravity = sf::Vector2f(100,0); //If directional gravity type this is the direction and force applied, else x = force
	sf::Vector2f m_gravityPoint = sf::Vector2f(0, 0); // The point that it should be forced towards or away from if that is the desired gravity effect

private:
	void spawnParticles(sf::Vector2f a_spawnPos);
	float getRandomFloatinRange(float a_min, float a_max);

	float m_currentSpawnCoolDown;
};