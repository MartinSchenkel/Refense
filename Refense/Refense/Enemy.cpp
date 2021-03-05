#include "Enemy.h"
#include "WorldStats.h"

Enemy::Enemy()
{
	m_enemySprite.setFillColor(sf::Color::Transparent);
	m_enemySprite.setOutlineThickness(4.0f);
	m_enemySprite.setOutlineColor(sf::Color::Blue);
	m_enemySprite.setRadius(20);

	int temp = 20 + (std::rand() % 1240);

	m_enemySprite.setPosition((float) temp, 0.0f);

	m_targetXValue = m_enemySprite.getPosition().x;
	m_jumpCountdown = m_jumpInterval.x + (std::rand() % (int)m_jumpInterval.y); 
	m_shootCountdown = m_shootInterval.x + (std::rand() % (int)m_shootInterval.y);
}

Enemy::~Enemy()
{
}

void Enemy::drawTo(sf::RenderTexture* a_texture)
{
	m_jumpParticle.drawTo(a_texture);
	if(!m_isDead) a_texture->draw(m_enemySprite);
}

bool Enemy::move(float a_deltaTime)
{
	m_jumpCountdown -= a_deltaTime;
	if (m_jumpCountdown <= 0.0f)
	{
		if (!m_isJumping) 
		{
			m_isJumping = true;
			m_velocity.y = JUMP_STRENGTH;
			addJumpParticleModule();
		}
		else if (m_velocity.y > 0)
		{
			m_gravityMulitplier = 2.2f;
		}

		m_jumpCountdown = m_jumpInterval.x + (std::rand() % (int) m_jumpInterval.y);
	}

	int moveDir = 0;

	if (std::abs(m_enemySprite.getPosition().x - m_targetXValue) < 20.0f)
	{
		m_targetXValue = 20.0f + (float) (std::rand() % 1240);
	}

	if (m_targetXValue > m_enemySprite.getPosition().x)
	{
		moveDir = 1;
	}
	else moveDir = -1;

	m_velocity.x = moveDir * MOVE_SPEED * a_deltaTime;

	updatePhysics(a_deltaTime);

	m_shootCountdown -= a_deltaTime;
	if (m_shootCountdown <= 0.0f)
	{
		m_shootCountdown = m_shootInterval.x + (std::rand() % (int)m_shootInterval.y);
		return true;
	}
	return false;
}

void Enemy::updatePhysics(float a_deltaTime)
{
	WorldStats& w = WorldStats::get();

	m_jumpParticle.update(a_deltaTime, m_enemySprite.getPosition() + sf::Vector2f(0, 25));

	//Koyote Time
	if (std::abs(m_velocity.y) > 2.0f) m_isJumping = true;

	m_velocity += w.getGravity() * m_gravityMulitplier * 0.01f; //TODO: Fix magic number. DeltaTime caused the jump to be lower if you have less fps. 0.01 is a placeholder value

	if (m_enemySprite.getPosition().x < 0)
	{
		m_velocity.x = 0;
		m_enemySprite.move({ m_enemySprite.getRadius(), 0 });
	}
	else if (m_enemySprite.getPosition().x + 2 * m_enemySprite.getRadius() > 1280)
	{
		m_velocity.x = 0;
		m_enemySprite.move({ -m_enemySprite.getRadius(), 0 });
	}

	m_enemySprite.move(m_velocity);

	for (auto i : w.m_staticWorldObjects)
	{
		float radius = m_enemySprite.getRadius();
		float centerX = m_enemySprite.getPosition().x + radius;
		float centerY = m_enemySprite.getPosition().y + radius;

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

					m_enemySprite.setPosition(m_enemySprite.getPosition().x, top - 2 * radius);
				}
				else
				{
					m_velocity.y = 0;
					m_enemySprite.setPosition(m_enemySprite.getPosition().x, bottom);
				}
			}
			else if (std::abs(distX) < radius)
			{
				if (centerX - radius < left) {
					m_velocity.x = 0;
					m_enemySprite.setPosition(left - 2 * radius, m_enemySprite.getPosition().y);
				}
				else
				{
					m_velocity.x = 0;
					m_enemySprite.setPosition(right, m_enemySprite.getPosition().y);
				}
			}
		}
	}

	//float scaleX = 1 + std::clamp(std::abs(m_velocity.x), 0.0f, 0.5f);
	//float scaleY = 1 + std::clamp(std::abs(m_velocity.y), 0.0f, 0.5f);

	//m_playerSprite.setScale(1, scaleY);
}


void Enemy::addJumpParticleModule()
{
	ParticleModule* jumpModule = new ParticleModule("../Resources/Textures/Particles/cross.png");

	jumpModule->m_gravityType = jumpModule->ENone;
	jumpModule->m_gravity = sf::Vector2f(0.0f, -2.0f);
	jumpModule->m_batchSize = sf::Vector2u(10, 10);
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
