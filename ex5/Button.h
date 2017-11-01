#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Graphics.hpp>
#define SFML_GRAPHICS_API

class Button
{
public:
	Button(const sf::Sprite& display, const sf::Sprite& notPressed)
		:m_display(display), m_notPressed(notPressed) {}
	virtual ~Button() {}
	virtual void pressed() = 0;
	const sf::Sprite& getDisplay() const { return(m_onBotton)? m_notPressed: m_display; }
	bool getOnBotton() const { return m_onBotton; }
	void setOnBotton(bool other) { m_onBotton = other; }

private:
	sf::Sprite m_display;
	sf::Sprite m_notPressed;
	bool m_onBotton{ false };
};
//------------------------------------
class Start : public Button {
	
	using Button::Button;
	void pressed()override {}
};
//-------------------------------------
class Help : public Button {
	using Button::Button;
	void pressed()override {}
};
//----------------------------------------
class Close : public Button {
	using Button::Button;
	void pressed()override {}
};