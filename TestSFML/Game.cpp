#include "Game.h"

bool Game::running()
{
	return (window.isOpen() && level <= 5);
}

void Game::pause_game()
{
    sf::sleep(sf::milliseconds(100));
    pause = !pause;
    for (Row* r : rows)
        r->set_pause(pause);
}

#pragma region INITIALIZATION
Game::Game()  {

	init_variables();
	init_map();

	cout << "Initializing..." << endl;

	room = 0;
	BGready = false;
	keyRel = true;
	tx = nullptr;
	gamespeed = 1;
	level = 0;

	vol_bgm = 7;
	vol_sfx = 10;


	cout << "Loading resources..." << endl;

	LoadTextures(tx, 25);
	font.loadFromFile(FONT);
	menu.LoadButton(tx, 3, 4, sf::Vector2f(320, 64));
	cre.setTexture(tx[24]);

	LoadSoundBuffer();
	bgm.setVolume((float)vol_bgm * 10.f);
	bgm.openFromFile(BGM_MENU);
	bgm.setLoop(true);

	back_x = new float[3];
	for (int i = 0; i < 3; i++) back_x[i] = 0.02f * i;

	back = new sf::Sprite * [4];
	for (int i = 0; i < 4; i++) {
		back[i] = new sf::Sprite[2];
		for (int j = 0; j < 2; j++) {
			back[i][j].setTexture(tx[20]);
			back[i][j].setTextureRect(sf::IntRect(240 * i, 0, 240, 208));
			back[i][j].setScale(4, 4);
		}
	}

	player = new Player(sb, vol_sfx);


	pm_option = new string[5];
	pm_option[0] = "GAME PAUSED";
	pm_option[1] = "Resume";
	pm_option[2] = "Load Game";
	pm_option[3] = "Save Game";
	pm_option[4] = "Quit Game";
	pausemenu = new PauseMenu(tx, 6, 5);


	menuRect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	menuRect.setFillColor(sf::Color::White);
	mRalpha = 255;


	wm_option = new string[3];
	wm_option[0] = "CONGRATS";
	wm_option[1] = "Play Again";
	wm_option[2] = "Quit Game";
	winmenu = new WinMenu(tx, 6, 3);


	eff_victory.loadTexture(tx, 23);

	// Settings

	cout << "Settings..." << endl;

	pmoption_txt = new sf::Text[5];
	for (int i = 0; i < 5; i++) {
		pmoption_txt[i].setFont(font);
		pmoption_txt[i].setString(pm_option[i]);
		pmoption_txt[i].setFillColor(sf::Color(35, 33, 30, 255));
		pmoption_txt[i].setCharacterSize(48);
		pmoption_txt[i].setLetterSpacing(0.65f);
		pmoption_txt[i].setOrigin(pmoption_txt[i].getLocalBounds().width / 2, 0);
		pmoption_txt[i].setPosition(WINDOW_WIDTH / 2,
			pausemenu->panel.getPosition().y + 24 + 64 * i);
	}

	wmoption_txt = new sf::Text[3];
	for (int i = 0; i < 3; i++) {
		wmoption_txt[i].setFont(font);
		wmoption_txt[i].setString(wm_option[i]);
		wmoption_txt[i].setFillColor(sf::Color(35, 33, 30, 255));
		wmoption_txt[i].setCharacterSize(48);
		wmoption_txt[i].setLetterSpacing(0.65f);
		wmoption_txt[i].setOrigin(wmoption_txt[i].getLocalBounds().width / 2, 0);
		wmoption_txt[i].setPosition(WINDOW_WIDTH / 2,
			winmenu->panel.getPosition().y + 24 + 64 * i);
	}

	setting = new Settings(tx);

	txt_str_no = 3;
	Setup_Settings();


	chooser.setSize(sf::Vector2f(448.f, 64.f));
	chooser.setFillColor(sf::Color(255, 255, 255, 0));
	chooser.setOutlineThickness(5.f);
	chooser.setOutlineColor(sf::Color(35, 33, 30, 255));
	chooser_idx = 0;

	cout << "Initialization complete." << endl;


	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Crossroad", sf::Style::Titlebar | sf::Style::Close);

}

