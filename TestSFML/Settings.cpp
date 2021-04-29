#include "Settings.h"
// PROJECT - CLASS - SETTINGS FUNCTION

Settings::Settings() {

}

Settings::Settings(sf::Texture* tx) {
	/*panel.setTexture(tx[6]);
	panel.setPosition(550, 210);
	sf::Vector2f panel_pos = panel.getPosition();
	panel.setScale(4, 4);*/

	panel.setTexture(tx[6]);
	panel.setOrigin(tx[6].getSize().x / 2, 0);
	panel.setScale(3, 3);
	panel.setPosition(WINDOW_WIDTH / 2, (WINDOW_HEIGHT - tx[6].getSize().y * 3) / 2);
	sf::Vector2f panel_pos = panel.getPosition();

}

Settings::~Settings() {}