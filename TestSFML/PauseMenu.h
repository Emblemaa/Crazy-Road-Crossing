#ifndef PauseMenu_h
#define PauseMenu_h

#include"CONSTANTS.h"

class PauseMenu
{
private:

	int option_no;
	int chooser_idx;
public:
	sf::Sprite panel;
	sf::RectangleShape chooser;

	PauseMenu();
	PauseMenu(sf::Texture* tx, int idx, int option_no);
	~PauseMenu();

	int getOption() {
		return chooser_idx;
	}
	int Update(bool& keyRel, sf::Sound* sound);
};


#endif
