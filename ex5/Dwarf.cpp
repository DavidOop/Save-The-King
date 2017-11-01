#include "Players.h"
#include "Board.h"

/***********************************************************************
						Dwarf functions
***********************************************************************/
Dwarf::Dwarf(const sf::Sprite & display, const sf::Vector2f & location)
	:Player(display, location)
{
	srand(unsigned int(time(NULL)));
	m_dirction = rand() % 4;  //whet diration the darwf will go to
	m_home = location*(float)IMAGE_SIZE;
}
//==================================================================================
void Dwarf::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, float deltaTime)
{
	if (getLocation() == m_home) //if giant hit the dwarf and the dwarf is back in its location. 
		home(board, players);
	else
		actMove(board, players, deltaTime);//the actuall move of the dwarf
}
//========== find  Tile and move ==========================================================
bool Dwarf::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& factor)
{
	auto temp = m_display;
	temp.move(factor);
	std::vector <std::unique_ptr<StaticTile>> tiles;

	board.getTiles(temp.getGlobalBounds(), tiles);

	if (isProperMove(temp, tiles, players))
		m_display.move(factor);
	else
		return false;

	return true;

}
//------------------------------------------------------------------------
bool Dwarf::isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players)
{
	for (auto& tile : check)
	{
		if (dynamic_cast<Empty*>(tile.get()) == nullptr && dynamic_cast<Key*>(tile.get()) == nullptr)
			return false;
	}

	for (auto & player : players)//run over non static tiles
	{
		if (dynamic_cast<Dwarf*>(player.get()) != nullptr)
			if (m_home == (dynamic_cast<Dwarf*>(player.get())->getHomeLocation()))
				continue;

		//a non static tile that is not the giant
		if (dynamic_cast<Giant*>(player.get()) == nullptr)
			if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
				return false;

		//if stept on the giant the dwarf will go back to its home
		if (dynamic_cast<Giant*>(player.get()) != nullptr)
			if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds())) //אם הוא דרך על ענק
			{
				goHome();
				return false;
			}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
//the actuall move of the dwarf
void Dwarf::actMove(Board & board, const std::vector<std::unique_ptr<Player>>& players, float deltaTime)
{
	for (int i = 0; i < 4; i++)  //every dwarf moves to a different place
	{
		 sf::Vector2f factor = (getDirction() < 2) ? (sf::Vector2f{ 0, deltaTime*DWARF_SPEED*((getDirction() == 0) ? -1 : 1) }): (sf::Vector2f{ deltaTime*DWARF_SPEED*((getDirction() == 2) ? -1 : 1),0 });
	
		if (move(board, players, factor)) //chack if can move
			break;
		else
			setDirction(getDirction() + 1);
	}
}
//------------------------------------------------------------------------------------------
void Dwarf::home(Board & board, const std::vector<std::unique_ptr<Player>>& players)
{
	//if there is a player on the dwarfs home, the dwarf will move to a new loction
	float x = 1;
	auto temp = m_display;
	temp.setPosition(m_home);
	while (true)
	{
		for (int i = 0; i < 4; i++)
		{
			temp.move(sf::Vector2f{ (i<2)?1:((i==3)?x:-x),  (i<2) ?((i == 1) ? x : -x):1 });//what diraction to move

			std::vector <std::unique_ptr<StaticTile>> tiles;
			board.getTiles(temp.getGlobalBounds(), tiles);

			if (isProperMove(temp, tiles, players))
			{
				m_display.setPosition(temp.getPosition());
				return;
			}
		}
		x += 2.f;
	}
}
