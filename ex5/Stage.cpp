#include "Stage.h"
const int MOVE = 2;
const int TIME = 3;


//========================== constructor =================================================================
Stage::Stage(std::ifstream& file, const std::vector<sf::Sprite>& images, const sf::Font& font, int level)
{
	m_board.setBoard(file, images, m_players);   //setd the board and static tile's
	setInfoBar(images, font, level);
	setCelected(images);
}
//***************** /***************************** information *********************/	****************************
void Stage::setInfoBar(const std::vector<sf::Sprite>& images, const sf::Font& font, int level) {
	srand(unsigned int(time(NULL)));
	bool move = bool(rand() % 2);				 //random if there is move limit
	bool time = (move) ? bool(rand() % 2) : true;    //random if there is time limit

	m_bar.push_back(std::make_unique<Logo>(images[BACKGROUND], sf::Vector2f{ 0,0 }, sf::Vector2f{ float(double(m_board.getBoardSize().y / 3264)),float(double(m_board.getBoardSize().x / 2448)) }));
	m_bar.push_back(std::make_unique<Level>(images[LEVEL], sf::Vector2f{ 0,float(m_board.getBoardSize().x - IMAGE_SIZE*2) }, font, level));
	m_bar.push_back(std::make_unique<MoveInfo>(images[(move) ? MOVE2 : MOVE1], sf::Vector2f{ float(m_board.getBoardSize().y - (IMAGE_SIZE * 3)),float(m_board.getBoardSize().x - IMAGE_SIZE*2) }, font, (move) ? (m_board.getBoardSizeCor().x *  m_board.getBoardSizeCor().y) / 3 * 2 : 0));
	m_bar.push_back(std::make_unique<TimeInfo>(images[(time) ? TIME2 : TIME1], sf::Vector2f{ float(m_board.getBoardSize().y - (IMAGE_SIZE * 6)),float(m_board.getBoardSize().x - IMAGE_SIZE*2) }, font, (time) ? m_board.getBoardSizeCor().x * 0.05 : 0));
	m_bar.push_back(std::make_unique<Logo>(images[LOGO], sf::Vector2f{ 105,float(m_board.getBoardSize().x - IMAGE_SIZE*2) }, sf::Vector2f{ float(double(double(m_board.getBoardSize().y - 315) / 350)), 1 }));

}
//======================================== set the selected signal ====================================================
void Stage::setCelected(const std::vector<sf::Sprite>& images) {
	m_choose = images[CHOOSE];
	for each (auto &player in m_players)
		if (dynamic_cast<King*>(player.get()) != nullptr)
			m_choose.setPosition(player->getLocation());
}
//*****************************************************************************************************************
//                  stage run function
//*****************************************************************************************************************
//runs the currnt level
bool Stage::run(sf::RenderWindow& window)
{
	window.create(sf::VideoMode{ unsigned int(m_board.getBoardSize().y),unsigned int(m_board.getBoardSize().x) },
		"Save The King", sf::Style::Close);

	sf::Clock clock; //for the dwarf
	float deltaTime = 0;


	//loop while playing the current level
	while (window.isOpen())
	{

		if (!doEvent(window)) //evevnt and moves players
			return false;

		if (win())  //if king is on the throne
			return true;

		//update time and check if time or move s are over
		if (!timeAndMoveLimit(clock, deltaTime))
			return false;

		moveDwarf(deltaTime);  //moves the dwarfs

		//     draw
		window.clear();
		draw(window, m_bar);
		m_board.drawBoard(window);  //draw static tiles
		window.draw(m_choose);
		draw(window, m_players);


		/* final draw*/
		window.display();

	}

	return true; //will never get here
}
//=========================== while the window is open =====================================
bool Stage::doEvent(sf::RenderWindow& window) {
	sf::Event event;
	if (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			exit(0);

		case sf::Event::KeyPressed:
			if (!keyPressed(event))
				return false;
			break;

		case sf::Event::MouseButtonPressed:
			mousebutton(event);
			break;
		}
	}
	return true;
}
//======================= key Pressed event =======================================================
bool Stage::keyPressed(sf::Event event)
{
	for (auto& player : m_players)
		if (dynamic_cast<Dwarf*>(player.get()) == nullptr)
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				return false;
				break;

			case sf::Keyboard::Up:
				static_cast<MoveInfo*>(m_bar[MOVE].get())->setInfo(static_cast<UserPlayer*>(player.get())->move(m_board, m_players, sf::Vector2f{ 0.f,-SPEED }, m_choose));

				break;

			case sf::Keyboard::Down:
				static_cast<MoveInfo*>(m_bar[MOVE].get())->setInfo(static_cast<UserPlayer*>(player.get())->move(m_board, m_players, sf::Vector2f{ 0.f,SPEED }, m_choose));
				break;

			case sf::Keyboard::Left:
				static_cast<MoveInfo*>(m_bar[MOVE].get())->setInfo(static_cast<UserPlayer*>(player.get())->move(m_board, m_players, sf::Vector2f{ -SPEED,0.f }, m_choose));
				break;

			case sf::Keyboard::Right:
				static_cast<MoveInfo*>(m_bar[MOVE].get())->setInfo(static_cast<UserPlayer*>(player.get())->move(m_board, m_players, sf::Vector2f{ SPEED,0.f }, m_choose));
				break;
			}

	return true;
}
//======================== mouse button event =====================================================================
void Stage::mousebutton(sf::Event event)
{
	bool choose = false;
	for (auto& player : m_players)
		if (dynamic_cast<Dwarf*>(player.get()) == nullptr)
			if (player->getDisplay().getGlobalBounds().contains(sf::Vector2f{ (float)event.mouseButton.x,(float)event.mouseButton.y }))
			{
				choose = true;
				static_cast<UserPlayer*>(player.get())->setSelected(true);
				m_choose.setPosition(player->getLocation());
				break;
			}

	if (choose)
		for (auto& player : m_players)
			if (player->getDisplay().getGlobalBounds().contains(sf::Vector2f{ (float)event.mouseButton.x,(float)event.mouseButton.y }))
				continue;
			else
				static_cast<UserPlayer*>(player.get())->setSelected(false);
}
//========================= move Dwarf =========================================================================
void Stage::moveDwarf(float deltaTime) {

	for (auto & dwarf : m_players)
		if (dynamic_cast<Dwarf*>(dwarf.get()) != nullptr)
			(dynamic_cast<Dwarf*>(dwarf.get()))->move(m_board, m_players, deltaTime);

}
//======================= time And Move Limit ===========================================================
bool Stage::timeAndMoveLimit(sf::Clock& clock, float& deltaTime) {
	deltaTime = clock.restart().asSeconds();
	static_cast<TimeInfo*>(m_bar[TIME].get())->setInfo(deltaTime*0.01);

	if (didLose(m_bar))
		return false;
	return true;
}
//=========================== if win =============================================================================
bool Stage::win()
{
	for (auto& player : m_players)
		if (dynamic_cast<King*>(player.get()) != nullptr)
			if ((dynamic_cast<King*>(m_players[0].get()))->getWin())
				return true;

	return false;
}
