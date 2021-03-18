#include "Player.h"
#include "WorldStats.h"

Player::Player()
{
	reset();
}

Player::~Player()
{
}

void Player::reset()
{
	m_health = 3;
	m_playerSprite.setFillColor(sf::Color::Transparent);
	m_playerSprite.setOutlineThickness(4.0f);
	m_playerSprite.setOutlineColor(sf::Color::Yellow);
	m_playerSprite.setRadius(20);
	m_playerSprite.setPosition(200, 0);

	m_velocity = sf::Vector2f(0, 0);
}

void Player::drawTo(sf::RenderTexture* a_texture)
{
	m_jumpParticle.drawTo(a_texture);
	a_texture->draw(m_playerSprite);
}

void Player::move(sf::Vector2i a_dir, float a_deltaTime)
{
	if (a_dir.y != 0 && !m_isJumping) {
		m_isJumping = true;
		m_velocity.y = JUMP_STRENGTH;
		addJumpParticleModule();
		m_soundplayer.playSound(m_soundplayer.EJump);
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
	WorldStats& w = WorldStats::get();

	m_jumpParticle.update(a_deltaTime, m_playerSprite.getPosition() - sf::Vector2f(0, -25));

	//Koyote Time
	if (std::abs(m_velocity.y) > 2.0f) m_isJumping = true;

	m_velocity += w.getGravity() * m_gravityMulitplier * 0.01f; //TODO: Fix magic number. DeltaTime caused the jump to be lower if you have less fps. 0.01 is a placeholder value

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

	for (auto i : w.m_staticWorldObjects)
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


void Player::addJumpParticleModule()
{
	ParticleModule* jumpModule = new ParticleModule("../Resources/Textures/Particles/circle.png"); 
	
	jumpModule->m_gravityType = jumpModule->ENone;
	jumpModule->m_gravity = sf::Vector2f(0.0f, -2.0f);
	jumpModule->m_batchSize = sf::Vector2u(8, 10);
	jumpModule->m_spawnCoolDown = sf::Vector2f(2.0f, 2.0f);
	jumpModule->m_maxNumberOfParticles = 10;
	jumpModule->m_xSpawnOffset = sf::Vector2f(-10, 10);
	jumpModule->m_ySpawnOffset = sf::Vector2f(-5, 5);
	jumpModule->m_finalXSize = sf::Vector2f(0, 0);
	jumpModule->m_finalYSize = sf::Vector2f(0, 0);
	jumpModule->m_lifeTime = sf::Vector2f(0.2f, 0.5f);
	jumpModule->m_initialXVelocity = sf::Vector2f(-50.0f, 50.0f);
	jumpModule->m_initialYVelocity = sf::Vector2f(-2.0f, 2.0f);

	m_jumpParticle.m_modules.push_back(jumpModule);
}
