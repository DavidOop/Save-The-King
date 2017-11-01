#pragma once

#include <SFML/Graphics.hpp>

#include <string>

enum Images_t
{
	KING,
	MAGE,
	GIANT,
	THIEF,
	THIEF2,
	DWARF,
	FIRE,
	GATE,
	KEY,
	THROWN,
	WALL1,
	WALL2,
	WALL3,
	CHOOSE,
	BACKGROUND1,
	START1,
	HELP1,
	CLOSE1,
	W_HELP1,
	BACKGROUND2,
	START2,
	HELP2,
	CLOSE2,
	W_HELP2,
	LOGO,
	INFO,
	EMPTY,
	WIN,
	LOSE,
	LEVEL,
	MOVE1,
	MOVE2,
	TIME1,
	TIME2,
	BACKGROUND,
	IMAGE_NUMBER, //number of images, add an image befor this line 
	IMAGE_SIZE = 35
};

const int H = 440;
const int W = 70;

class Images
{
public:
	Images();
	//void setImage(int x) {  m_image[x].setPosition() }//
	const sf::Sprite& getImage(int x)const { return m_image[x]; }//
	const std::vector<sf::Sprite>& getImages()const { return m_image; }

	/* set */
	void setPosition(const int i, const sf::Vector2f& position) { m_image[i].setPosition(position); }
	void setScale(const int i, const sf::Vector2f& scale) { m_image[i].setScale(scale); }

	//operator
	const sf::Sprite& operator[](int i)const { return m_image[i]; }
	sf::Sprite& operator[](int i) { return m_image[i]; }
private:
	void startImages();

	sf::Texture m_picTexture[Images_t::IMAGE_NUMBER];
	std::vector<sf::Sprite> m_image;
};