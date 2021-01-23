#include "Projectile.h"

Projectile::Projectile(sf::Vector2f a_position)
{
	m_projectileSprite.setPosition(a_position);
	m_projectileSprite.setSize(sf::Vector2f(10, 10));
	m_projectileSprite.setFillColor(sf::Color::Transparent);
	m_projectileSprite.setOutlineThickness(4.0f);
}

bool Projectile::update(float a_deltaTime, Player* a_player, std::vector<Enemy>& a_enemies)
{
	m_projectileSprite.move(m_direction * m_velocity * a_deltaTime);

	if (m_firedFromEnemy)
	{
		if (a_player->getGlobalBounds().intersects(m_projectileSprite.getGlobalBounds()))
		{
			a_player->m_health--;
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

void Projectile::setType(int a_type)
{

	m_type = a_type;

	if (m_type == 1)
		m_projectileSprite.setOutlineColor(sf::Color::Blue);
	else if (m_type == 2)
		m_projectileSprite.setOutlineColor(sf::Color::Red);
	else if (m_type == 3)
		m_projectileSprite.setOutlineColor(sf::Color::Green);
}