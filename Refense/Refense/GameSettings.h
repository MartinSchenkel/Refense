#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <ShlObj.h>
#include <atlstr.h>
#include <filesystem>

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

	bool m_easyMode = true;

	void safeSettings()
	{
		LPWSTR path = NULL;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);

		if (SUCCEEDED(hr))
		{
			printf("\n");
			std::string appdatapath = CW2A(path);

			appdatapath.append("\\MartinsGame\\Refense");

			std::filesystem::path path{ appdatapath };
			path.append("gamesettings.sav");
			if (!std::filesystem::exists(appdatapath))
			{
				std::filesystem::create_directories(path.parent_path());
			}

			std::ofstream outstream(path);

			outstream << m_up << "\n";
			outstream << m_left << "\n";
			outstream << m_right << "\n";
			outstream << m_reflect1 << "\n";
			outstream << m_reflect2 << "\n";
			outstream << m_reflect3 << "\n";
			outstream << m_pause << "\n";
			outstream << m_musicVolume << "\n";
			outstream << m_sfxVolume << "\n";
			outstream << m_highScore << "\n";
			if(m_easyMode)
				outstream << "Easy Mode is On" << "\n";

			outstream.close();

			return;
		}

		printf("AppDataPath not found");
	}

	void loadSettings()
	{
		LPWSTR path = NULL;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);

		if (SUCCEEDED(hr))
		{
			printf("\n");
			std::string appdatapath = CW2A(path);

			appdatapath.append("\\MartinsGame\\Refense\\gamesettings.sav");

			std::ifstream instream;
			instream.open(appdatapath);

			if (instream.is_open()) {  
				std::string tp;
				std::getline(instream, tp);
				m_up = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_left = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_right = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_reflect1 = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_reflect2 = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_reflect3 = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_pause = (sf::Keyboard::Key) std::stoi(tp); //print the data of the string
				std::getline(instream, tp);
				m_musicVolume = std::stof(tp);
				std::getline(instream, tp);
				m_sfxVolume = std::stof(tp);
				std::getline(instream, tp);
				m_highScore = std::stof(tp);
				std::getline(instream, tp);
				if (tp.length() == 0) m_easyMode = false;
				else m_easyMode = true;

				instream.close(); //close the file object.
			}			
		}
	}
	std::string fromKtoS(const sf::Keyboard::Key& k) {
		std::string ret;
		switch (k) {

		case sf::Keyboard::A:

			ret = "A";
			break;
		case sf::Keyboard::B:

			ret = "B";
			break;
		case sf::Keyboard::C:

			ret = "C";
			break;
		case sf::Keyboard::D:

			ret = "D";
			break;
		case sf::Keyboard::E:

			ret = "E";
			break;
		case sf::Keyboard::F:

			ret = "F";
			break;
		case sf::Keyboard::G:

			ret = "G";
			break;
		case sf::Keyboard::H:

			ret = "H";
			break;
		case sf::Keyboard::I:

			ret = "I";
			break;
		case sf::Keyboard::J:

			ret = "J";
			break;
		case sf::Keyboard::K:

			ret = "K";
			break;
		case sf::Keyboard::L:

			ret = "L";
			break;
		case sf::Keyboard::M:

			ret = "M";
			break;
		case sf::Keyboard::N:

			ret = "N";
			break;
		case sf::Keyboard::O:

			ret = "O";
			break;
		case sf::Keyboard::P:

			ret = "P";
			break;
		case sf::Keyboard::Q:

			ret = "Q";
			break;
		case sf::Keyboard::R:

			ret = "R";
			break;
		case sf::Keyboard::S:

			ret = "S";
			break;
		case sf::Keyboard::T:

			ret = "T";
			break;
		case sf::Keyboard::U:

			ret = "U";
			break;
		case sf::Keyboard::V:

			ret = "V";
			break;
		case sf::Keyboard::W:

			ret = "W";
			break;
		case sf::Keyboard::X:

			ret = "X";
			break;
		case sf::Keyboard::Y:

			ret = "Y";
			break;
		case sf::Keyboard::Z:

			ret = "Z";
			break;
		case sf::Keyboard::Num0:

			ret = "Num0";
			break;
		case sf::Keyboard::Num1:

			ret = "Num1";
			break;
		case sf::Keyboard::Num2:

			ret = "Num2";
			break;
		case sf::Keyboard::Num3:

			ret = "Num3";
			break;
		case sf::Keyboard::Num4:

			ret = "Num4";
			break;
		case sf::Keyboard::Num5:

			ret = "Num5";
			break;
		case sf::Keyboard::Num6:

			ret = "Num6";
			break;
		case sf::Keyboard::Num7:

			ret = "Num7";
			break;
		case sf::Keyboard::Num8:

			ret = "Num8";
			break;
		case sf::Keyboard::Num9:

			ret = "Num9";
			break;
		case sf::Keyboard::Escape:

			ret = "Escape";
			break;
		case sf::Keyboard::LControl:

			ret = "LControl";
			break;
		case sf::Keyboard::LShift:

			ret = "LShift";
			break;
		case sf::Keyboard::LAlt:

			ret = "LAlt";
			break;
		case sf::Keyboard::LSystem:

			ret = "LSystem";
			break;
		case sf::Keyboard::RControl:

			ret = "RControl";
			break;
		case sf::Keyboard::RShift:

			ret = "RShift";
			break;
		case sf::Keyboard::RAlt:

			ret = "RAlt";
			break;
		case sf::Keyboard::RSystem:

			ret = "RSystem";
			break;
		case sf::Keyboard::Menu:

			ret = "Menu";
			break;
		case sf::Keyboard::LBracket:

			ret = "LBracket";
			break;
		case sf::Keyboard::RBracket:

			ret = "RBracket";
			break;
		case sf::Keyboard::SemiColon:

			ret = "SemiColon";
			break;
		case sf::Keyboard::Comma:

			ret = "Comma";
			break;
		case sf::Keyboard::Period:

			ret = "Period";
			break;
		case sf::Keyboard::Quote:

			ret = "Quote";
			break;
		case sf::Keyboard::Slash:

			ret = "Slash";
			break;
		case sf::Keyboard::BackSlash:

			ret = "BackSlash";
			break;
		case sf::Keyboard::Tilde:

			ret = "Tilde";
			break;
		case sf::Keyboard::Equal:

			ret = "Equal";
			break;
		case sf::Keyboard::Dash:

			ret = "Dash";
			break;
		case sf::Keyboard::Space:

			ret = "Space";
			break;
		case sf::Keyboard::Return:

			ret = "Return";
			break;
		case sf::Keyboard::BackSpace:

			ret = "BackSpace";
			break;
		case sf::Keyboard::Tab:

			ret = "Tab";
			break;
		case sf::Keyboard::PageUp:

			ret = "PageUp";
			break;
		case sf::Keyboard::PageDown:

			ret = "PageDown";
			break;
		case sf::Keyboard::End:

			ret = "End";
			break;
		case sf::Keyboard::Home:

			ret = "Home";
			break;
		case sf::Keyboard::Insert:

			ret = "Insert";
			break;
		case sf::Keyboard::Delete:

			ret = "Delete";
			break;
		case sf::Keyboard::Add:

			ret = "Add";
			break;
		case sf::Keyboard::Subtract:

			ret = "Subtract";
			break;
		case sf::Keyboard::Multiply:

			ret = "Multiply";
			break;
		case sf::Keyboard::Divide:

			ret = "Divide";
			break;
		case sf::Keyboard::Left:

			ret = "Left";
			break;
		case sf::Keyboard::Right:

			ret = "Right";
			break;
		case sf::Keyboard::Up:

			ret = "Up";
			break;
		case sf::Keyboard::Down:

			ret = "Down";
			break;
		case sf::Keyboard::Numpad0:

			ret = "Numpad0";
			break;
		case sf::Keyboard::Numpad1:

			ret = "Numpad1";
			break;
		case sf::Keyboard::Numpad2:

			ret = "Numpad2";
			break;
		case sf::Keyboard::Numpad3:

			ret = "Numpad3";
			break;
		case sf::Keyboard::Numpad4:

			ret = "Numpad4";
			break;
		case sf::Keyboard::Numpad5:

			ret = "Numpad5";
			break;
		case sf::Keyboard::Numpad6:

			ret = "Numpad6";
			break;
		case sf::Keyboard::Numpad7:

			ret = "Numpad7";
			break;
		case sf::Keyboard::Numpad8:

			ret = "Numpad8";
			break;
		case sf::Keyboard::Numpad9:

			ret = "Numpad9";
			break;
		case sf::Keyboard::F1:

			ret = "F1";
			break;
		case sf::Keyboard::F2:

			ret = "F2";
			break;
		case sf::Keyboard::F3:

			ret = "F3";
			break;
		case sf::Keyboard::F4:

			ret = "F4";
			break;
		case sf::Keyboard::F5:

			ret = "F5";
			break;
		case sf::Keyboard::F6:

			ret = "F6";
			break;
		case sf::Keyboard::F7:

			ret = "F7";
			break;
		case sf::Keyboard::F8:

			ret = "F8";
			break;
		case sf::Keyboard::F9:

			ret = "F9";
			break;
		case sf::Keyboard::F10:

			ret = "F10";
			break;
		case sf::Keyboard::F11:

			ret = "F11";
			break;
		case sf::Keyboard::F12:

			ret = "F12";
			break;
		case sf::Keyboard::F13:

			ret = "F13";
			break;
		case sf::Keyboard::F14:

			ret = "F14";
			break;
		case sf::Keyboard::F15:

			ret = "F15";
			break;
		case sf::Keyboard::Pause:

			ret = "Pause";
			break;
		case sf::Keyboard::KeyCount:

			ret = "KeyCount";
			break;


		default:
			ret = "Unknow";
			break;
		}
		return ret;
	}
private:
	GameSettings(){}
};
