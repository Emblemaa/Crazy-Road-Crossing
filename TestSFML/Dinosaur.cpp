#include "Dinosaur.h"

Dinosaur::Dinosaur(const sf::Vector2f& position, const float& speed, const bool& direction) : Obstacle(speed, direction)
{
	/*         __
	*       __|__|
	*    __|_____|
	*   |______|
	*/
	/*sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize({ 85.f,OBSTACLE_BLOCK_HEIGHT });
	shapes.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ 85.f, OBSTACLE_BLOCK_HEIGHT });
	if (direction)
		rec->setPosition(position.x + 20.f, position.y - OBSTACLE_BLOCK_HEIGHT);
	else rec->setPosition(position.x - 20.f, position.y - OBSTACLE_BLOCK_HEIGHT);
	shapes.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ 50.f,OBSTACLE_BLOCK_HEIGHT });
	if (direction)
		rec->setPosition(position.x + 55.f, position.y - 2 * OBSTACLE_BLOCK_HEIGHT);
	else rec->setPosition(position.x - 20.f, position.y - 2 * OBSTACLE_BLOCK_HEIGHT);
	shapes.push_back(rec);

	for (auto& c : shapes)
		c->setFillColor(sf::Color::Blue);*/
	if (this->direction == false)
		this->texture.loadFromFile("Resources/Sprite/Vehicle/Dinosaur.png");
	else
		this->texture.loadFromFile("Resources/Sprite/Vehicle/DinosaurF.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.75f, 0.75f);
	this->sprite.setPosition(position.x, position.y - GAP+15);
}

void Dinosaur::set_initial_position()
{
	sf::Vector2f position;
	if (direction)
		position = { -85.f,sprite.getPosition().y };
	else position = { PLAY_WINDOW_WIDTH,sprite.getPosition().y };
	sprite.setPosition(position);
}

void Dinosaur::save(std::ofstream& out)
{
	out << this->sprite.getPosition().x << '\n';
	out << this->speed << '\n';
	out << "2" << '\n';
}