void Game::init_variables()
{
    for (int i = 0; i < LANE_NUMBER; i++)
    {
        sf::RectangleShape stripe;
        stripe.setSize({ PLAY_WINDOW_WIDTH, STRIPE_THICKNESS });
        stripe.setPosition(0, LOWEST_LANE_Y - GAP * i);
        stripe.setFillColor(sf::Color::Black);
        stripes.push_back(stripe);
    }
}

void Game::init_map()
{
    if (!rows.empty())
    {
        for (Row* r : rows)
            delete r;
        rows.clear();
    }
    Row* r;

	if (level == 0 || level == 6)
	{
		for (int i = 0; i < LANE_NUMBER; i += 2)
		{
			r = new Row(Randomizer::random(0, 1), i);
			rows.push_back(r);
		}
	}

	else if (level == 1)
	{
		for (int i = 0; i < LANE_NUMBER; i += 2)
		{
			r = new Row(Randomizer::random(0, 1), i);
			rows.push_back(r);
		}
		int extraLane;
		do
		{
			extraLane = Randomizer::random(1, 7);
		} while ((extraLane + 1) % 2);
		r = new Row(Randomizer::random(0, 1), extraLane);
		rows.push_back(r);
	}
	else if (level == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			r = new Row(i % 2, i);
			rows.push_back(r);
		}
		r = new Row(Randomizer::random(0, 1), 4);
		rows.push_back(r);
		for (int i = 6; i < 9; i++)
		{
			r = new Row(i % 2, i);
			rows.push_back(r);
		}
	}
	else if (level == 3)
	{
		r = new Row(Randomizer::random(0, 1), 0);
		rows.push_back(r);
		r = new Row(Randomizer::random(0, 1), 2);
		rows.push_back(r);
		for (int i = 4; i < 9; i++)
		{
			r = new Row(i % 2, i);
			rows.push_back(r);
		}
	}
	else if (level == 4)
	{
		int empty = Randomizer::random(1, 7);
		for (int i = 0; i < LANE_NUMBER - 1; i++)
		{
			if (i != empty)
			{
				r = new Row(i % 2, i);
				rows.push_back(r);
			}
		}
	}
	else if (level == 5)
	{
		for (int i = 0; i < LANE_NUMBER - 1; i++)
		{
			r = new Row(i % 2, i);
			rows.push_back(r);
		}
	}
}
#pragma endregion

#pragma region UPDATE

void Game::update()
{
    window.pollEvent(ev);
    
    update_player(ev);
    update_rows();
    update_sidemenu();
}

void Game::update_player(const sf::Event& ev)
{
    player->move(ev);
    if (player->win())
    {
		player->sb_fxsk[4].play();
		player->set_initial_position();
        level++;
        init_map();
    }
}

void Game::update_rows()
{
    for (Row* r : rows)
    {
        r->update();
		if (r->check_collide(player->get_bound()))
		{
			player->set_initial_position();
			player->sb_fxsk[3].play();
		}
    }
}

void Game::update_sidemenu()
{
	sidemenu.update(&window, level + 1, (int)clock.getElapsedTime().asSeconds() + time);    
}
#pragma endregion

#pragma region MENU
void Game::LoadTextures(sf::Texture*& texture, int tx_size) {
	texture = new sf::Texture[tx_size];
	for (int i = 0; i < tx_size; i++) {
		string s = "";
		switch (i) {
		case 0:
			s = TILE_GRASS;
			break;
		case 1:
			s = TILE_PAVEMENT;
			break;
		case 2:
			s = SPR_PLAYER;
			break;
		case 3:
			s = TILE_BUTTON;
			break;
		case 4:
			s = SPR_TITLE;
			break;
		case 5:
			s = SPR_PANEL00;
			break;
		case 6:
			s = SPR_PANEL01;
			break;
		case 7:
			s = SPR_PANEL02;
			break;
		case 8:
			s = SPR_PANEL_BOT;
			break;
		case 9:
			s = POR_STUDENT;
			break;
		case 10:
			s = MINI_STUDENT;
			break;
		case 11:
			s = SPR_ANIMAL_EAGLE;
			break;
		case 12:
			s = SPR_ANIMAL_DINOSAUR;
			break;
		case 13:
			s = TILE_SKILL;
			break;
		case 14:
			s = SPR_SKILLBAR;
			break;
		case 15:
			s = SPR_SKILLBAR_OL;
			break;
		case 16:
			s = POR_DOCTOR;
			break;
		case 17:
			s = MINI_DOCTOR;
			break;
		case 18:
			s = POR_NINJA;
			break;
		case 19:
			s = MINI_NINJA;
			break;
		case 20:
			s = BACKGROUND;
			break;
		case 21:
			s = SPR_VEHICLE;
			break;
		case 22:
			s = SPR_TFLIGHT;
			break;
		case 23:
			s = SPR_VICTORY;
			break;
		case 24:
			s = SPR_LEVEL;
			break;
		}
		texture[i].loadFromFile(s);
	}
}

