#include "HUD.h"
#include "WorldStats.h"

HUD::HUD()
{
	m_UIFont.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_scoreUI.setFont(m_UIFont);
	m_scoreUI.setCharacterSize(20.0f);
	m_scoreUI.setPosition(1100, 20);
	m_scoreUI.setString("Score: 100");

	m_healthUITexture.loadFromFile("../Resources/Textures/Particles/temp2.png");

	for (int i = 0; i < 3; i++)
	{
		m_healthUI[i].setTexture(m_healthUITexture);
		m_healthUI[i].setPosition(50 + 20 * i, 20);
	}
}

void HUD::drawTo(sf::RenderWindow& a_window, int a_playerhealth)
{
	std::string scoreText = "Score: ";
	int score = WorldStats::get().m_score;
	scoreText.append(std::to_string(score));

	m_scoreUI.setString(scoreText);

	a_window.draw(m_scoreUI);

	for (int i = 0; i < a_playerhealth; i++)
	{
		a_window.draw(m_healthUI[i]);
	}
	}