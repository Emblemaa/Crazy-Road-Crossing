#include "Row.h"

Row::Row(const bool& direction, const int& lane) : light(direction, lane)
{
	pause = false;
	this->pause = pause;
	movingDirection = direction;
	this->lane = lane;
	Obstacle* t;
	spawn_enemy();
}

bool Row::check_collide(const sf::FloatRect& player)
{
	for (Obstacle* i : obstacles)
		if (i->collide(player))
			return true;
	return false;
}

void Row::move_obstacles()
{
	for (Obstacle* i : obstacles)
		i->move();
}

void Row::set_obstacles_speed(const float& speed)
{
	for (Obstacle* i : obstacles)
		i->set_speed(speed);
}

void Row::update()
{
	if (!pause)
	{
		switch (light.get_state())
		{
		case 0: set_obstacles_speed(OBSTACLE_SPEED);
			break;
		case 1: set_obstacles_speed(OBSTACLE_SPEED / 3);
			break;
		case 2: set_obstacles_speed(0);
			break;
		}
		move_obstacles();
		light.update_light();
	}
}

void Row::render(sf::RenderWindow* window)
{
	for (Obstacle* i : obstacles)
		i->render(window);
	light.render(window);
	
}

Obstacle* Row::get_random_obstacle(const float& x)
{
	Obstacle* obs = nullptr;
	int type = Randomizer::random(0, 2);
	switch (type)
	{
	case 0:
		obs = new Car({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	case 1:
		obs = new Truck({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	case 2:
		obs = new Dinosaur({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	}
	return obs;
}

Obstacle* Row::get_obstacle(int type, const float& x)
{
	Obstacle* obs = nullptr;
	switch (type)
	{
	case 0:
		obs = new Car({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	case 1:
		obs = new Truck({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	case 2:
		obs = new Dinosaur({ x,LOWEST_LANE_Y - OBSTACLE_BLOCK_HEIGHT - GAP * lane }, OBSTACLE_SPEED, movingDirection);
		break;
	}
	return obs;
}

void Row::spawn_enemy()
{
	sf::sleep(sf::milliseconds(200));
	int rand_min = 200;
	int rand_max = 250;

	if (!obstacles.empty())
	{
		for (Obstacle* i : obstacles)
			delete i;
		obstacles.clear();
	}

	float firstPos = Randomizer::random(20, 1140);
	obstacles.push_back(get_random_obstacle(firstPos));

	//	left
	float tmpPos = firstPos;
	float distance;
	do
	{
		distance = Randomizer::random(rand_min, rand_max);
		tmpPos -= distance;
		if (tmpPos >= 0)
			obstacles.push_back(get_random_obstacle(tmpPos));
	} while (tmpPos >= 0);

	//	right
	tmpPos = firstPos;
	do
	{
		distance = Randomizer::random(rand_min, rand_max);
		tmpPos += distance;
		if (tmpPos <= PLAY_WINDOW_WIDTH)
			obstacles.push_back(get_random_obstacle(tmpPos));
	} while (tmpPos <= PLAY_WINDOW_WIDTH);
}

void Row::set_pause(const bool& state)
{
	pause = state;
}

void Row::save_rows(std::ofstream& out)
{
	//num of lane
	out << lane << '\n';
	//direction
	if (movingDirection) out << "1" << '\n';
	else out << "0" << '\n';

	//num obstacles
	out << this->obstacles.size() << '\n';
	//save obstacles
	for (int i = 0; i < this->obstacles.size(); ++i) {
		this->obstacles[i]->save(out);
	}
	//save light
	this->light.save(out);
}

void Row::load_rows(std::ifstream& in)
{
	//num of obstacles
	int numObstacles;
	in >> numObstacles;

	//load obstacles
	if (!obstacles.empty())
	{
		for (Obstacle* i : obstacles)
			delete i;
		obstacles.clear();
	}
	for (int i = 0; i < numObstacles; ++i) {
		float x;
		float speed;
		int type;
		in >> x >> speed >> type;
		obstacles.push_back(get_obstacle(type, x));
	}

	//load light
	this->light.load(in);
}

Row::~Row()
{
	for (Obstacle* i : obstacles)
		delete i;
}