#ifndef WinMenu_h
#define WinMenu_h

#include"CONSTANTS.h"

class WinMenu
{
private:

	int option_no;
	int chooser_idx;
public:
	sf::Sprite panel;
	sf::RectangleShape chooser;

	WinMenu();
	WinMenu(sf::Texture* tx, int idx, int option_no);
	~WinMenu();

	int getOption() {
		return chooser_idx;
	}
	int Update(bool& keyRel, sf::Sound* sound);
};

#endif

