#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Randomizer.h"
#include "CONSTANTS.h"

class TrafficLight
{
private:
	std::vector<sf::Shape*> shape;

	float timeMax;
	float greenTime;
	float yellowTime;
	float redTime;
	float timer;

	int state;
public:
	TrafficLight(const bool& side, const int& lane);
	void render(sf::RenderWindow* window);
	void update_light();
	int get_state();

	void save(std::ofstream& out);
	void load(std::ifstream& in);
	~TrafficLight();
};

#endif