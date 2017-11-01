#pragma once
#include "Images.h"
#include "Players.h"
#include <memory>
#include <vector>

class Board
{
public:
	Board() {}    //constructor
	~Board() {}

	void drawBoard(sf::RenderWindow& );

	/* get functions */
	const sf::Vector2f& getBoardSize()const { return m_boardSize; }
	const sf::Vector2f& getBoardSizeCor()const { return sf::Vector2f{ m_boardSize.x / 35,m_boardSize.y / 35 }; }
	void getTiles(sf::Rect<float>, std::vector<std::unique_ptr<StaticTile>>& ) const;
	const std::unique_ptr<StaticTile>&  getTile(const sf::Vector2f& location) const;

	/* set functions */
	std::unique_ptr<StaticTile> Board::addToBoard(const std::vector<sf::Sprite>& images, std::vector<std::unique_ptr<Player>>&players, char c, const sf::Vector2f& location);
	void Board::push(const std::string& str, std::vector<std::unique_ptr<Player>>&players, int i, const std::vector<sf::Sprite>& images);
	void Board::update(std::vector<std::unique_ptr<StaticTile>>& tiles, const std::string& str);
	void Board::setBoard(std::ifstream& file, const std::vector<sf::Sprite>& images, std::vector<std::unique_ptr<Player>>& players);//

private:
	void Board::readBoard(std::ifstream& , const std::vector<sf::Sprite>&, std::vector<std::unique_ptr<Player>>& );
	void setBoardSize(const sf::Vector2f&);

	std::vector<std::vector<std::unique_ptr<StaticTile>>> m_matrix;          //The matrix
																	   //
	sf::Vector2f m_boardSize;   //size of board in pixel
};
//===========================================================================

//============================================================================
template<typename T>//this function draws the board for all vectors
void draw(sf::RenderWindow& window, const T & vec) {
	for (auto& tile : vec)
		tile->display(window);
}


