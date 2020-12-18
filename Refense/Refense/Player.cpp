#include "Player.h"
#include "WorldStats.h"

Player::Player()
{
	m_playerSprite.setFillColor(sf::Color::Transparent);
	m_playerSprite.setOutlineThickness(4.0f);
	m_playerSprite.setOutlineColor(sf::Color::Yellow);
	m_playerSprite.setRadius(20);
	m_playerSprite.setPosition(200, 0);
}

Player::~Player()
{
}

void Player::drawTo(sf::RenderWindow &a_window)
{
	a_window.draw(m_playerSprite);

	WorldStats *w = w->getInstance();

	w->drawTo(a_window);
}

void Player::drawTo(sf::RenderTexture* a_texture)
{
	a_texture->draw(m_playerSprite);

	WorldStats *w = w->getInstance();

	w->drawTo(a_texture);
}

void Player::move(sf::Vector2i a_dir, float a_deltaTime)
{
	if (a_dir.y != 0 && !m_isJumping) {
		m_isJumping = true;
		m_velocity.y = JUMP_STRENGTH;
	}
	else if (a_dir.y == 0 && m_isJumping) //key was released
	{
		m_gravityMulitplier = 2.2f;
	}
	else if (m_velocity.y > 0)
	{
		m_gravityMulitplier = 2.2f;
	}

	m_velocity.x = a_dir.x * MOVE_SPEED * a_deltaTime;

	updatePhysics(a_deltaTime);
}

void Player::updatePhysics(float a_deltaTime)
{
	WorldStats *w = w->getInstance();

	//Koyote Time
	if (std::abs(m_velocity.y) > 2.0f) m_isJumping = true;

	m_velocity += w->getGravity() * m_gravityMulitplier * a_deltaTime;

	if (m_playerSprite.getPosition().x < 0)
	{
		m_velocity.x = 0;
		m_playerSprite.move({ m_playerSprite.getRadius(), 0 });
	}
	else if(m_playerSprite.getPosition().x + 2 * m_playerSprite.getRadius() > 1280)
	{
		m_velocity.x = 0;
		m_playerSprite.move({ -m_playerSprite.getRadius(), 0 });
	}

	m_playerSprite.move(m_velocity);

	for (auto i : w->m_staticWorldObjects)
	{
		float radius = m_playerSprite.getRadius();
		float centerX = m_playerSprite.getPosition().x + radius;
		float centerY = m_playerSprite.getPosition().y + radius;

		float left = i.getPosition().x;
		float right = i.getPosition().x + i.getSize().x;
		float top = i.getPosition().y;
		float bottom = i.getPosition().y + i.getSize().y;

		float testX = centerX, testY = centerY;

		if (centerX < left) testX = left;
		else if (centerX > right) testX = right;

		if (centerY < top) testY = top;
		else if (centerY > bottom) testY = bottom;

		float distX = centerX - testX;
		float distY = centerY - testY;
		float distance = std::sqrt((distX * distX) + (distY * distY));

		if (distance <= radius)
		{
			if (std::abs(distY) < radius)
			{
				if (centerY - radius < top) {
					m_velocity.y = 0;
					m_isJumping = false;
					m_gravityMulitplier = 1.0f;

					m_playerSprite.setPosition(m_playerSprite.getPosition().x, top - 2 * radius);
				}
				else 
				{
					m_velocity.y = 0;
					m_playerSprite.setPosition(m_playerSprite.getPosition().x, bottom);
				}
			}
			else if (std::abs(distX) < radius)
			{
				if (centerX - radius < left) {
					m_velocity.x = 0;
					m_playerSprite.setPosition(left - 2 * radius, m_playerSprite.getPosition().y);
				}
				else
				{
					m_velocity.x = 0;
					m_playerSprite.setPosition(right, m_playerSprite.getPosition().y);
				}
			}
		}
	}

	//float scaleX = 1 + std::clamp(std::abs(m_velocity.x), 0.0f, 0.5f);
	//float scaleY = 1 + std::clamp(std::abs(m_velocity.y), 0.0f, 0.5f);

	//m_playerSprite.setScale(1, scaleY);
}
