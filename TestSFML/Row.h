#ifndef ROW_H
#define ROW_H

#include "Obstacle.h"
#include "TracfficLight.h"
#include "Truck.h"
#include "Dinosaur.h"
#include "Car.h"
#include "Randomizer.h"

class Row
{
private:
	std::vector<Obstacle*> obstacles;
	TrafficLight light;
	int lane;
	bool movingDirection;
	bool pause;
	Obstacle* get_random_obstacle(const float& x);
	Obstacle* get_obstacle(int type, const float& x);
public:
	Row(const bool& direction, const int& lane);
	bool check_collide(const sf::FloatRect& player);
	void move_obstacles();
	void set_obstacles_speed(const float& speed);
	void set_pause(const bool& state);

	void update();
	void render(sf::RenderWindow* window);
	void spawn_enemy();

	void save_rows(std::ofstream& out);
	void load_rows(std::ifstream& in);

	~Row();
};

#endif