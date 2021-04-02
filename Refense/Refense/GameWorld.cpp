#include "GameWorld.h"

#include "WorldStats.h"

GameWorld::GameWorld()
{

}

int GameWorld::update(sf::Vector2f a_mousePos, float a_deltaTime)
{
	m_reasonForDeath = 0;

	m_reflectParticles.update(a_deltaTime, m_player.getPosition());

	spawnEnemies(a_deltaTime);

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

			m_soundplayer.playSound(m_soundplayer.EShoot);
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
						m_projectiles[i].setParticleTexturePath("../Resources/Textures/Particles/circle.png");
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());

						if (a_mousePos.x < m_player.getPosition().x)
							addReflectParticleModule(sf::Color(0, 0, 255, 255), true);
						else
							addReflectParticleModule(sf::Color(0, 0, 255, 255), false);

						m_soundplayer.playSound(m_soundplayer.EReflect);
					}
				}
				else if (m_projectiles[i].getType() == 2)
				{
					if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect2) && !m_reflected2)
					{
						m_reflected2 = true;

						m_projectiles[i].setFiredFromEnemy(false);
						m_projectiles[i].setColor(sf::Color::Yellow);
						m_projectiles[i].setParticleTexturePath("../Resources/Textures/Particles/circle.png");
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());

						if (a_mousePos.x < m_player.getPosition().x)
							addReflectParticleModule(sf::Color(255, 0, 0, 255), true);
						else
							addReflectParticleModule(sf::Color(255, 0, 0, 255), false);


						m_soundplayer.playSound(m_soundplayer.EReflect);
					}
				}
				else if (m_projectiles[i].getType() == 3)
				{
					if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect3) && !m_reflected3)
					{
						m_reflected3 = true;

						m_projectiles[i].setFiredFromEnemy(false);
						m_projectiles[i].setColor(sf::Color::Yellow);
						m_projectiles[i].setParticleTexturePath("../Resources/Textures/Particles/circle.png");
						m_projectiles[i].setDirection(a_mousePos - m_player.getPosition());

						if (a_mousePos.x < m_player.getPosition().x)
							addReflectParticleModule(sf::Color(0, 255, 0, 255), true);
						else
							addReflectParticleModule(sf::Color(0, 255, 0, 255), false);


						m_soundplayer.playSound(m_soundplayer.EReflect);
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

		m_soundplayer.playSound(m_soundplayer.EHealthLost);

		if (a_mousePos.x < m_player.getPosition().x)
			addReflectParticleModule(sf::Color(0, 0, 255, 255), true);
		else
			addReflectParticleModule(sf::Color(0, 0, 255, 255), false);


		m_soundplayer.playSound(m_soundplayer.EReflectFail);
		m_reasonForDeath = 1;
	}
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect2) && !m_reflected2 && !m_reflected2Wrong) //pressed reflect button but it didnt reflect anything
	{
		m_reflected2Wrong = true;
		m_player.m_health--;
		m_soundplayer.playSound(m_soundplayer.EHealthLost);
		if (a_mousePos.x < m_player.getPosition().x)
			addReflectParticleModule(sf::Color(255, 0, 0, 255), true);
		else
			addReflectParticleModule(sf::Color(255, 0, 0, 255), false);


		m_soundplayer.playSound(m_soundplayer.EReflectFail);
		m_reasonForDeath = 1;
	}
	if (sf::Keyboard::isKeyPressed(GAME_SETTINGS.m_reflect3) && !m_reflected3 && !m_reflected3Wrong) //pressed reflect button but it didnt reflect anything
	{
		m_reflected3Wrong = true;
		m_player.m_health--;
		m_soundplayer.playSound(m_soundplayer.EHealthLost);

		if (a_mousePos.x < m_player.getPosition().x)
			addReflectParticleModule(sf::Color(0, 255, 0, 255), true);
		else
			addReflectParticleModule(sf::Color(0, 255, 0, 255), false);
			

		m_soundplayer.playSound(m_soundplayer.EReflectFail);
		m_reasonForDeath = 1;
	}
	if (m_player.m_health <= 0)
	{
		m_soundplayer.playSound(m_soundplayer.EPlayerDeath);

		resetGame();
		return 2;
	}

	return 0;
}


void GameWorld::resetGame()
{
	int rng = rand() % 4;
	WorldStats::get().m_deathReason = m_deathReasonStrings[m_reasonForDeath][rng];

	m_player.reset();
	m_enemies.clear();
	m_projectiles.clear();
}

void GameWorld::draw(sf::RenderTexture* a_renderTexture)
{
	m_reflectParticles.drawTo(a_renderTexture);
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

void GameWorld::drawHUD(sf::RenderWindow& a_window)
{

	m_playerHUD.drawTo(a_window, m_player.m_health);
}

void GameWorld::spawnEnemies(float a_deltaTime)
{
	m_timeSinceLastSpawn += a_deltaTime;

	WorldStats& ws = WorldStats::get();
	if (m_timeSinceLastSpawn >= m_spawnCoolDown)
	{
		int tempscore = (int) (ws.m_score / 100.0f);
		if (tempscore > m_maxEnemies)
		{
			if (m_maxEnemies > m_enemies.size())
			{
				m_timeSinceLastSpawn = 0;
				Enemy e;
				m_enemies.push_back(e);
				return;
			}
		}
		if (tempscore > m_enemies.size())
		{
			m_timeSinceLastSpawn = 0;
			Enemy e;
			m_enemies.push_back(e);
			return;
		}
		if (tempscore == 0 && m_enemies.size() == 0)
		{
			m_timeSinceLastSpawn = 0;
			Enemy e;
			m_enemies.push_back(e);
		}
		
	}
}


void GameWorld::addReflectParticleModule(sf::Color a_color, bool a_left)
{
	ParticleModule* reflectModule = new ParticleModule("../Resources/Textures/Particles/reflectleft.png");
	reflectModule->m_initialXVelocity = sf::Vector2f(-100.0f, -100.0f);
	if (!a_left)
	{
		reflectModule->setTexturePath("../Resources/Textures/Particles/reflectright.png");
		reflectModule->m_initialXVelocity = sf::Vector2f(100.0f, 100.0f);
	}

	reflectModule->m_gravityType = reflectModule->ENone;
	reflectModule->m_batchSize = sf::Vector2u(1, 1);
	reflectModule->m_spawnCoolDown = sf::Vector2f(2.0f, 2.0f);
	reflectModule->m_maxNumberOfParticles = 1;
	reflectModule->m_xSpawnOffset = sf::Vector2f(0, 0);
	reflectModule->m_ySpawnOffset = sf::Vector2f(0, 0);
	reflectModule->m_finalXSize = sf::Vector2f(1.2f, 1.2f);
	reflectModule->m_finalYSize = sf::Vector2f(1.2f, 1.2f);
	reflectModule->m_lifeTime = sf::Vector2f(0.2f, 0.2f);
	reflectModule->m_initialYVelocity = sf::Vector2f(0.0f, 0.0f);
	reflectModule->m_initialColor.first = a_color;
	reflectModule->m_initialColor.second = a_color;
	reflectModule->m_finalColor.first = a_color;
	reflectModule->m_finalColor.second = a_color;

	m_reflectParticles.m_modules.push_back(reflectModule);
}