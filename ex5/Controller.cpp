
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "Controller.h"
#include "Stage.h"
#include <Windows.h>

#define GAME_OVER -1
#define START_GAME 1

//====================== main function =====================================================
int main() {

	auto controller = std::make_unique<Controller>();
	controller->run();

	return 0;
}
/*****************************************************************************************
				basic Controller functions
**********************************************************************************************/
//----------------------------- the font ----------------------------------------------------
std::string getWinDirName()
{

	size_t envSize;
	std::string winDirName(1, ' ');
	auto ret = getenv_s(&envSize, &winDirName[0], winDirName.size(), "WINDIR");
	winDirName.resize(envSize);
	ret = getenv_s(&envSize, &winDirName[0], winDirName.size(), "WINDIR");
	winDirName.resize(envSize - 1); // remove the null-terminator
	return winDirName;
}
//===================== constructor ===================================
Controller::Controller() {

	// font load From File for text
	std::string fontFileName = getWinDirName();
	fontFileName += "/fonts/Arial.ttf";
	m_font.loadFromFile(fontFileName);

	setMenu();
	makeMenu();

}
/************************************************************************
					Controller running functions

************************************************************************/
//=======================================================================
void menuWindow(sf::RenderWindow& window) {
	window.create(sf::VideoMode{ sf::VideoMode::getDesktopMode().width / 2u,
		sf::VideoMode::getDesktopMode().height / 2u }, "Save The King", sf::Style::Close);
}
//========================= run =====================================
void Controller::run() {

	sf::RenderWindow window;
	menuWindow(window);

	//for the drawMouse
	window.setJoystickThreshold(10000);

	// play music 
	backgroundMusic();

	// Menu window
	MenuEvents(window); //draw menu window and get events

}
//======================== while window is open =================================
void Controller::MenuEvents(sf::RenderWindow& window) {

	while (window.isOpen())
	{
		events(window);  //get event from user
		if (static_cast<Start*>(m_Menus[START_GAME].get())->getStartGame())
			if (play(window))//if game is over (no levels left)
				return;

		window.clear();
		updateHelpMode(m_Menus); //if user pressed "Help"
		draw(window, m_Menus);
		window.display();
	}
}
//========================= start playing ====================================
//if user pressed "Start"
bool Controller::play(sf::RenderWindow& window) {

	static int level = 1;
	Stage stage{ m_file, m_images.getImages(), m_font,level };// = dynamic_cast<Stage*>(controller);
	bool didWin = stage.run(window); //run current level
	++level;

	//when the level is over resize the window to half screen
	menuWindow(window);
	endLevelScreen(window, didWin);

	if (!didWin) {  //if didnt win will start from first level
		m_file.seekg(0, m_file.beg);
		level = 1;
	}

	if (m_file.peek() == '0')//if no levels are left
		return true;

	//sets the start boolean to be false
	static_cast<Start*>(m_Menus[START_GAME].get())->setStartGame();
	backgroundMusic();

	//return game isint over;
	return false;
}
//======================= The events of menu screen ===================================
void Controller::events(sf::RenderWindow& window) {

	sf::Event event;
	window.pollEvent(event);

	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::MouseButtonPressed:
		mouseEventButton(m_Menus, window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), true);
		break;
	case sf::Event::MouseMoved:
		mouseEventButton(m_Menus, window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }), false);
		break;
	}

}
//==================== end level ==============================
void Controller::endLevelScreen(sf::RenderWindow& window, bool ifwon) {
	window.draw((ifwon) ? m_images[WIN] : m_images[LOSE]); //what image to display
	m_music.openFromFile((ifwon) ? "Music\\win.wav" : "Music\\lose.wav"); //type of music to play
	m_music.setLoop(false);
	m_music.play();
	window.display();
	Sleep(3000);
}

//==================== music play ===================================
void Controller::backgroundMusic() {
	m_music.openFromFile("Music\\game.wav");
	m_music.setLoop(true);
	m_music.play();
}
//========================================================================================

//======================== add menu screen to vector ===========================================
void Controller::makeMenu() {

	//puts Menus for opnning screen in a vector
	m_Menus.push_back(std::make_unique<Background>(m_images[BACKGROUND1], m_images[BACKGROUND2]));
	m_Menus.push_back(std::make_unique<Start>(m_images[START1], m_images[START2]));
	m_Menus.push_back(std::make_unique<Close>(m_images[CLOSE1], m_images[CLOSE2]));
	m_Menus.push_back(std::make_unique<Help>(m_images[HELP1], m_images[HELP2]));
	m_Menus.push_back(std::make_unique<HelpWindow>(m_images[W_HELP1], m_images[W_HELP2])); // help screen
}
//================================================================================
void Controller::setMenu() {
	//this function sets the menu buttons in there right location on the screen
	
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	for (int i = START1, j = 4; i < START1 + 3; i++, j++) {
		m_images.setPosition(i, (sf::Vector2f{ (float)((desktopMode.width / 2u) - 440) / 2,(float)(((desktopMode.height / 2u) - 70) / 6)*j }));
		m_images.setPosition(i + 5, (m_images[i].getPosition()));
	}

	m_images.setPosition(W_HELP1, sf::Vector2f{ ((float)((desktopMode.width / 2u) - 200) / 2), m_images[CLOSE1].getPosition().y });
	m_images.setPosition(W_HELP2, m_images[W_HELP1].getPosition());

	m_images.setScale(BACKGROUND1, sf::Vector2f{ (float)(double(desktopMode.width / 2) / 560),(float)(double(desktopMode.height / 2) / 280) });
	m_images.setScale(BACKGROUND2, sf::Vector2f{ (float)(double(desktopMode.width / 2) / 960), (float)(double(desktopMode.height / 2) / 540) });
}