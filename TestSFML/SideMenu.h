#ifndef SIDE_MENU_H
#define SIDE_MENU_H

#include "Button.h"
#include "CONSTANTS.h"

class SideMenu
{
private:
	sf::Font font;
	sf::RectangleShape menu;
	std::vector<Button*> buttons;
	sf::Text level;
	sf::Text timer;
public:
	SideMenu();
	void update(sf::RenderWindow* window, const int& lvl, const int& time);
	void render(sf::RenderWindow* window);
	~SideMenu();
};

#endif