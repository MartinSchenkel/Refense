#pragma once

#include <SFML/Graphics.hpp>

class KeyBindings {
	static KeyBindings *m_instance;

public:
	static KeyBindings *getInstance() {
		if (!m_instance)
			m_instance = new KeyBindings;
		return m_instance;
	}

	sf::Keyboard::Key m_up = sf::Keyboard::W;
	sf::Keyboard::Key m_left = sf::Keyboard::A;
	sf::Keyboard::Key m_right = sf::Keyboard::D;

	sf::Keyboard::Key m_reflect1 = sf::Keyboard::E;
	sf::Keyboard::Key m_reflect2 = sf::Keyboard::Q;
	sf::Keyboard::Key m_reflect3 = sf::Keyboard::LShift;

	sf::Keyboard::Key m_pause = sf::Keyboard::Escape;

};
KeyBindings *KeyBindings::m_instance = 0;
