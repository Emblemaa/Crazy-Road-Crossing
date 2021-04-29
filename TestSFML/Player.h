#ifndef PLAYER_H
#define PLAYER_H

#include "CONSTANTS.h"

class Player
{
private:
	sf::RectangleShape player;
public:
	sf::Sound* sb_fxsk;
	Player();
	Player(sf::SoundBuffer* sb, int vol_sfx);
	void move(const sf::Event& ev);
	void render(sf::RenderWindow* window);
	void set_initial_position();
	bool win();
	sf::FloatRect get_bound();
	void save_position(std::ofstream& out);
	void load_position(std::ifstream& in);
};

#endif