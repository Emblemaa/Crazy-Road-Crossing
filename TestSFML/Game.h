#ifndef GAME_H
#define GAME_H

#include "TracfficLight.h"
#include "Truck.h"
#include "Car.h"
#include "Dinosaur.h"
#include "Player.h"
#include "SideMenu.h"
#include "Row.h"
#include"Menu.h"
#include"PauseMenu.h"
#include"WinMenu.h"
#include "CONSTANTS.h"
#include"Effect.h"
#include"Settings.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;
	SideMenu sidemenu;
	std::vector<sf::RectangleShape> stripes;
	Player* player;
	//std::vector<Obstacle*> truck;
	std::vector<Row*> rows;
	sf::Clock clock;
	int level;
	bool pause;
	int time;

private:
	Menu menu;
	sf::Texture* tx;
	sf::Font font;
	int gamespeed;
	int room;
	bool BGready, keyRel;


	string* pm_option;
	PauseMenu* pausemenu;
	float* back_x;
	sf::Sprite** back;


	string* wm_option;
	WinMenu* winmenu;

	// Audio
	sf::SoundBuffer* sb;
	sf::Sound* sound;
	sf::Music bgm;

	// Video
	sf::RectangleShape menuRect;
	float mRalpha;

	// Settings
	int vol_bgm, vol_sfx;
	int txt_str_no;
	sf::Text* pmoption_txt, *wmoption_txt;
	string** txt_str;
	sf::Text** txt;
	sf::Text description;
	sf::Sprite por;
	sf::RectangleShape chooser;
	int chooser_idx;
	Settings* setting;


	sf::Sprite cre;

	Effect_Victory eff_victory;

public:
	bool running();
	void pause_game();

#pragma region INITIALIZATION
	Game();
	void init_variables();
	void init_map();
#pragma endregion

#pragma region UPDATE
	void update();
	void update_player(const sf::Event& ev);
	void update_rows();
	void update_sidemenu();
#pragma endregion

#pragma region RENDER
	void render();
	void render_stripes();
#pragma endregion

#pragma region SAVE
	void save();
#pragma endregion

#pragma region LOAD
	void load();
#pragma endregion

#pragma region MENU
	void LoadTextures(sf::Texture*& texture, int tx_size);
	void LoadSoundBuffer();
	void Run();
	void Room_Menu(sf::Event ev, sf::Texture* texture);
	void PlaySound(sf::Sound* sound, int idx);
	void Room_Game();
	void Setup_Settings();
	void Room_Settings(sf::Event ev);
#pragma endregion

	virtual ~Game();
};

#endif