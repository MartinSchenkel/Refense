#pragma once

#include <SFML\Graphics.hpp>

class Player 
{
public:
	Player();
	~Player();

	void drawTo(sf::RenderTexture* a_texture);
	void move(sf::Vector2i a_dir, float a_deltaTime);
	void updatePhysics(float a_deltaTime);

	sf::Vector2f getPosition() { return m_playerSprite.getPosition(); }
	sf::FloatRect getGlobalBounds() { return m_playerSprite.getGlobalBounds(); }

	float m_gravityMulitplier = 1.0f;

	int m_health = 3;

	const float REFLECT_RANGE = 200;

private:

	sf::Vector2f m_velocity;

	bool m_isJumping = false;

	const float MOVE_SPEED= 500;
	const float JUMP_STRENGTH = -8;

	sf::CircleShape m_playerSprite;
};