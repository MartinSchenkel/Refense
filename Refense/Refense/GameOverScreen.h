#pragma once

#include <SFML\Graphics.hpp>

#include "WorldStats.h"
#include "GameSettings.h"
#include "Button.h"

class GameOverScreen
{
public:
	GameOverScreen()
	{
		GameSettings& gs = GameSettings::get();
		WorldStats& ws = WorldStats::get();

		std::string temp = "Back to Main Menu";
		m_backToMainMenuButton.setButtonText(&temp);
		m_backToMainMenuButton.setColors(
			sf::Color(255, 255, 255, 255),
			sf::Color(125, 125, 125, 255),
			sf::Color(255, 125, 0, 255));
		m_backToMainMenuButton.m_position = sf::Vector2f(100, 650);

		unsigned int fontSize = 20;
		float leftPos = 100.0f;
		float rightPos = 400.0f;

		m_font.loadFromFile("../Resources/Fonts/unispace.ttf");

		m_gameOverText.setString("Game Over!");
		m_gameOverText.setCharacterSize(60);
		m_gameOverText.setPosition(500, 50);
		m_gameOverText.setFillColor(sf::Color::Red);
		m_gameOverText.setFont(m_font);

		m_youDiedText.setString("You died by");
		m_youDiedText.setCharacterSize(fontSize);
		m_youDiedText.setPosition(leftPos, 200);
		m_youDiedText.setFillColor(sf::Color::White);
		m_youDiedText.setFont(m_font);

		m_deathReasonText.setString(ws.m_deathReason);
		m_deathReasonText.setCharacterSize(fontSize);
		m_deathReasonText.setPosition(leftPos + 180, 200);
		m_deathReasonText.setFillColor(sf::Color::Red);
		m_deathReasonText.setFont(m_font);

		m_yourScoreText.setString("Your score was");
		m_yourScoreText.setCharacterSize(fontSize);
		m_yourScoreText.setPosition(leftPos, 300);
		m_yourScoreText.setFillColor(sf::Color::White);
		m_yourScoreText.setFont(m_font);

		m_scoreText.setString(std::to_string(ws.m_score));
		m_scoreText.setCharacterSize(fontSize);
		m_scoreText.setPosition(leftPos + 220, 300);
		m_scoreText.setFillColor(sf::Color::Red);
		m_scoreText.setFont(m_font);

		if (ws.m_score > gs.m_highScore)
		{
			m_yourHighScoreText.setString("You beat your highscore of");
			m_yourHighScoreText.setCharacterSize(fontSize);
			m_yourHighScoreText.setPosition(leftPos, 400);
			m_yourHighScoreText.setFillColor(sf::Color::White);
			m_yourHighScoreText.setFont(m_font);

		}
		else if (ws.m_score == gs.m_highScore)
		{
			m_yourHighScoreText.setString("You matched your highscore of");
			m_yourHighScoreText.setCharacterSize(fontSize);
			m_yourHighScoreText.setPosition(leftPos, 400);
			m_yourHighScoreText.setFillColor(sf::Color::White);
			m_yourHighScoreText.setFont(m_font);
		}
		else
		{
			m_yourHighScoreText.setString("You did not beat your highscore of");
			m_yourHighScoreText.setCharacterSize(fontSize);
			m_yourHighScoreText.setPosition(leftPos, 400);
			m_yourHighScoreText.setFillColor(sf::Color::White);
			m_yourHighScoreText.setFont(m_font);
		}

		m_highScoreText.setString(std::to_string(gs.m_highScore));
		m_highScoreText.setCharacterSize(fontSize);
		m_highScoreText.setPosition(leftPos + 520, 400);
		m_highScoreText.setFillColor(sf::Color::Red);
		m_highScoreText.setFont(m_font);

		if (ws.m_score > gs.m_highScore)
		{
			gs.m_highScore = ws.m_score;
			gs.safeSettings();
		}

		ws.m_score = 0;

	}
	bool update(float a_deltaTime, sf::Vector2f a_mousePos)
	{
		m_duration -= a_deltaTime;

		m_shouldTransition = m_backToMainMenuButton.update(a_mousePos);

		return shouldTransition();
	}
	void drawTo(sf::RenderTexture* a_texture)
	{
		m_backToMainMenuButton.drawTo(a_texture);
		
		a_texture->draw(m_gameOverText);
		a_texture->draw(m_youDiedText);
		a_texture->draw(m_deathReasonText);
		a_texture->draw(m_yourScoreText);
		a_texture->draw(m_scoreText);
		a_texture->draw(m_yourHighScoreText);
		a_texture->draw(m_highScoreText);
	}
	bool shouldTransition()
	{
		return (m_duration <= 0.0f || m_shouldTransition);
	}

private:

	float m_duration = 5.0f;
	bool m_shouldTransition = false;

	Button m_backToMainMenuButton;

	sf::Font m_font;

	sf::Text m_gameOverText;
	sf::Text m_youDiedText;
	sf::Text m_deathReasonText;
	sf::Text m_yourScoreText;
	sf::Text m_scoreText;
	sf::Text m_yourHighScoreText;
	sf::Text m_highScoreText;

};
