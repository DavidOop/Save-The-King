#pragma once
#include "Images.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include <SFML/Audio.hpp>

//===========================================
class Controller
{
public:
	Controller();
	virtual ~Controller() {}

	void run();
	void MenuEvents(sf::RenderWindow&);
	void events(sf::RenderWindow&);
	bool play(sf::RenderWindow&);
	
	std::ifstream& getFile() { return m_file; }
	void endLevelScreen(sf::RenderWindow&, bool);
	void backgroundMusic();

private:
	void makeMenu(); //put images in Group
	void setMenu();  //not in use

	sf::Font m_font;
	std::ifstream m_file{ R"(level.txt)" }; //levels
	Images m_images;   //loads from file and saves in a vector of Sprite
	std::vector<std::unique_ptr<Menu>> m_Menus; //display background and menu
	sf::Music m_music;
};
