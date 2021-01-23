#pragma once

#include <SFML\Graphics.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy();

	void drawTo(sf::RenderTexture* a_texture);
	bool move(float a_deltaTime); //return true if it should spawn a projectile
	void updatePhysics(float a_deltaTime);

	sf::Vector2f getPosition() { return m_enemySprite.getPosition(); }
	sf::FloatRect getGlobalBounds() { return m_enemySprite.getGlobalBounds(); }

	float m_gravityMulitplier = 1.0f;
	bool m_isDead = false;
private:

	sf::Vector2f m_velocity;

	float m_targetXValue;

	bool m_isJumping = false;

	float MOVE_SPEED = 200;
	float JUMP_STRENGTH = -8;

	float m_jumpCountdown = 0.0f;
	sf::Vector2f m_jumpInterval = sf::Vector2f(1.0f, 2.0f); //x = min time, y = max time

	float m_shootCountdown = 0.0f;
	sf::Vector2f m_shootInterval = sf::Vector2f(1.0f, 4.0f); //x = min time, y = max time

	sf::CircleShape m_enemySprite;
};