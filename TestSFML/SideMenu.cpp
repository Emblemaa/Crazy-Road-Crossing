#include "SideMenu.h"

SideMenu::SideMenu()
{
	menu.setSize({ WINDOW_WIDTH - PLAY_WINDOW_WIDTH,WINDOW_HEIGHT });
	menu.setPosition(PLAY_WINDOW_WIDTH, 0);
	menu.setFillColor(sf::Color::Black);

	font.loadFromFile(FONT);
	sf::Text text;
	text.setFont(font);


	// init buttons
	Button* button;
	sf::Vector2f initPos = { (WINDOW_WIDTH + PLAY_WINDOW_WIDTH - BUTTON_WIDTH) / 2, 160 };
	// pause
	button = new Button("Pause= P", font, { initPos.x, initPos.y + BUTTON_GAP });
	buttons.push_back(button);

	sf::Vector2f initTextPos = { (WINDOW_WIDTH + PLAY_WINDOW_WIDTH) / 2, 50 };
	sf::FloatRect textRect;
	// Level
	level.setFont(font);
	level.setString("Level 1");
	textRect = level.getGlobalBounds();
	level.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	level.setPosition(initTextPos);
	level.setFillColor(sf::Color::White);
	// Timer
	timer.setFont(font);
	timer.setString("Time: 0s");
	textRect = timer.getGlobalBounds();
	timer.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	timer.setPosition({ initTextPos.x, initTextPos.y + 50.f });
	timer.setFillColor(sf::Color::White);
}

void SideMenu::update(sf::RenderWindow* window, const int& lvl, const int& time)
{
	level.setString("Level " + std::to_string(lvl));
	timer.setString("Time: " + std::to_string(time) + "s");
}

void SideMenu::render(sf::RenderWindow* window)
{
	window->draw(menu);
	for (Button* i : buttons)
		i->render(window);
	window->draw(level);
	window->draw(timer);
}

SideMenu::~SideMenu()
{
	for (Button* i : buttons)
		delete i;
}