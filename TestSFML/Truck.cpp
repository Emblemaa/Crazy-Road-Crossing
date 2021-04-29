#include "Truck.h"

Truck::Truck(const sf::Vector2f& position, const float& speed, const bool& direction) : Obstacle(speed, direction)
{
	/*     _____
	*   __|____|    2 blocks of rectangle
	*  |_______|
	*/

	/*sf::RectangleShape* rec = new sf::RectangleShape;
	
	rec->setSize({ 85.f, OBSTACLE_BLOCK_HEIGHT });
	rec->setPosition(position);
	shapes.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ 50.f, OBSTACLE_BLOCK_HEIGHT });
	if (direction)
		rec->setPosition(sf::Vector2f(position.x, position.y - OBSTACLE_BLOCK_HEIGHT));
	else rec->setPosition(sf::Vector2f(position.x + 35, position.y - OBSTACLE_BLOCK_HEIGHT));

	shapes.push_back(rec);
	
	for (auto& c : shapes)
		c->setFillColor(sf::Color::Magenta);*/

	if (this->direction == false)
		this->texture.loadFromFile("Resources/Sprite/Vehicle/Vehicle 2.png");
	else
		this->texture.loadFromFile("Resources/Sprite/Vehicle/Vehicle_2F.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.7f, 0.7f);
	this->sprite.setPosition(position.x, position.y - GAP + 15);
}

void Truck::set_initial_position()
{

	sf::Vector2f position;
	if (direction)
		position = { -85.f,sprite.getPosition().y };
	else position = { PLAY_WINDOW_WIDTH,sprite.getPosition().y };
	sprite.setPosition(position);
}

void Truck::save(std::ofstream& out)
{
	out << this->sprite.getPosition().x << '\n';
	out << this->speed << '\n';
	out << "1" << '\n';
}