void Game::LoadSoundBuffer()
{
	int snd_no = 7;
	sb = new sf::SoundBuffer[snd_no];
	sb[0].loadFromFile(SND_EFFECTSK00);
	sb[1].loadFromFile(SND_EFFECTSK01);
	sb[2].loadFromFile(SND_EFFECTSK02);
	sb[3].loadFromFile(SND_BUTTON);
	sb[4].loadFromFile(SND_BUTTON_CHANGE);
	sb[5].loadFromFile(SND_CRASH);
	sb[6].loadFromFile(SND_WIN);

	sound = new sf::Sound[snd_no];
	for (int i = 0; i < snd_no; i++) {
		sound[i].setBuffer(sb[i]);
	}
}

void Game::Run()
{
	while (window.isOpen()) {


		sf::Event ev;
		if (window.pollEvent(ev)) {

			switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				if (!keyRel) keyRel = true;
				break;
			}
		}

		window.clear(sf::Color::White);

		if (bgm.getStatus() == sf::Music::Stopped) {
			bgm.play();
		}

		switch (room) {
		case 0:
			Room_Menu(ev, tx);
			break;
		case 1:
			Room_Game();
			break;
		case 2:
			Room_Settings(ev);
			break;
		}
		window.display();

	}
}

void Game::Room_Menu(sf::Event ev, sf::Texture* texture)
{
	if (mRalpha > 0) {
		mRalpha -= GAMESPEED;
		menuRect.setFillColor(sf::Color(255, 255, 255, (int)mRalpha));
	}
	else {

		if (keyRel && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			switch (menu.getbIdx()) {
			case 0:
				room = 1;
				bgm.stop();
				bgm.openFromFile(BGM_GAME);
				break;
			case 1:
				this->load();
				bgm.stop();
				bgm.openFromFile(BGM_GAME);
				room = 1;
				break;
			case 2:
				room = 2;
				break;
			case 3:
				window.close();
				break;
			}
			keyRel = false;
			PlaySound(sound, 3);
		}
		if (menu.delay > 0) {
			menu.delay--;
		}
		else
			if (keyRel && sf::Keyboard::isKeyPressed(ev.key.code)) {
				switch (ev.key.code) {
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				}
				keyRel = false;
				PlaySound(sound, 4);
			}

	}

	sf::Sprite title(tx[4]);
	title.setOrigin(tx[4].getSize().x / 2, tx[4].getSize().y / 2);
	title.setPosition(WINDOW_WIDTH / 2, 224);
	title.setScale(1.2f, 1.2f);
	window.draw(title);

	for (int i = 0; i < menu.getbNumber(); i++) {
		window.draw(menu.getButton(i, menu.isOn(i)));
	}

	if (mRalpha > 0) window.draw(menuRect);
}

void Game::PlaySound(sf::Sound* sound, int idx) {
	sound[idx].setVolume((float)vol_sfx * 10.f);
	sound[idx].play();
}

