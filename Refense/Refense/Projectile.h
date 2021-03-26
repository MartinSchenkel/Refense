#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Enemy.h"
#include "ParticleSystem.h"

class Projectile
{
public:

	Projectile(sf::Vector2f a_position);

	bool update(float a_deltaTime, Player* a_player, std::vector<Enemy>& a_enemies); //if true delete
	void draw(sf::RenderTexture* a_renderTexture);
	void setDirection(sf::Vector2f a_dir);
	bool getFiredFromEnemy() { return m_firedFromEnemy; }
	void setFiredFromEnemy(bool a_firedFromEnemy);
	void setColor(sf::Color a_color);
	void setParticleTexturePath(std::string a_path);
	sf::Vector2f getPosition() { return m_projectileSprite.getPosition(); }

	int getType() { return m_type; }
	void setType(int a_type);

private:

	sf::Font m_tooltipfont;
	sf::Text m_tooltip;
	
	bool m_firedFromEnemy = true;

	sf::Vector2f m_direction;
	float m_velocity = 400.0f;

	sf::RectangleShape m_projectileSprite;

	int m_type = 1;

	ParticleSystem m_trailparticle;
};