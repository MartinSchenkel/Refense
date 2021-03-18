#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameSettings 
{
public:
	GameSettings(const GameSettings&) = delete;

	static GameSettings& get()
	{
		static GameSettings s_Instance;
		return s_Instance;
	}

	sf::Keyboard::Key m_up = sf::Keyboard::W;
	sf::Keyboard::Key m_left = sf::Keyboard::A;
	sf::Keyboard::Key m_right = sf::Keyboard::D;

	sf::Keyboard::Key m_reflect1 = sf::Keyboard::E;
	sf::Keyboard::Key m_reflect2 = sf::Keyboard::Q;
	sf::Keyboard::Key m_reflect3 = sf::Keyboard::LShift;

	sf::Keyboard::Key m_pause = sf::Keyboard::Escape;

	float m_musicVolume = 1.0f;
	float m_sfxVolume = 1.0f;

	float m_highScore = 0.0f;

private:
	GameSettings(){}
};
