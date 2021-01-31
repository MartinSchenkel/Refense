#include "Credits.h"

Credits::Credits()
{
	m_textFont.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_title.setFont(m_textFont);
	m_title.setStyle(sf::Text::Bold);
	m_title.setCharacterSize(64);
	m_title.setPosition(460, 20);
	m_title.setString("Credits");
	m_titleBackDrop.setPosition(m_title.getPosition());
	m_titleBackDrop.setSize(sf::Vector2f(m_title.getGlobalBounds().width, m_title.getGlobalBounds().height));
	m_titleBackDrop.setFillColor(sf::Color(0, 0, 0, 255));

	std::string temp = "Back to Main Menu";
	m_backButton.setButtonText(&temp);
	m_backButton.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_backButton.m_position = sf::Vector2f(100, 650);
	m_backButton.setOnClickVariable(&m_goBack);
	m_buttonBackDrop.setPosition(m_backButton.m_position);
	m_buttonBackDrop.setSize(m_backButton.getSize());
	m_buttonBackDrop.setFillColor(sf::Color(0, 0, 0, 255));

	m_scrollPane.setFont(m_textFont);
	m_scrollPane.setInitialPosition(sf::Vector2f(640, 360));
	m_scrollPane.addText("Idea: Martin Schenkel");
	m_scrollPane.addText("");
	m_scrollPane.addText("");
	m_scrollPane.addText("-Programming-");
	m_scrollPane.addText("");
	m_scrollPane.addText("AI Programming: Martin Schenkel");
	m_scrollPane.addText("Tools Programming: Martin Schenkel");
	m_scrollPane.addText("Graphics Programming: Martin Schenkel");
	m_scrollPane.addText("Engine Programming: Martin Schenkel");
	m_scrollPane.addText("Physics Programming: Martin Schenkel");
	m_scrollPane.addText("Gameplay Programming: Martin Schenkel");
	m_scrollPane.addText("UI Programming: Martin Schenkel");
	m_scrollPane.addText("Animation Programming: Martin Schenkel");
	m_scrollPane.addText("VFX Programming: Martin Schenkel");
	m_scrollPane.addText("");
	m_scrollPane.addText("");
	m_scrollPane.addText("-Design-");
	m_scrollPane.addText("");
	m_scrollPane.addText("AI Design: Martin Schenkel");
	m_scrollPane.addText("Game Design: Martin Schenkel");
	m_scrollPane.addText("UI/UX Design: Martin Schenkel");
	m_scrollPane.addText("Level Design: Martin Schenkel");
	m_scrollPane.addText("Audio Design: Martin Schenkel");
	m_scrollPane.addText("Production: Martin Schenkel");
	m_scrollPane.addText("");
	m_scrollPane.addText("");
	m_scrollPane.addText("-Art-");
	m_scrollPane.addText("");
	m_scrollPane.addText("Character Art: Martin Schenkel");
	m_scrollPane.addText("Environment Art: Martin Schenkel");
	m_scrollPane.addText("UI Art: Martin Schenkel");
	m_scrollPane.addText("Prop Art: Martin Schenkel");
	m_scrollPane.addText("VFX: Martin Schenkel");
	m_scrollPane.addText("Animation: Martin Schenkel");
	m_scrollPane.addText("");
	m_scrollPane.addText(""); 
	m_scrollPane.addText("-Audio-");
	m_scrollPane.addText("");
	m_scrollPane.addText("SFX Audio: Martin Schenkel");
	m_scrollPane.addText("Background Music: Martin Schenkel");
	m_scrollPane.addText("");
	m_scrollPane.addText("");
	m_scrollPane.addText("-External Thanks-");
	m_scrollPane.addText("");
	m_scrollPane.addText("Electric City Font");
	m_scrollPane.addText("creativefabrica.com/designer/weknow/");
	m_scrollPane.addText("");
	m_scrollPane.addText("Unispace Font");
	m_scrollPane.addText("typodermicfonts.com");
	m_scrollPane.addText("");
	m_scrollPane.addText("All Fonts from:");
	m_scrollPane.addText("1001freefonts.com/");
}
void Credits::update(sf::Vector2f a_mousePos, float a_deltaTime)
{
	m_backButton.update(a_mousePos);
	m_scrollPane.update(a_deltaTime);
}
void Credits::drawTo(sf::RenderTexture* a_texture)
{
	m_scrollPane.drawTo(a_texture);
	a_texture->draw(m_buttonBackDrop);
	a_texture->draw(m_titleBackDrop);
	a_texture->draw(m_title);
	m_backButton.drawTo(a_texture);
}
int Credits::shouldTransition()
{
	if (m_goBack)
	{
		m_scrollPane.reset();
		m_goBack = false;
		return 1;
	}
	return 0;
}