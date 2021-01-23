#pragma once

#include "Button.h"
#include "Slider.h"
#include "KeyBindInput.h"

class Settings
{
public:
	Settings();
	void update(sf::Vector2f a_mousePos, sf::Keyboard::Key a_keyDown);
	void drawTo(sf::RenderTexture* a_texture);
	int shouldTransition(); //0 = dont transition, 1 = go back

private:

	Button m_backButton;
	Slider m_musicVolumeSlider;
	Slider m_sfxVolumeSlider;

	sf::Font m_textFont;
	sf::Text m_title;

	KeyBindInput m_leftBind;
	KeyBindInput m_rightBind;
	KeyBindInput m_jumpBind;

	KeyBindInput m_reflect1Bind;
	KeyBindInput m_reflect2Bind;
	KeyBindInput m_reflect3Bind;

	KeyBindInput m_pauseBind;

	/* Default Bind
		sf::Keyboard::Key m_up = sf::Keyboard::W;
		sf::Keyboard::Key m_left = sf::Keyboard::A;
		sf::Keyboard::Key m_right = sf::Keyboard::D;

		sf::Keyboard::Key m_reflect1 = sf::Keyboard::E;
		sf::Keyboard::Key m_reflect2 = sf::Keyboard::Q;
		sf::Keyboard::Key m_reflect3 = sf::Keyboard::LShift;

		sf::Keyboard::Key m_pause = sf::Keyboard::Escape;
	*/

	bool m_goBack = false;

};
