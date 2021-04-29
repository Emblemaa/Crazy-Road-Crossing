#include "Obstacle.h"

void Obstacle::initSprite(){}

void Obstacle::initTexture(){}

Obstacle::Obstacle(const float& speed, const bool& direction)
{
	this->speed = speed;
	this->direction = direction;
	initSprite();
	initTexture();
}

void Obstacle::render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

bool Obstacle::out_of_window()
{
	sf::Vector2f curPos = sprite.getPosition();
	return (direction && curPos.x >= PLAY_WINDOW_WIDTH) || (!direction && curPos.x + 85 <= 0);
}

void Obstacle::move()
{
	if (direction)
		this->sprite.move({ speed,0 });
	else this->sprite.move({ -speed,0 });
	if (out_of_window())
		this->set_initial_position();
}

void Obstacle::set_speed(const float& speed)
{
	this->speed = speed;
}

bool Obstacle::collide(const sf::FloatRect& playerBound)
{
	if (this->sprite.getGlobalBounds().intersects(playerBound))
		return true;
	return false;
}

Obstacle::~Obstacle()
{}
