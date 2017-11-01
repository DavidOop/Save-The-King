#pragma once

#include "Board.h"
#include "Controller.h"
#include "InfBar.h"


class Stage
{
public:
	Stage(std::ifstream& file, const std::vector<sf::Sprite>&, const sf::Font&,int);
	~Stage() {}

	bool run(sf::RenderWindow&);
	bool keyPressed(sf::Event event);
	void mousebutton(sf::Event event);
	bool win();


private:
	void setInfoBar(const std::vector<sf::Sprite>&, const sf::Font&, int);
	void setCelected(const std::vector<sf::Sprite>&);
	void moveDwarf(float);
	bool timeAndMoveLimit(sf::Clock&,float&);
	bool doEvent(sf::RenderWindow&);

	Board m_board;
	std::vector <std::unique_ptr<Player>> m_players;  //user players and dwarfs
	std::vector<std::unique_ptr<Bar>> m_bar;  //informtion of level number, time limit, move limit
	sf::Sprite m_choose;

};
