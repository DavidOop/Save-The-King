#include "Board.h"
#include <fstream>
#include <istream>
#include <typeinfo>

//----------------------------------------------------------------------------------
void Board::setBoard(std::ifstream& file, const std::vector<sf::Sprite>& images, std::vector<std::unique_ptr<Player>>& players) {
	readBoard(file, images, players);
}
////=========================================================================
//
////======================== read board ==============================================
void Board::readBoard(std::ifstream& file, const std::vector<sf::Sprite>& images, std::vector<std::unique_ptr<Player>>& players) {

	int size;
	std::string line;

	getline(file, line);
	if ((size = std::stoi(line)) == 0)
		exit(0);

	//loop reading from input file
	for (int i = 0; i < size; i++) {
		getline(file, line);
		push(line, players, i, images);
	}

	setBoardSize(sf::Vector2f{ float(m_matrix.size()),float(m_matrix[0].size()) });
}
//========================= push back to matrix ====================================
void Board::push(const std::string& str, std::vector<std::unique_ptr<Player>>&players, int i, const std::vector<sf::Sprite>& images) {

	std::vector< std::unique_ptr<StaticTile >> temp;
	for (size_t j = 0; j < str.length(); j++) {
		temp.push_back(addToBoard(images, players, str[j], sf::Vector2f{ float(j), float(i) }));
	}

	m_matrix.push_back(std::move(temp));
}
//======================== set Board Size ==========================================
void Board::setBoardSize(const sf::Vector2f& boardSize) {

	m_boardSize.x = IMAGE_SIZE*(boardSize.x + 2);
	m_boardSize.y = IMAGE_SIZE*boardSize.y;
}
//======================= display ==================================================
std::unique_ptr<StaticTile> Board::addToBoard(const std::vector<sf::Sprite>& images, std::vector<std::unique_ptr<Player>>&players, char c, const sf::Vector2f& location) {

	switch (c) {
	case 'K':
		players.push_back(std::make_unique<King>(images[KING], location));
		break;
	case 'M':
		players.push_back(std::make_unique<Mage>(images[MAGE], location));
		break;
	case 'T':
		players.push_back(std::make_unique<Thief>(images[THIEF2], location, images[THIEF]));
		break;
	case 'G':
		players.push_back(std::make_unique<Giant>(images[GIANT], location));
		break;
	case '^':
		players.push_back(std::make_unique<Dwarf>(images[DWARF], location));
		break;
	case '*':
		return 	(std::make_unique<Fire>(images[FIRE], location));
	case '#':
		return (std::make_unique<Gate>(images[GATE], location));
	case 'F':
		return (std::make_unique<Key>(images[KEY], location));
	case '@':
		return 	(std::make_unique<Thrown>(images[THROWN], location));
	case '=':
		return (std::make_unique<Wall>(images[rand() % 3 + WALL1], location));
	}

	return (std::make_unique<Empty>(images[EMPTY], location));
}
//======================== draw Board =============================================
void Board::drawBoard(sf::RenderWindow& window) {
	for (auto& tiles : m_matrix)
		draw(window, tiles);
}

//========================================================
const std::unique_ptr<StaticTile>& Board::getTile(const sf::Vector2f & location) const
{
	int i, j;
	i = int(location.x / IMAGE_SIZE);
	j = int(location.y / IMAGE_SIZE);
	return m_matrix[i][j];
}
//---------------------------------------------------------------------------
void Board::getTiles(sf::Rect<float> curr, std::vector<std::unique_ptr<StaticTile>>& tiles) const
{
	for (auto i = 0; i < getBoardSizeCor().x - 2; i++)
		for (auto j = 0; j < getBoardSizeCor().y; j++)
			if (m_matrix[i][j]->getDisplay().getGlobalBounds().intersects(curr)) {
				tiles.push_back(m_matrix[i][j]->makeTile(m_matrix[i][j]));
			}
}
//---------------------------------------------------------------------------
void Board::update(std::vector<std::unique_ptr<StaticTile>>& tiles, const std::string& str)
{
	std::string string;
	for (auto& tile : tiles)
	{
		string = typeid(*tile).name();
		if (string == str)
		{
			auto i = tile->getLocation().x / IMAGE_SIZE / IMAGE_SIZE;
			auto j = tile->getLocation().y / IMAGE_SIZE / IMAGE_SIZE;
			std::unique_ptr<StaticTile> empty = std::make_unique<Empty>(sf::Sprite{}, sf::Vector2f{ i,j });
			std::swap(m_matrix[j][i], empty);
			if (str != "class Fire")
				break;
		}
	}
}
