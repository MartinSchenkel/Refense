#include "GameWorld.h"

#include "WorldStats.h"

GameWorld::GameWorld()
{
	Enemy e;
	Enemy e1;
	Enemy e2;
	m_enemies.push_back(e);
	m_enemies.push_back(e1);
	m_enemies.push_back(e2);
}

int GameWorld::update(sf::Vector2f a_mousePos, float a_deltaTime)
{
	//TODO SpawnSystem

	sf::Vector2i moveDir;

	if (!sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect1))
	{
		m_reflected1 = false;
		m_reflected1Wrong = false;
	}
	if (!sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect2))
	{
		m_reflected2 = false;
		m_reflected2Wrong = false;
	}
	if (!sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect3))
	{
		m_reflected3 = false;
		m_reflected3Wrong = false;
	}

	//Up
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_up))
	{
		moveDir.y = -1;
	}
	//Right
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_right))
	{
		moveDir.x = 1;
	}
	//Left
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_left))
	{
		moveDir.x = -1;
	}

	m_player.move(moveDir, a_deltaTime);
	
	for (auto& e : m_enemies)
	{
		if (e.move(a_deltaTime)) //enemy shot
		{
			Projectile p(e.getPosition());
			p.setDirection(m_player.getPosition() - e.getPosition());

			p.setType(1 + std::rand() % 3);

			m_projectiles.push_back(p);
		}
	}

	for (size_t i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i].getFiredFromEnemy())
		{
			sf::Vector2f temp = m_player.getPosition() - m_projectiles[i].getPosition();
			float distanceToPlayer = std::sqrt((temp.x * temp.x) + (temp.y + temp.y));
			if (distanceToPlayer <= m_player.REFLECT_RANGE)
			{
				if (m_projectiles[i].getType() == 1)
				{
					if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect1) && !m_reflected1)
					{
						m_reflected1 = true;

						m_projectiles[i].setFiredFromEnemy(false);
						m_projectiles[i].setColor(sf::Color::Yellow);
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());
					}
				}
				else if (m_projectiles[i].getType() == 2)
				{
					if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect2) && !m_reflected2)
					{
						m_reflected2 = true;

						m_projectiles[i].setFiredFromEnemy(false);
						m_projectiles[i].setColor(sf::Color::Yellow);
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());
					}
				}
				else if (m_projectiles[i].getType() == 3)
				{
					if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect3) && !m_reflected3)
					{
						m_reflected3 = true;

						m_projectiles[i].setFiredFromEnemy(false);
						m_projectiles[i].setColor(sf::Color::Yellow);
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());
					}
				}
			}
		}

		if (m_projectiles[i].update(a_deltaTime, &m_player, m_enemies)) //projectile hit something and should be deleted
		{
			m_projectiles.erase(m_projectiles.begin() + i, m_projectiles.begin() + i + 1);
			i--;
		}
	}

	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect1) && !m_reflected1 && !m_reflected1Wrong) //pressed reflect button but it didnt reflect anything
	{
		m_reflected1Wrong = true;
		m_player.m_health--;
	}
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect2) && !m_reflected2 && !m_reflected2Wrong) //pressed reflect button but it didnt reflect anything
	{
		m_reflected2Wrong = true;
		m_player.m_health--;
	}
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect3) && !m_reflected3 && !m_reflected3Wrong) //pressed reflect button but it didnt reflect anything
	{
		m_reflected3Wrong = true;
		m_player.m_health--;
	}

	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_pause))
	{
		return 1;
	}
	if (m_player.m_health <= 0)
	{
		//TODO RESET GAME
		return 2;
	}

	return 0;
}
void GameWorld::draw(sf::RenderTexture* a_renderTexture)
{

	WorldStats& w = WorldStats::get();

	w.drawTo(a_renderTexture);

	m_player.drawTo(a_renderTexture);
	
	for (auto& e : m_enemies)
	{
		e.drawTo(a_renderTexture);
	}

	for (auto& p : m_projectiles)
	{
		p.draw(a_renderTexture);
	}
}