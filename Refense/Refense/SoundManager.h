#pragma once

#include <SFML/Audio.hpp>
#include "GameSettings.h"

class SoundManager
{
public:
	SoundManager(const SoundManager&) = delete;

	enum ESoundEffect
	{
		EMusic,
		EJump,
		EShoot,
		EHealthLost,
		EEnemyDeath,
		EPlayerDeath,
		EPause,
		EButton,
		EReflectFail,
		EReflect
	};

	void setupSounds()
	{
		float musicVolume = GameSettings::get().m_musicVolume * 100.0f;


		m_backgroundMusic = new sf::Music();
		m_backgroundMusic->openFromFile("../Resources/Audio/jump.wav");
		m_backgroundMusic->setVolume(musicVolume);
		m_backgroundMusic->setLoop(true);
		//m_backgroundMusic->play();
		
		m_jumpSound = new sf::SoundBuffer();
		m_jumpSound->loadFromFile("../Resources/Audio/jump.wav");
		m_shootSound = new sf::SoundBuffer();
		m_shootSound->loadFromFile("../Resources/Audio/enemyshoot.wav");
		m_healthLostSound = new sf::SoundBuffer();
		m_healthLostSound->loadFromFile("../Resources/Audio/healthlost.wav");
		m_enemyDeathSound = new sf::SoundBuffer();
		m_enemyDeathSound->loadFromFile("../Resources/Audio/enemydeath.wav");
		m_playerDeathSound = new sf::SoundBuffer();
		m_playerDeathSound->loadFromFile("../Resources/Audio/playerdeath.wav");
		m_pauseSound = new sf::SoundBuffer();
		m_pauseSound->loadFromFile("../Resources/Audio/pause.wav");
		m_buttonSound = new sf::SoundBuffer();
		m_buttonSound->loadFromFile("../Resources/Audio/button.wav");
		m_failedReflectSound = new sf::SoundBuffer();
		m_failedReflectSound->loadFromFile("../Resources/Audio/reflectfail.wav");
		m_reflectSound = new sf::SoundBuffer();
		m_reflectSound->loadFromFile("../Resources/Audio/reflectsuccess.wav");
	}

	void playSound(ESoundEffect type)
	{
		switch (type)
		{
		case(EMusic):

			//m_backgroundMusic->openFromFile("../Resources/Audio/RefenseV2.wav");
			//m_backgroundMusic->setVolume(musicVolume);
			//m_backgroundMusic->setLoop(true);
			//m_backgroundMusic->play();

			return;

			break;
		case(EJump):

			m_player.setBuffer(*m_jumpSound);

			break;
		case(EShoot):

			m_player.setBuffer(*m_shootSound);

			break;
		case(EHealthLost):

			m_player.setBuffer(*m_healthLostSound);

			break;
		case(EEnemyDeath):

			m_player.setBuffer(*m_enemyDeathSound);

			break;
		case(EPlayerDeath):

			m_player.setBuffer(*m_playerDeathSound);

			break;
		case(EPause):

			m_player.setBuffer(*m_pauseSound);

			break;
		case(EButton):

			m_player.setBuffer(*m_buttonSound);

			break;
		case(EReflectFail):

			m_player.setBuffer(*m_failedReflectSound);

			break;
		case(EReflect):

			m_player.setBuffer(*m_reflectSound);

			break;

		default:
			return;
		}

		m_player.setVolume(GameSettings::get().m_sfxVolume * 100.0f);
		m_player.play();
	}

	static SoundManager& get()
	{
		static SoundManager s_Instance;
		return s_Instance;
	}

	sf::Sound m_player;

	sf::Music* m_backgroundMusic = nullptr;

	sf::SoundBuffer* m_jumpSound = nullptr;
	sf::SoundBuffer* m_shootSound = nullptr;
	sf::SoundBuffer* m_healthLostSound = nullptr;
	sf::SoundBuffer* m_enemyDeathSound = nullptr;
	sf::SoundBuffer* m_playerDeathSound = nullptr;
	sf::SoundBuffer* m_pauseSound = nullptr;
	sf::SoundBuffer* m_buttonSound = nullptr;
	sf::SoundBuffer* m_failedReflectSound = nullptr;
	sf::SoundBuffer* m_reflectSound = nullptr;

private:
	SoundManager() {}
}; 
