#include "Tile.h"

Tile::~Tile() = default;
StaticTile::~StaticTile() = default;

//======================= fire ===================================
std::unique_ptr<StaticTile> Fire::makeTile(const std::unique_ptr<StaticTile>& other) {
	return (std::make_unique<Fire>(other->getDisplay(), other->getDisplay().getPosition()));
}
//======================= Gate ===================================
std::unique_ptr<StaticTile> Gate::makeTile(const std::unique_ptr<StaticTile>& other) {
	return (std::make_unique<Gate>(other->getDisplay(), other->getDisplay().getPosition()));
}
//======================= Wall ===================================

std::unique_ptr<StaticTile> Wall::makeTile(const std::unique_ptr<StaticTile>& other) {
	return std::make_unique<Wall>(other->getDisplay(), other->getDisplay().getPosition());
}
//==================== Key ============================================
std::unique_ptr<StaticTile> Key::makeTile(const std::unique_ptr<StaticTile>& other) {
	return (std::make_unique<Key>(other->getDisplay(), other->getDisplay().getPosition()));
}

//======================== Thrown ========================================

std::unique_ptr<StaticTile> Thrown::makeTile(const std::unique_ptr<StaticTile>& other) {
	return (std::make_unique<Thrown>(other->getDisplay(), other->getDisplay().getPosition()));
}

//======================== Empty ========================================

std::unique_ptr<StaticTile> Empty::makeTile(const std::unique_ptr<StaticTile>& other)
{
	return (std::make_unique<Empty>(other->getDisplay(), other->getDisplay().getPosition()));
}
//================================================================

