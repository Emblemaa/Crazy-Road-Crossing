#include "Car.h"

void Car::initTexture()
{
	this->texture.loadFromFile("Resources/Sprite/Vehicle/Vehicle 1.png");
}


void Car::initSprite()
{
	this->sprite.setTexture(texture);
}

Car::Car(const sf::Vector2f& position, const float& speed, const bool& direction) : Obstacle(speed, direction)
{
	/*    ____
	*   _|____|_    2 blocks of rectangle
	*  |________|
	*/
	/*sf::RectangleShape* rec = new sf::RectangleShape;

	rec->setSize({ 85.f, OBSTACLE_BLOCK_HEIGHT });
	rec->setPosition(position);
	shapes.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ 50.f,OBSTACLE_BLOCK_HEIGHT });
	rec->setPosition(position.x + 17.5, position.y - OBSTACLE_BLOCK_HEIGHT);
	shapes.push_back(rec);

	for (auto& c : shapes)
		c->setFillColor(sf::Color::Green);*/

	if (this->direction == false)
		this->texture.loadFromFile("Resources/Sprite/Vehicle/Vehicle 1.png");
	else
		this->texture.loadFromFile("Resources/Sprite/Vehicle/Vehicle_1F.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.7f, 0.7f);
	this->sprite.setPosition(position.x, position.y - GAP + 17);

	
}

void Car::set_initial_position()
{
	sf::Vector2f position;
	if (direction)
		position = { -85.f,sprite.getPosition().y };
	else position = { PLAY_WINDOW_WIDTH,sprite.getPosition().y };
	sprite.setPosition(position);
}

void Car::save(std::ofstream& out)
{
	out << this->sprite.getPosition().x << '\n';
	out << this->speed << '\n';
	out << "0" << '\n';
}