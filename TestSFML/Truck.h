#ifndef TRUCK_H
#define TRUCK_H

#include "Obstacle.h"

class Truck : public Obstacle
{
public:
	Truck(const sf::Vector2f& position, const float& speed, const bool& direction);
	void set_initial_position();
	void save(std::ofstream& out);
};

#endif