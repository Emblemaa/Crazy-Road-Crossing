#ifndef Menu_h
#define Menu_h

#include"GeneralConstants.h"
#include"defineVariables.h"
#include"CONSTANTS.h"

class Menu {
private:
	int bPtr, bno;
	float cooldown;
	bool* button_on;
	sf::Sprite** button;
	int tx_idx;
public:
	float delay;

	Menu();
	~Menu();
	void LoadButton(sf::Texture* tx, int idx, int n, sf::Vector2f size);
	void Reset();

	int getbNumber() {
		return bno;
	}
	sf::Sprite getButton(int idx, int ison) {
		return button[idx][ison];
	}
	int getbIdx() {
		return bPtr;
	}
	bool isOn(int idx) {
		return button_on[idx];
	}
	float getCooldown() {
		return cooldown;
	}
	void MoveUp() {
		if (bPtr > 0) bPtr--;
		else bPtr = bno - 1;
		Reset();
	}
	void MoveDown() {
		if (bPtr < bno - 1) bPtr++;
		else bPtr = 0;
		Reset();
	}
};

#endif // !Menu_h
