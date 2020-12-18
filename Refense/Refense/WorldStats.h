#pragma once

#include <SFML\Graphics.hpp>

#include <vector>

class WorldStats {
	static WorldStats *m_instance;
	
	const sf::Vector2f GRAVITY = { 0, 10.0f };

	WorldStats() {
		sf::RectangleShape floor;
		floor.setPosition(4, 600);
		floor.setFillColor(sf::Color::Transparent);
		floor.setOutlineThickness(4);
		floor.setOutlineColor(sf::Color::White);
		floor.setSize( { 1272.0f, 100.0f } );

		m_staticWorldObjects.push_back(floor);

		sf::RectangleShape platform1;
		platform1.setPosition(200, 400);
		platform1.setFillColor(sf::Color::Transparent);
		platform1.setOutlineThickness(4);
		platform1.setOutlineColor(sf::Color::White);
		platform1.setSize({ 200, 50 });

		m_staticWorldObjects.push_back(platform1);

		sf::RectangleShape platform2;
		platform2.setPosition(900, 500);
		platform2.setFillColor(sf::Color::Transparent);
		platform2.setOutlineThickness(4);
		platform2.setOutlineColor(sf::Color::White);
		platform2.setSize({ 200, 50 });

		m_staticWorldObjects.push_back(platform2);

		sf::RectangleShape platform3;
		platform3.setPosition(800, 200);
		platform3.setFillColor(sf::Color::Transparent);
		platform3.setOutlineThickness(4);
		platform3.setOutlineColor(sf::Color::White);
		platform3.setSize({ 200, 50 });

		m_staticWorldObjects.push_back(platform3);
	};


public:

	static WorldStats *getInstance() {
		if (!m_instance)
			m_instance = new WorldStats;
		return m_instance;
	}

	void drawTo(sf::RenderWindow &a_window)
	{
		for(auto i : m_staticWorldObjects)
			a_window.draw(i);
	}


	void drawTo(sf::RenderTexture* a_texture) {
		for (auto i : m_staticWorldObjects)
			a_texture->draw(i);
	}

	std::vector<sf::RectangleShape> m_staticWorldObjects;

	sf::Vector2f getGravity() { return GRAVITY; };
};

WorldStats *WorldStats::m_instance = 0;