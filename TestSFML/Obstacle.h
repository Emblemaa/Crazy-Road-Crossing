#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "CONSTANTS.h"

class Obstacle
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	bool direction;
public:
	virtual void initSprite();
	virtual void initTexture();
	Obstacle(const float& speed, const bool& direction);
	virtual void set_initial_position() = 0;
	bool out_of_window();

	void set_speed(const float& speed);
	void move();
	void render(sf::RenderWindow* window);
	bool collide(const sf::FloatRect& playerBound);

	virtual void save(std::ofstream& out){}

	virtual ~Obstacle();
};

#endif