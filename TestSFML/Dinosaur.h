#ifndef DINASAUR_H
#define DINASAUR_H

#include "Obstacle.h"
class Dinosaur : public Obstacle
{
public:      
	Dinosaur(const sf::Vector2f& position, const float& speed, const bool& direction);
	void set_initial_position();
	void save(std::ofstream& out);
};

#endif