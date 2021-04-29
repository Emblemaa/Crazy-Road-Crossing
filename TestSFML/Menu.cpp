// PROJECT - CLASS - MENU FUNCTION
#include "Menu.h"
// Menu

Menu::Menu() {
	bPtr = 0;
	bno = 0;
	cooldown = 1 * GAMESPEED;
	delay = 0;
	tx_idx = 3;
	button_on = 0;
	button = nullptr;
}

Menu::~Menu() {
	delete[]button_on;
	for (int i = 0; i < bno; i++) {
		delete[]button[i];
	}
	delete[]button;
}

void Menu::LoadButton(sf::Texture* tx, int idx, int n, sf::Vector2f size) {
	bno = n;
	button_on = new bool[bno];
	for (int i = 0; i < bno; i++) {
		if (i == bPtr) button_on[i] = 1;
		else button_on[i] = 0;
	}
	button = new sf::Sprite * [bno];
	for (int i = 0; i < bno; i++) {
		button[i] = new sf::Sprite[2];
	}

	for (int i = 0; i < bno; i++) {
		for (int j = 0; j < 2; j++) {
			button[i][j].setTexture(tx[idx]);
			button[i][j].setTextureRect(sf::IntRect(
				j * size.x, i * size.y, size.x, size.y));
			button[i][j].setOrigin(sf::Vector2f(size.x / 3.f, size.y / 3.f));
			button[i][j].setPosition(sf::Vector2f(
				WINDOW_WIDTH / 2, (RESO_WIDTH / 2) + i * size.y));
			button[i][j].setScale(1.2f, 1.2f);
		}
	}
}

void Menu::Reset() {
	for (int i = 0; i < bno; i++) {
		if (i == bPtr) button_on[i] = 1;
		else button_on[i] = 0;
	}
	delay = cooldown;
}
