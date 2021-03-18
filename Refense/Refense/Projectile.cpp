#include "Projectile.h"
#include "WorldStats.h"

Projectile::Projectile(sf::Vector2f a_position)
{
	m_projectileSprite.setPosition(a_position);
	m_projectileSprite.setSize(sf::Vector2f(10, 10));
	m_projectileSprite.setFillColor(sf::Color::Transparent);
	m_projectileSprite.setOutlineThickness(4.0f);

	ParticleModule* trailModule = new ParticleModule("../Resources/Textures/Particles/cross.png");

	trailModule->m_gravityType = trailModule->EDirection;
	trailModule->m_gravity = sf::Vector2f(0.0f, -2.0f);
	trailModule->m_batchSize = sf::Vector2u(5, 10);
	trailModule->m_spawnCoolDown = sf::Vector2f(0.0f, 0.001f);
	trailModule->m_maxNumberOfParticles = 40;
	trailModule->m_xSpawnOffset = sf::Vector2f(-5, 5);
	trailModule->m_ySpawnOffset = sf::Vector2f(-5, 5);
	trailModule->m_finalXSize = sf::Vector2f(0, 0);
	trailModule->m_finalYSize = sf::Vector2f(0, 0);
	trailModule->m_lifeTime = sf::Vector2f(0.2f, 0.5f);

	m_trailparticle.m_modules.push_back(trailModule);
}

bool Projectile::update(float a_deltaTime, Player* a_player, std::vector<Enemy>& a_enemies)
{
	m_projectileSprite.move(m_direction * m_velocity * a_deltaTime);

	m_trailparticle.update(a_deltaTime, m_projectileSprite.getPosition());

	if (m_firedFromEnemy)
	{
		if (a_player->getGlobalBounds().intersects(m_projectileSprite.getGlobalBounds()))
		{
			a_player->m_health--;
			SoundManager::get().playSound(SoundManager::get().EHealthLost);
			return true;
		}
	}
	else
	{
		for(size_t i = 0; i < a_enemies.size(); i++)
		{
			if (a_enemies.at(i).getGlobalBounds().intersects(m_projectileSprite.getGlobalBounds()))
			{
				a_enemies.erase(a_enemies.begin() + i, a_enemies.begin() + i + 1);

				SoundManager::get().playSound(SoundManager::get().EEnemyDeath);

				WorldStats::get().m_score += 100;

				return true;
			}
		}
	}

	if (m_projectileSprite.getPosition().x < -20 || m_projectileSprite.getPosition().x > 1300 || m_projectileSprite.getPosition().y < -20 || m_projectileSprite.getPosition().y > 740)
	{
		return true;
	}

	return false;
}
void Projectile::draw(sf::RenderTexture* a_renderTexture)
{
	m_trailparticle.drawTo(a_renderTexture);
	a_renderTexture->draw(m_projectileSprite);
}

void Projectile::setDirection(sf::Vector2f a_dir) 
{
	float length = std::sqrt((a_dir.x * a_dir.x) + (a_dir.y * a_dir.y));
	a_dir.x /= length;
	a_dir.y /= length;

	m_direction = a_dir;
}

void Projectile::setFiredFromEnemy(bool a_firedFromEnemy)
{
	m_firedFromEnemy = a_firedFromEnemy;
}

void Projectile::setColor(sf::Color a_color)
{
	m_projectileSprite.setOutlineColor(a_color);
}
void Projectile::setParticleTexturePath(std::string a_path)
{
	m_trailparticle.m_modules[0]->setTexturePath(a_path);
}

void Projectile::setType(int a_type)
{
	m_type = a_type;

	if (m_type == 1) //cross
	{
		m_projectileSprite.setOutlineColor(sf::Color::Blue);
		m_trailparticle.m_modules[0]->setTexturePath("../Resources/Textures/Particles/cross.png");
	}
	else if (m_type == 2) //square
	{
		m_trailparticle.m_modules[0]->setTexturePath("../Resources/Textures/Particles/square.png");
		m_projectileSprite.setOutlineColor(sf::Color::Red);
	}
	else if (m_type == 3) //triangle
	{
		m_trailparticle.m_modules[0]->setTexturePath("../Resources/Textures/Particles/triangle.png");
		m_projectileSprite.setOutlineColor(sf::Color::Green);
	}

}