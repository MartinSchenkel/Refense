#include "Settings.h"

#include "GameSettings.h"

Settings::Settings()
{
	GameSettings& k = GameSettings::get();

	m_textFont.loadFromFile("../Resources/Fonts/unispace.ttf");
	m_title.setFont(m_textFont);
	m_title.setStyle(sf::Text::Bold);
	m_title.setCharacterSize(64);
	m_title.setPosition(440, 20);
	m_title.setString("Settings");

	std::string temp = "Back to Main Menu";
	m_backButton.setButtonText(&temp);
	m_backButton.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_backButton.m_position = sf::Vector2f(100, 650);
	m_backButton.setOnClickVariable(&m_goBack);


	m_musicVolumeSlider.setValue(k.m_musicVolume);
	m_musicVolumeSlider.setTitleText("Music Volume");
	m_musicVolumeSlider.setBarSize(sf::Vector2f(250, 10));
	m_musicVolumeSlider.setHeadSize(sf::Vector2f(25, 50));
	m_musicVolumeSlider.setPosition(sf::Vector2f(195, 260));

	m_sfxVolumeSlider.setValue(k.m_sfxVolume);
	m_sfxVolumeSlider.setTitleText("SFX Volume");
	m_sfxVolumeSlider.setBarSize(sf::Vector2f(250, 10));
	m_sfxVolumeSlider.setHeadSize(sf::Vector2f(25, 50));
	m_sfxVolumeSlider.setPosition(sf::Vector2f(835, 260));

	temp = "Move Left:";
	m_leftBind.setDescriptionText(&temp);
	m_leftBind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_leftBind.setDescriptionPosition(sf::Vector2f(300, 400));
	m_leftBind.setBindPosition(sf::Vector2f(500, 400));
	m_leftBind.setBind(k.m_left);

	temp = "Move Right:";
	m_rightBind.setDescriptionText(&temp);
	m_rightBind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_rightBind.setDescriptionPosition(sf::Vector2f(300, 440));
	m_rightBind.setBindPosition(sf::Vector2f(500, 440));
	m_rightBind.setBind(k.m_right);

	temp = "Jump:";
	m_jumpBind.setDescriptionText(&temp);
	m_jumpBind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_jumpBind.setDescriptionPosition(sf::Vector2f(300, 480));
	m_jumpBind.setBindPosition(sf::Vector2f(500, 480));
	m_jumpBind.setBind(k.m_up);

	temp = "Reflect Projectile 1:";
	m_reflect1Bind.setDescriptionText(&temp);
	m_reflect1Bind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_reflect1Bind.setDescriptionPosition(sf::Vector2f(600, 400));
	m_reflect1Bind.setBindPosition(sf::Vector2f(970, 400));
	m_reflect1Bind.setBind(k.m_reflect1);

	temp = "Reflect Projectile 2:";
	m_reflect2Bind.setDescriptionText(&temp);
	m_reflect2Bind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_reflect2Bind.setDescriptionPosition(sf::Vector2f(600, 440));
	m_reflect2Bind.setBindPosition(sf::Vector2f(970, 440));
	m_reflect2Bind.setBind(k.m_reflect2);

	temp = "Reflect Projectile 3:";
	m_reflect3Bind.setDescriptionText(&temp);
	m_reflect3Bind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_reflect3Bind.setDescriptionPosition(sf::Vector2f(600, 480));
	m_reflect3Bind.setBindPosition(sf::Vector2f(970, 480));
	m_reflect3Bind.setBind(k.m_reflect3);

	temp = "Pause Game:";
	m_pauseBind.setDescriptionText(&temp);
	m_pauseBind.setColors(
		sf::Color(255, 255, 255, 255),
		sf::Color(125, 125, 125, 255),
		sf::Color(255, 125, 0, 255));
	m_pauseBind.setDescriptionPosition(sf::Vector2f(300, 560));
	m_pauseBind.setBindPosition(sf::Vector2f(500, 560));
	m_pauseBind.setBind(k.m_pause);
}
void Settings::update(sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown)
{
	m_backButton.update(a_mousePos);
	m_musicVolumeSlider.update(a_mousePos);
	m_sfxVolumeSlider.update(a_mousePos);

	m_leftBind.update(a_mousePos, a_keyDown);
	m_rightBind.update(a_mousePos, a_keyDown);
	m_jumpBind.update(a_mousePos, a_keyDown);
	m_reflect1Bind.update(a_mousePos, a_keyDown);
	m_reflect2Bind.update(a_mousePos, a_keyDown);
	m_reflect3Bind.update(a_mousePos, a_keyDown);
	m_pauseBind.update(a_mousePos, a_keyDown);
}
void Settings::drawTo(sf::RenderTexture* a_texture)
{
	a_texture->draw(m_title);
	m_backButton.drawTo(a_texture);
	m_musicVolumeSlider.drawTo(a_texture);
	m_sfxVolumeSlider.drawTo(a_texture);

	m_leftBind.drawTo(a_texture);
	m_rightBind.drawTo(a_texture);
	m_jumpBind.drawTo(a_texture);
	m_reflect1Bind.drawTo(a_texture);
	m_reflect2Bind.drawTo(a_texture);
	m_reflect3Bind.drawTo(a_texture);
	m_pauseBind.drawTo(a_texture);
}
int Settings::shouldTransition()
{
	if (m_goBack)
	{
		//Save settings
		GameSettings& k = GameSettings::get();

		k.m_up = m_jumpBind.getBind();
		k.m_left = m_leftBind.getBind();
		k.m_right = m_rightBind.getBind();

		k.m_reflect1 = m_reflect1Bind.getBind();
		k.m_reflect2 = m_reflect2Bind.getBind();
		k.m_reflect3 = m_reflect3Bind.getBind();

		k.m_pause = m_pauseBind.getBind();		

		k.m_musicVolume = m_musicVolumeSlider.getValue();
		k.m_sfxVolume = m_sfxVolumeSlider.getValue();

		m_leftBind.reset();
		m_rightBind.reset();
		m_jumpBind.reset();
		m_reflect1Bind.reset();
		m_reflect2Bind.reset();
		m_reflect3Bind.reset();
		m_pauseBind.reset();

		m_goBack = false;

		m_soundManager.playSound(m_soundManager.EMusic);

		return 1;
	}
	return 0;
}