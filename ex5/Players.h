#pragma once
#include "Tile.h"
#include <memory>
class Board;

/***********************************************************************
							class Player

					for all non static Tiles
***********************************************************************/
class Player : public Tile
{
public:
	using Tile::Tile;
	virtual ~Player() {}

	bool operator==(std::unique_ptr<Player> other) { return other->getLocation() == getLocation(); }
	virtual bool isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) = 0;

};
/***********************************************************************
							class UserPlayer

			for players hwo are controlled by the user
***********************************************************************/
class UserPlayer : public Player
{
public:
	using Player::Player;
	virtual ~UserPlayer() = 0;

	/* set */
	void setSelected(bool select) { m_selected = select; }

	virtual bool move(Board &board, const std::vector<std::unique_ptr<Player>>& , const sf::Vector2f& , sf::Sprite &) = 0;

protected:
	bool m_selected = false;
};
/*********************************************************************************************************
								class King

**********************************************************************************************************/
class King :public UserPlayer
{
public:
	King(const sf::Sprite& display, const sf::Vector2f& location) :UserPlayer(display, location) { setSelected(true); }
	~King() {}
	bool isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) override;
	bool move(Board &board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& location, sf::Sprite &choose) override;
	bool getWin() { return m_win; }

private:
	bool m_win = false;
};


/*********************************************************************************************************
								class Mage

**********************************************************************************************************/
class Mage :public UserPlayer
{
public:
	using UserPlayer::UserPlayer;
	~Mage() {}
	bool isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) override;
	bool move(Board &board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& location, sf::Sprite &choose) override;
};

/*********************************************************************************************************
								class Thief

**********************************************************************************************************/
class Thief :public UserPlayer
{
public:
	Thief(const sf::Sprite& , const sf::Vector2f& , const sf::Sprite& );
	~Thief() {}
	bool isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) override;
	bool move(Board &board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& location, sf::Sprite &choose) override;
	void display(sf::RenderWindow& window)const override;

private:
	bool m_key = false;
	sf::Sprite m_display2;
};

/*********************************************************************************************************
							class Giant

**********************************************************************************************************/
class Giant :public UserPlayer
{
public:
	using UserPlayer::UserPlayer;
	~Giant() {}
	bool isProperMove(const sf::Sprite& , const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) override;
	bool move(Board &, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& location, sf::Sprite &choose) override;
};

/*********************************************************************************************************
								class Dwarf

**********************************************************************************************************/
class Dwarf :public Player
{
public:
	Dwarf(const sf::Sprite& , const sf::Vector2f& );
	~Dwarf() {}

	int getDirction() const { return m_dirction; }
	const sf::Vector2f& getHomeLocation()const { return m_home; }

	bool isProperMove(const sf::Sprite& curr, const std::vector<std::unique_ptr<StaticTile>> & check, const std::vector<std::unique_ptr<Player>>& players) override;
	void move(Board &board, const std::vector<std::unique_ptr<Player>>& players, float deltaTime);
	void setDirction(int dirction) { m_dirction = dirction % 4; }
	void Dwarf::actMove(Board & board, const std::vector<std::unique_ptr<Player>>& players, float deltaTime);
	void home(Board & board, const std::vector<std::unique_ptr<Player>>& players);
	void goHome() { m_display.setPosition(m_home); }


private:
	bool move(Board &board, const std::vector<std::unique_ptr<Player>>& players, const sf::Vector2f& location);
	
	sf::Vector2f m_home;
	int m_dirction; //0-up; 1-down; 2-right; 3-left;
};
