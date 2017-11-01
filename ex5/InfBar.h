#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
/*****************************************************************************
class BoardImage
******************************************************************************/
class Bar {
public:
	/* c-cr, d-cr */
	Bar(const sf::Sprite& display, const sf::Vector2f& location = sf::Vector2f{});
	virtual ~Bar() = 0;

	virtual void display(sf::RenderWindow& window) = 0;

protected:
	sf::Sprite m_display;
};
//=====================================================================
//                  Logo class

//======================================================================
class Logo : public Bar
{
public:
	Logo(const sf::Sprite&, const sf::Vector2f&, const sf::Vector2f&);
	void display(sf::RenderWindow& window) override { window.draw(m_display); }
	~Logo() {}
};
//=====================================================================
//                 information class

//======================================================================
template<typename T>
class Info :public Bar {
public:
	Info(const sf::Sprite&, const sf::Vector2f& location, const sf::Font& font, T info);
	virtual ~Info() = 0;

	void display(sf::RenderWindow& window) override;
	virtual const sf::Text& getText() = 0;
protected:

	sf::Text m_text;
	T m_info;         //time or number of moves
};
//=======================================================================
//                     Level number class
//=======================================================================
class Level : public Info<int>
{
public:
	Level(const sf::Sprite&, const sf::Vector2f&, const sf::Font&, int);
	~Level() {}
	const sf::Text& getText() override;


};
//======================================================================
//                    Game limit class
//=======================================================================
template <typename T>
class GameLimit : public Info<T>
{
public:
	GameLimit(const sf::Sprite&, const sf::Vector2f& location, const sf::Font& font, T info);
	virtual ~GameLimit() = 0;
	virtual void setInfo(T) = 0;
	virtual bool didLose()const = 0;
protected:
	bool m_isLimit = false;   //limit of time or move

};
//=======================================================================
//                     number of moves class
//=======================================================================
class MoveInfo : public GameLimit<double>
{
public:
	MoveInfo(const sf::Sprite&, const sf::Vector2f&, const sf::Font&, double);
	~MoveInfo() {}
	void setInfo(double moved)override { if (bool(moved))(m_isLimit) ? m_info -= 0.25 : m_info += 0.25; }
	const sf::Text& getText() override;
	bool didLose()const override { return (m_isLimit && m_info / 4 == 0); }
};
//=======================================================================
//                     time of game class
//=======================================================================
class TimeInfo : public GameLimit<float>
{
public:
	TimeInfo(const sf::Sprite& display, const sf::Vector2f&, const sf::Font&, float);
	~TimeInfo() {}
	void setInfo(float time)override { (m_isLimit) ? m_info -= time : m_info += time; }
	const sf::Text& getText() override;
	bool didLose()const override { return (m_isLimit && m_info <= 0.f); }
};
////========================================================
template<typename T>
bool castDidLose(const std::unique_ptr<Bar>&, T);
bool didLose(const std::vector<std::unique_ptr<Bar>>&);