#pragma once
#include "Images.h"
#include <memory>
//======================================================================================
//                          class Menu
//======================================================================================
class Menu
{
public:
	Menu(const sf::Sprite& display1, const sf::Sprite& display2)
		:m_display1(display1), m_display2(display2) {}
	virtual ~Menu() = 0;

	/* set */
	virtual void setHelpMode(bool other) { m_helpMode = other; }

	/* get functions */
	bool getHelpMode() const { return m_helpMode; }
	virtual void display(sf::RenderWindow&) const = 0;

protected:
	sf::Sprite m_display1;  //normal display
	sf::Sprite m_display2;  //if mouse on button
	bool m_helpMode{ false };  //if button help was pressed
};
//======================================================================================
//					            class Background
//======================================================================================
class Background : public Menu {
public:
	using Menu::Menu;
	void display(sf::RenderWindow& window) const override { window.draw((m_helpMode) ? m_display2 : m_display1); }
};
//===========================================================================================
//							class  Buttons 
//===========================================================================================
class Buttons :public Menu
{
public:
	using Menu::Menu;
	virtual ~Buttons() = 0;

	/* check functions */
	bool check(const sf::Vector2f& location) const { return (*this).m_display1.getGlobalBounds().contains(location); }
	virtual void onBotton(const sf::Vector2f& location) { m_switch = (check(location)) ? true : false; }
	virtual void display(sf::RenderWindow& window) const override { window.draw((!m_helpMode) ? ((m_switch) ? m_display2 : m_display1) : m_empty); }

	/* virtual functions */
	virtual void pressed(const sf::Vector2f&) = 0;

protected:
	sf::Sprite m_empty;
	bool m_switch{ false };    //if mouse on button switch display
};
//======================================================================================
//                           class Start
//======================================================================================
class Start : public Buttons {
public:
	using Buttons::Buttons;
	void pressed(const sf::Vector2f& location)override { m_startGame = (!m_helpMode && check(location)); }
	bool getStartGame()const { return m_startGame; }
	void setStartGame() { m_startGame = false; }

protected:
	bool m_startGame{ false };
};
//======================================================================================
//                           class Help
//======================================================================================
class Help : public Buttons {
public:
	using Buttons::Buttons;
	void pressed(const sf::Vector2f& location)override { m_helpMode = ((m_helpMode) ? true : (check(location) ? true : false)); }
};
//======================================================================================
//                        class Close
//======================================================================================
class Close : public Buttons {
public:
	using Buttons::Buttons;
	void pressed(const sf::Vector2f& location)override { if (!m_helpMode && check(location)) exit(0); }
};
//======================================================================================
//                         class HelpWindow
//======================================================================================
class HelpWindow : public Buttons {
public:
	using Buttons::Buttons;
	void display(sf::RenderWindow& window) const override { window.draw((m_helpMode) ? ((m_switch) ? m_display2 : m_display1) : m_empty); }
	void pressed(const sf::Vector2f& location)override { m_helpMode = ((!m_helpMode) ? false : (check(location)) ? false : true); }
};
//**************************************************************************************

//**************************************************************************************
void mouseEventButton(std::vector <std::unique_ptr<Menu>>& vec, const sf::Vector2f& location, bool event);
void updateHelpMode(std::vector <std::unique_ptr<Menu>>& vec);
bool checkHelpMode(std::vector <std::unique_ptr<Menu>>& vec);
