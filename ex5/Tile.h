#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Images.h"

const float SPEED = 5;
const float DWARF_SPEED = 200;

class Tile
{
public:
	Tile(const sf::Sprite& display, const sf::Vector2f& location) :m_display(display) {
		m_display.setPosition(location*float(IMAGE_SIZE));
	}
	virtual ~Tile() = 0;

	void operator=(std::unique_ptr<Tile> other) { m_display = other->getDisplay(); }

	virtual void display(sf::RenderWindow& window)const { window.draw(m_display); }
	virtual const sf::Sprite& getDisplay()const { return m_display; }
	const sf::Vector2f& getLocation()const { return m_display.getPosition(); }

	/* set */
	void setEmpty(const sf::Sprite& other) { auto loc = getLocation(); m_display = other; m_display.setPosition(loc); }
	void setLocation(const sf::Vector2f& location) { m_display.setPosition(location); }
	void setDisplay(const sf::Sprite& temp) { m_display = temp; }

protected:
	sf::Sprite m_display;				//the final image
};
//=====================================================================================================
//              class of static tile
//========================================================================================
class StaticTile : public Tile
{
public:
	using Tile::Tile;
	~StaticTile() = 0;
	virtual std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other) = 0;
};
//=================================================================================================
class Fire : public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
//================================================================
class Gate :public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
//================================================================
class Wall :public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
//================================================================
class Key :public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
//================================================================
class Thrown :public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
//================================================================
class Empty :public StaticTile
{
public:
	using  StaticTile::StaticTile;
	std::unique_ptr<StaticTile> makeTile(const std::unique_ptr<StaticTile>& other)override;
};
