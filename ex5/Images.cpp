#include "Images.h"

Images::Images() {

	startImages();

	for (int i = 0; i < Images_t::IMAGE_NUMBER; i++)
		m_image.push_back(sf::Sprite{ m_picTexture[i] });

}
//================================================================
void Images::startImages() {

	m_picTexture[KING].loadFromFile("Images/King.png");
	m_picTexture[MAGE].loadFromFile("Images/Mage.png");
	m_picTexture[GIANT].loadFromFile("Images/Giant.png");
	m_picTexture[THIEF].loadFromFile("Images/Thief.png");
	m_picTexture[THIEF2].loadFromFile("Images/Thief2.png");
	m_picTexture[DWARF].loadFromFile("Images/Dwarf.png");
	m_picTexture[FIRE].loadFromFile("Images/Fire.png");
	m_picTexture[GATE].loadFromFile("Images/Gate.png");
	m_picTexture[KEY].loadFromFile("Images/Key.png");
	m_picTexture[THROWN].loadFromFile("Images/Throne.png");
	m_picTexture[WALL1].loadFromFile("Images/Wall1.jpg");
	m_picTexture[WALL2].loadFromFile("Images/Wall2.jpg");
	m_picTexture[CHOOSE].loadFromFile("Images/choose.jpg");	
	m_picTexture[WALL3].loadFromFile("Images/Wall3.jpg");  //^^ Tiles ^^
	m_picTexture[BACKGROUND1].loadFromFile("Images/Background1.jpg");
	m_picTexture[START1].loadFromFile("Images/Start1.png");
	m_picTexture[HELP1].loadFromFile("Images/Help1.png");
	m_picTexture[CLOSE1].loadFromFile("Images/Close1.png");
	m_picTexture[W_HELP1].loadFromFile("Images/Return1.png");
	m_picTexture[BACKGROUND2].loadFromFile("Images/Background2.PNG");
	m_picTexture[START2].loadFromFile("Images/Start2.png");
	m_picTexture[HELP2].loadFromFile("Images/Help2.png");
	m_picTexture[CLOSE2].loadFromFile("Images/Close2.png");
	m_picTexture[W_HELP2].loadFromFile("Images/Return2.png"); //^^ Menu ^^
	m_picTexture[LOGO].loadFromFile("Images/Logo.jpg");
	m_picTexture[INFO].loadFromFile("Images/Info.jpg");  
	m_picTexture[EMPTY].loadFromFile("Images/Empty.png");  
	m_picTexture[WIN].loadFromFile("Images/Win.jpg"); 
	m_picTexture[LOSE].loadFromFile("Images/Lose.jpg");  
	m_picTexture[LEVEL].loadFromFile("Images/Level.jpg"); 
	m_picTexture[MOVE1].loadFromFile("Images/Move1.jpg");  
	m_picTexture[MOVE2].loadFromFile("Images/Move2.jpg");
	m_picTexture[TIME1].loadFromFile("Images/Time1.jpg");
	m_picTexture[TIME2].loadFromFile("Images/Time2.jpg");
	m_picTexture[BACKGROUND].loadFromFile("Images/Background.jpeg");//^^ infoBar ^^

}