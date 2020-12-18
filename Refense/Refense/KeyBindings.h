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
	sf::Keyboard::Key m_down = sf::Keyboard::S;
	sf::Keyboard::Key m_left = sf::Keyboard::A;
	sf::Keyboard::Key m_right = sf::Keyboard::D;

	sf::Keyboard::Key m_reflect1;
	sf::Keyboard::Key m_reflect2;
	sf::Keyboard::Key m_reflect3;
};

KeyBindings *KeyBindings::m_instance = 0;