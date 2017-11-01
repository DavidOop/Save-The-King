#include "InfBar.h"


/* c-cr*/
Bar::Bar(const sf::Sprite& display, const sf::Vector2f& location)
	:m_display(display) {
	m_display.setPosition(location);
}
//--------------------------------------------------------------
Bar::~Bar() = default;
template<typename T>
Info<T>::~Info() = default;
template<typename T>
GameLimit<T>::~GameLimit() = default;
//=====================================================================
//                  Logo class
//======================================================================
Logo::Logo(const sf::Sprite& display, const sf::Vector2f& location, const sf::Vector2f& factors)
	:Bar(display, location) {
	m_display.setScale(factors);
}
//==============================================================================
//             information class
//==============================================================================
template<typename T>
Info<T>::Info(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, T info)
	: Bar(display, location), m_info(info) {
	m_text.setFont(font);
	m_text.setFillColor(sf::Color::Black);
}
//------------------------------------------------------------------
template<typename T>
void Info<T>::display(sf::RenderWindow& window) {
	window.draw(m_display);
	window.draw(getText());
}
//=======================================================================
//                     Level number class
//=======================================================================
Level::Level(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, int info)
	:Info(display, location, font, info) {
	m_text.setCharacterSize(35);
	m_text.setPosition(sf::Vector2f{ location.x + 40,location.y + 22 });
}
//--------------------------------------------------------------------
const  sf::Text& Level::getText() {
	m_text.setString(std::to_string(m_info));
	return m_text;
}
//-------------------------------------------------------------------
//==============================================================================
//             game limit class
//==============================================================================
template<typename T>
GameLimit<T>::GameLimit(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, T info)
	: Info(display, location, font, info) {
	m_isLimit = (info != 0);
}
//=======================================================================
//                     number of moves class
//=======================================================================
MoveInfo::MoveInfo(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, double info)
	:GameLimit(display, location, font, info) {
	m_text.setCharacterSize(30);
	m_text.setPosition(sf::Vector2f{ location.x + 30,location.y + 25 });

}
//--------------------------------------------------------------------
const  sf::Text& MoveInfo::getText() {
	m_text.setString(std::to_string(int(m_info)));
	return m_text;
}
//-------------------------------------------------------------------


//=======================================================================
//                     time of game class
//=======================================================================
TimeInfo::TimeInfo(const sf::Sprite& display, const sf::Vector2f& location, const sf::Font& font, float info)
	:GameLimit(display, location, font, info) {
	m_text.setCharacterSize(25);
	m_text.setPosition(sf::Vector2f{ location.x + 20,location.y + 25 });
}
//--------------------------------------------------------------------------
const sf::Text& TimeInfo::getText() {
	if (m_info > .6f &&  m_info < 1.f)
		m_info += (m_isLimit) ? -.4f : .4f;
	auto str = std::to_string(m_info);
	m_text.setString(std::string{ '0',str[0],':',str[2],str[3] });

	return m_text;
}

//==============================================================================
//===============================================================================
////=============================================================================
bool didLose(const std::vector<std::unique_ptr<Bar>>& barVec) {
	for (auto& bar : barVec)
	{
		if (castDidLose(bar, .0))
			return true;
		if (castDidLose(bar, 0.f))
			return true;
	}
	return false;
}
//------------------------------------------------------------
template<typename T>
bool castDidLose(const std::unique_ptr<Bar>& bar, T type) {
	if (dynamic_cast<GameLimit<T>*>(bar.get()) != nullptr)
		if (dynamic_cast<GameLimit<T>*>(bar.get())->didLose())
			return true;
	return false;
}