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

				instream.close(); //close the file object.
			}			
		}
	}

private:
	GameSettings(){}
};
