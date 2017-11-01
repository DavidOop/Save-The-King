#include "Menu.h"
#include <memory>

Menu::~Menu() = default;
Buttons::~Buttons() = default;

//=====================================================================================
// the mouse event: true- mousePressed. false- mouseMoved.
void mouseEventButton(std::vector <std::unique_ptr<Menu>>& vec, const sf::Vector2f& location, bool event) {

	for (auto& button : vec) {
		if (dynamic_cast<Buttons*>(button.get()))
			(event) ? dynamic_cast<Buttons*>(button.get())->pressed(location) : dynamic_cast<Buttons*>(button.get())->onBotton(location);
	}
}
//----------------------------------------------------------
//updat screen mode
void updateHelpMode(std::vector <std::unique_ptr<Menu>>& vec) {
	bool helpMode = checkHelpMode(vec);  //for update help mode
	for (auto& button : vec)
		button->setHelpMode(helpMode);
}
//------------------------------------------------------------
// get current help mode
bool checkHelpMode(std::vector <std::unique_ptr<Menu>>& vec) {
	bool temp1 = vec[3]->getHelpMode();  //help
	bool temp2 = vec[4]->getHelpMode();  //window help
	bool temp3 = vec[0]->getHelpMode();  //other

	return((temp1 == temp2) ? ((temp1) ? true : false) : ((temp1 && !temp2 && !temp3) ? true : false));

}
//================================= draw menu =======================================