void Game::Room_Game()
{
	if (gamespeed == 1)
	{
		while (this->running())
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
			{
				this->update();
				this->render();
			}
			else
			{
				gamespeed = 0;
				break;
			}
		}
		if (!this->running())
			gamespeed = 2;
	}
	if (gamespeed == 0) {
		sf::RectangleShape black;
		black.setFillColor(sf::Color(35, 33, 30, 155));
		black.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		window.draw(black);
		pausemenu->chooser.setPosition(pausemenu->panel.getPosition().x,
			pausemenu->panel.getPosition().y + 24 + 64 * pausemenu->getOption());
		window.draw(pausemenu->panel);
		for (int i = 0; i < 5; i++) {
			window.draw(pmoption_txt[i]);
		}
		window.draw(pausemenu->chooser);

		switch (pausemenu->Update(keyRel, sound)) {
		case 1:
			gamespeed = 1;
			break;
		case 2:
			this->load();
			room = 1;
			break;
		case 3:
			this->save();
			break;
		case 4:
			room = 0;
			gamespeed = 1;
			bgm.stop();
			bgm.openFromFile(BGM_MENU);
			break;
		}
	}
	if (gamespeed == 2)
	{
		window.draw(eff_victory.getRect());
		window.draw(eff_victory.getSprite());
		if (eff_victory.getDelay() < 1000.f)
			eff_victory.Update();
		else {
			window.clear();
			sf::RectangleShape black;
			black.setFillColor(sf::Color(35, 33, 30, 155));
			black.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
			window.draw(black);
			winmenu->chooser.setPosition(winmenu->panel.getPosition().x,
				winmenu->panel.getPosition().y + 24 + 64 * winmenu->getOption());
			window.draw(winmenu->panel);
			for (int i = 0; i < 3; i++) {
				window.draw(wmoption_txt[i]);
			}
			window.draw(winmenu->chooser);

			switch (winmenu->Update(keyRel, sound)) {
			case 1:
				room = 1;
				gamespeed = 1;
				level = 0;
				player->set_initial_position();
				init_map();

				break;
			case 2:
				room = 0;
				gamespeed = 1;
				bgm.stop();
				bgm.openFromFile(BGM_MENU);
				break;
			}
		}
		if (gamespeed == 1 && keyRel && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			gamespeed = 0;
			keyRel = false;
			PlaySound(sound, 3);
		}
	}
}

void Game::Setup_Settings() {
	sf::Vector2f panel_pos = setting->panel.getPosition();

	txt_str = new string * [txt_str_no];
	
	for (int i = 0; i < txt_str_no; i++) {
		txt_str[i] = new string[2];
		switch (i) {
		case 0:
			txt_str[i][0] = "BGM";
			txt_str[i][1] = to_string(vol_bgm);
			break;
		case 1:
			txt_str[i][0] = "SFX";
			txt_str[i][1] = to_string(vol_sfx);
			break;
		case 2:
			txt_str[i][0] = "Main Menu";
			txt_str[i][1] = "";
			break;
		}
	}

	const sf::Color txt_col[3] = {
		sf::Color(35, 33, 30, 255), sf::Color(54, 51, 48, 255),
		sf::Color(234, 28, 38, 255)
	};
	txt = new sf::Text * [txt_str_no];
	for (int i = 0; i < txt_str_no; i++) {
		txt[i] = new sf::Text[2];
		for (int j = 0; j < 2; j++) {
			txt[i][j].setFont(font);
			txt[i][j].setString(txt_str[i][j]);
			txt[i][j].setFillColor(txt_col[j]);
			txt[i][j].setCharacterSize(48);
			txt[i][j].setLetterSpacing(0.65f);
			if (j == 1) {
				txt[i][j].setOrigin(txt[i][j].getLocalBounds().width / 2, 0);
			}
			txt[i][j].setPosition(panel_pos.x - 223+314 * j,
				panel_pos.y + 24 + 64 * i);
		}
	}
}

