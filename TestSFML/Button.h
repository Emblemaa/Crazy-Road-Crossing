#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CONSTANTS.h"

class Button 
{
private:
	sf::RectangleShape bound;
	sf::Text text;
public:
	Button(const std::string& text, const sf::Font& font, const sf::Vector2f& position);
	void render(sf::RenderWindow* window);
	void check_hover(sf::RenderWindow* window);
	bool check_on_click(sf::RenderWindow* window);
};

#endif