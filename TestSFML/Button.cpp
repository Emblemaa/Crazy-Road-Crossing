#include "Button.h"

Button::Button(const std::string& text, const sf::Font& font, const sf::Vector2f& position)
{
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(position.x + BUTTON_WIDTH / 2, position.y + BUTTON_HEIGHT / 2 - 7.5);
	this->text.setFillColor(sf::Color::Black);

	bound.setSize({ BUTTON_WIDTH, BUTTON_HEIGHT });
	bound.setPosition(position);
	bound.setFillColor(sf::Color::White);
	
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(bound);
	window->draw(text);
}

void Button::check_hover(sf::RenderWindow* window)
{
	sf::IntRect rect(bound.getPosition().x, bound.getPosition().y, bound.getGlobalBounds().width, bound.getGlobalBounds().height);
	if (check_on_click(window))
	{
		bound.setFillColor(sf::Color(128, 128, 128));
		text.setFillColor(sf::Color::White);
		render(window);
		window->display();
	}
	else if (rect.contains(sf::Mouse::getPosition(*window)))
	{
		bound.setFillColor(sf::Color(169, 169, 169));
		text.setFillColor(sf::Color::Black);
	}
	else 
	{
		bound.setFillColor(sf::Color::White);
		text.setFillColor(sf::Color::Black);
	}
}

bool Button::check_on_click(sf::RenderWindow* window)
{
	sf::IntRect rect(bound.getPosition().x, bound.getPosition().y, bound.getGlobalBounds().width, bound.getGlobalBounds().height);

	return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(sf::Mouse::getPosition(*window)));
}