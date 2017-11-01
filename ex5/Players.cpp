#include "Players.h"
#include "Board.h"


UserPlayer::~UserPlayer() = default;
/***********************************************************************
								King functions
***********************************************************************/
//========== find  Tile and move ==========================================================
bool King::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f & factor, sf::Sprite &choose)
{
	if (!m_selected)  //if the king was selected
		return false;

	//the temp king first moves and if he moves ok the king himself will move
	auto temp = m_display; 
	temp.move(factor);
	std::vector <std::unique_ptr<StaticTile>> tiles;//the tiles on the board ho are in found in the path

	board.getTiles(temp.getGlobalBounds(), tiles);

	if (isProperMove(temp, tiles, players))
	{
		m_display.move(factor);
		choose.move(factor);
	}
	else
		return false;

	board.update(tiles, "class King");//if on throne earse throne from board

	return true;
}
//------------------------------------------------------------------------
bool King::isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players)
{
	for (auto& tile : check)//run over static tiles and check
	{
		if (dynamic_cast<Empty*>(tile.get()) == nullptr && dynamic_cast<Thrown*>(tile.get()) == nullptr && dynamic_cast<Key*>(tile.get()) == nullptr)
			return false;

		if (dynamic_cast<Thrown*>(tile.get()) != nullptr)
			m_win = true;
	}

	for (auto & player : players)//run over non static tiles
		if (getLocation() == player->getLocation())
			continue;
		else if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
			return false;

	return true;
}

/***********************************************************************
											Mage functions
***********************************************************************/
//========== find  Tile and move ==========================================================
bool Mage::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f & factor, sf::Sprite &choose)
{
	if (!m_selected)//if the mage was selected
		return false;

	//the temp mage first moves and if he moves ok the mage himself will move
	auto temp = m_display;
	temp.move(factor);
	std::vector <std::unique_ptr<StaticTile>> tiles;//the tiles on the board ho are in found in the path

	board.getTiles(temp.getGlobalBounds(), tiles);

	if (isProperMove(temp, tiles, players))
	{
		m_display.move(factor);
		choose.move(factor);
	}
	else
		return false;

	board.update(tiles, "class Fire");//if on fire, earse fire from board

	return true;
}
//------------------------------------------------------------------------
bool Mage::isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players)
{
	for (auto& tile : check)//run over static tiles and check
		if (dynamic_cast<Empty*>(tile.get()) == nullptr && dynamic_cast<Fire*>(tile.get()) == nullptr && dynamic_cast<Key*>(tile.get()) == nullptr)
			return false;

	for (auto & player : players)//run over non static tiles
	{
		if (getLocation() == player->getLocation())
			continue;
		else if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
			return false;
	}

	return true;
}

Thief::Thief(const sf::Sprite& display, const sf::Vector2f& location, const sf::Sprite& display2)
	:UserPlayer(display, location), m_display2(display2) {
	setSelected(false);
	m_display2.setPosition(m_display.getPosition());
}
//========== find  Tile and move ==========================================================
bool Thief::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f & factor, sf::Sprite &choose)
{
	if (!m_selected)
		return false;

	//the temp mage first moves and if he moves ok the mage himself will move
	bool tile = m_key;
	auto temp = m_display;
	temp.move(factor);
	std::vector <std::unique_ptr<StaticTile>> tiles;

	board.getTiles(temp.getGlobalBounds(), tiles);

	if (isProperMove(temp, tiles, players))
	{
		m_display.move(factor);
		choose.move(factor);
	}
	else
	{
		m_key = tile;
		return false;
	}

	board.update(tiles, (tile) ? "class Gate" : "class Key");//if on gate or on key earse from the board
	m_display2.setPosition(m_display.getPosition());

	return true;
}
//------------------------------------------------------------------------
bool Thief::isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players)
{
	for (auto& tile : check)//run over static tiles
	{
		if (dynamic_cast<Empty*>(tile.get()) == nullptr && dynamic_cast<Key*>(tile.get()) == nullptr && dynamic_cast<Gate*>(tile.get()) == nullptr)
			return false;

		if (dynamic_cast<Gate*>(tile.get()) != nullptr)
			if (!m_key)
				return false;
			else
				m_key = false;

		if (dynamic_cast<Key*>(tile.get()) != nullptr)
			m_key = true;
	}

	for (auto & player : players)//run over non static tiles
		if (getLocation() == player->getLocation())
			continue;
		else if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
			return false;

	return true;
}
//-------------------------------------------------------------------------
void Thief::display(sf::RenderWindow& window)const {
	window.draw((m_key) ? m_display : m_display2);
}
/*********************************************************************************************************
												Giant functions
**************************************************************************************************************/
//=============================== find  Tile and move ==========================================================
bool Giant::move(Board & board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f & factor, sf::Sprite &choose)
{
	if (!m_selected)
		return false;

	//the temp mage first moves and if he moves ok the mage himself will move
	auto temp = m_display;
	temp.move(factor);
	std::vector <std::unique_ptr<StaticTile>> tiles;

	board.getTiles(temp.getGlobalBounds(), tiles);

	if (isProperMove(temp, tiles, players))
	{
		m_display.move(factor);
		choose.move(factor);
	}
	else
		return false;

	return true;
}
//------------------------------------------------------------------------
bool Giant::isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players)
{
	for (auto& tile : check) {//run over static tiles
		if (dynamic_cast<Empty*>(tile.get()) == nullptr && dynamic_cast<Key*>(tile.get()) == nullptr)
			return false;
	}

	for (auto & player : players)//run over non static tiles
	{
		if (getLocation() == player->getLocation())
			continue;

		if (dynamic_cast<Dwarf*>(player.get()) == nullptr)
			if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
				return false;
			else;
		else
			if (player->getDisplay().getGlobalBounds().intersects(curr.getGlobalBounds()))
				(dynamic_cast<Dwarf*>(player.get())->goHome());
	}

	return true;
}


