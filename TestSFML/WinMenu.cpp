#include "WinMenu.h"
// PROJECT - CLASS - PAUSEMENU FUNCTION

WinMenu::WinMenu() {
	option_no = 0;
	chooser.setSize(sf::Vector2f(448.f, 64.f));
	chooser.setFillColor(sf::Color(255, 255, 255, 0));
	chooser.setOutlineThickness(5.f);
	chooser.setOutlineColor(sf::Color(35, 33, 30, 255));
	chooser.setOrigin(chooser.getSize().x / 2, 0);
	chooser_idx = 1;
}

WinMenu::WinMenu(sf::Texture* tx, int idx, int option_no) {
	chooser_idx = 1;
	this->option_no = option_no;

	panel.setTexture(tx[idx]);
	panel.setOrigin(tx[idx].getSize().x / 2, 0);
	panel.setScale(3, 3);
	panel.setPosition(WINDOW_WIDTH / 2, (WINDOW_HEIGHT - tx[idx].getSize().y * 3) / 2);


	chooser.setSize(sf::Vector2f(448.f, 64.f));
	chooser.setFillColor(sf::Color(255, 255, 255, 0));
	chooser.setOutlineThickness(5.f);
	chooser.setOutlineColor(sf::Color(35, 33, 30, 255));
	chooser.setOrigin(chooser.getSize().x / 2, 0);

}

WinMenu::~WinMenu()
{

}

int WinMenu::Update(bool& keyRel, sf::Sound* sound) {
	if (!keyRel) return 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (chooser_idx >= 1 && chooser_idx <= option_no - 1) {
			keyRel = false;
			int ci_return = chooser_idx;
			chooser_idx = 1;
			sound[3].play();
			return ci_return;
		}
		keyRel = false;
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (chooser_idx == 1) chooser_idx = option_no - 1;
			else chooser_idx--;
			keyRel = false;
			sound[4].play();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (chooser_idx == option_no - 1) chooser_idx = 1;
			else chooser_idx++;
			keyRel = false;
			sound[4].play();
		}
	}
	return 0;
}