#ifndef CAR_H
#define CAR_H

#include "Obstacle.h"

class Car : public Obstacle
{
public:
	Car(const sf::Vector2f& position, const float& speed, const bool& direction);
	void set_initial_position();
	void save(std::ofstream& out);

	void initSprite();
	void initTexture();

};

#endif