void Game::Room_Settings(sf::Event ev) {
	window.draw(setting->panel);
	sf::Vector2f panel_pos = setting->panel.getPosition();

	chooser.setPosition(panel_pos.x-223, panel_pos.y + 24 + 64 * chooser_idx);
	window.draw(chooser);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			window.draw(txt[i][j]);
		}
	}


	if (keyRel && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		if (chooser_idx == 2) {
			room = 0;
			chooser_idx = 0;
			PlaySound(sound, 3);
		}
		keyRel = false;
	}
	if (keyRel && sf::Keyboard::isKeyPressed(ev.key.code)) {
		if (ev.key.code == sf::Keyboard::Key::Right ||
			ev.key.code == sf::Keyboard::Key::Left) {
			int Kb = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) -
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
			switch (chooser_idx) {
			case 0:
				vol_bgm += Kb;
				break;
			case 1:
				vol_sfx += Kb;
				break;
			}

			if (vol_bgm > 10) vol_bgm = 0;
			if (vol_bgm < 0) vol_bgm = 10;
			if (vol_sfx > 10) vol_sfx = 0;
			if (vol_sfx < 0) vol_sfx = 10;

			bgm.setVolume((float)vol_bgm * 10.f);

			PlaySound(sound, 4);

		}
		else
			switch (ev.key.code) {
			case sf::Keyboard::Up:
				if (chooser_idx <= 0)
					chooser_idx = 2;
				else chooser_idx--;
				PlaySound(sound, 4);
				break;
			case sf::Keyboard::Down:
				if (chooser_idx >= 2)
					chooser_idx = 0;
				else chooser_idx++;
				PlaySound(sound, 4);
				break;
			}
		keyRel = false;
	}

	for (int i = 0; i < txt_str_no; i++) {
		for (int j = 0; j < 2; j++) {
			txt[i][j].setString(txt_str[i][j]);
			if (j == 1) {
				txt[i][j].setOrigin(txt[i][j].getLocalBounds().width / 2, 0);
			}
		}
	}
	
	for (int i = 0; i < txt_str_no; i++) {
		switch (i) {
		case 0:
			txt_str[i][1] = to_string(vol_bgm);
			break;
		case 1:
			txt_str[i][1] = to_string(vol_sfx);
			break;
		}
	}
}
#pragma endregion

void Game::render()
{
    window.clear(sf::Color::White);
	player->render(&window);
    render_stripes();
    for (Row* r : rows)
        r->render(&window);
    sidemenu.render(&window);
    window.display();
}

void Game::render_stripes()
{
    for (auto& i : stripes)
        window.draw(i);
}

void Game::save()
{
    std::ofstream out;
    out.open("saved_game.txt");
    if (!out.is_open()) { // need other notification
        std::cout << "Can not open file to write." << '\n';
        return;
    }

    out << (int)this->clock.getElapsedTime().asSeconds() + time<< '\n';

    //save player position
    player->save_position(out);

    //save level
    out << this->level << '\n';

    //num of row
    out << this->rows.size() << '\n';

    //save row
    for (int i = 0; i < this->rows.size(); ++i) {
        this->rows[i]->save_rows(out);
    }

    out.close();

    sf::sleep(sf::milliseconds(100));
}

void Game::load()
{
    std::ifstream in;
    in.open("saved_game.txt");
    if (!in.is_open()) {
        std::cout << "Can not open file to write." << '\n';
        return;
    }

    in >> this->time;

    //load position
    player->load_position(in);

    //load level
    in >> this->level;

    //load num of rows
    int numRows;
    in >> numRows;

    //load rows
    if (!rows.empty())
    {
        for (Row* r : rows) {
            delete r;
        }
        rows.clear();
    }
    for (int i = 0; i < numRows; ++i) {
        Row* r;
        int lane;
        int direction;
        in >> lane >> direction;
        r = new Row(direction, lane);
        rows.push_back(r);
        r->load_rows(in);
    }

    in.close();

    sf::sleep(sf::milliseconds(100));
	gamespeed = 1;
}

Game::~Game()
{
	delete[]tx;
	if (player != nullptr) delete player;
	/*if (animal != nullptr) {
		delete[]animal[0]; delete[]animal[1];
		delete[]animal;
	}
	if (vehicle != nullptr) {
		delete[]vehicle[0]; delete[]vehicle[1];
		delete[]vehicle;
	}
	if (traffic != nullptr) delete[]traffic;
	if (back_x != nullptr) delete[]back_x;
	if (back != nullptr) {
		for (int i = 0; i < 4; i++) {
			delete[]back[i];
		}
		delete[]back;
	}
	*/
	if (sb != nullptr) delete[]sb;
	if (sound != nullptr) delete[]sound;
	//delete setting;
	if (pmoption_txt != nullptr) delete[]pmoption_txt;
	if (wmoption_txt != nullptr) delete[]wmoption_txt;
    for (Row* r : rows)
        delete r;
	cout << "Exit successfully." << endl;
}