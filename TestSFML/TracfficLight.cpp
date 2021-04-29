#include "TracfficLight.h"

TrafficLight::TrafficLight(const bool& side, const int& lane)
{
	yellowTime = 1000;
	greenTime = Randomizer::random(3000, 4000);
	redTime = Randomizer::random(1500, 2500);
	timeMax = 0;
	timer = 0;

	//	VỊ TRÍ TRAFFIC LIGHT BÊN PHẢI 
	const sf::Vector2f rightPosition = { PLAY_WINDOW_WIDTH - TRAFFIC_LIGHT_BLOCK_HEIGHT * 3, 
										LOWEST_LANE_Y - TRAFFIC_LIGHT_BLOCK_HEIGHT - lane * GAP};
	//	VỊ TRÍ TRAFFIC LIGHT BÊN TRÁI
	const sf::Vector2f leftPosition = { TRAFFIC_LIGHT_BLOCK_HEIGHT * 2, LOWEST_LANE_Y - TRAFFIC_LIGHT_BLOCK_HEIGHT - lane * GAP };

	// Tùy theo direction của lane mà mình sẽ set position bằng biến nào
	const sf::Vector2f position = side ? rightPosition : leftPosition;

	// blue: 0, yellow: 1, green: 2
	state = Randomizer::random(0, 2);

	sf::RectangleShape* rec;
	
	/*	 _____
	*	|  O  |
	*	|  O  | <- 2nd
	*	|  O  |
	*	|_   _|
	*	  |_|   <- 1st
	*/

	//1st
	rec = new sf::RectangleShape;
	rec->setSize({ 1 * TRAFFIC_LIGHT_BLOCK_HEIGHT, 1 * TRAFFIC_LIGHT_BLOCK_HEIGHT });
	rec->setPosition(position);
	shape.push_back(rec);

	//2nd
	rec = new sf::RectangleShape;
	rec->setSize({ 3 * TRAFFIC_LIGHT_BLOCK_HEIGHT, 4 * TRAFFIC_LIGHT_BLOCK_HEIGHT });
	rec->setPosition(position.x - TRAFFIC_LIGHT_BLOCK_HEIGHT, position.y - 4 * TRAFFIC_LIGHT_BLOCK_HEIGHT);
	shape.push_back(rec);

	for (auto& c : shape)
		c->setFillColor(sf::Color::Black);

	rec = new sf::RectangleShape;
	rec->setSize({ TRAFFIC_LIGHT_BLOCK_HEIGHT / 2,TRAFFIC_LIGHT_BLOCK_HEIGHT / 2 });
	rec->setPosition(position.x + TRAFFIC_LIGHT_BLOCK_HEIGHT * 0.25, position.y - 3.5 * TRAFFIC_LIGHT_BLOCK_HEIGHT);
	rec->setFillColor(sf::Color::White);
	shape.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ TRAFFIC_LIGHT_BLOCK_HEIGHT / 2,TRAFFIC_LIGHT_BLOCK_HEIGHT / 2 });
	rec->setPosition(position.x + TRAFFIC_LIGHT_BLOCK_HEIGHT * 0.25, position.y - 2.5 * TRAFFIC_LIGHT_BLOCK_HEIGHT);
	rec->setFillColor(sf::Color::White);
	shape.push_back(rec);

	rec = new sf::RectangleShape;
	rec->setSize({ TRAFFIC_LIGHT_BLOCK_HEIGHT / 2,TRAFFIC_LIGHT_BLOCK_HEIGHT / 2 });
	rec->setPosition(position.x + TRAFFIC_LIGHT_BLOCK_HEIGHT * 0.25, position.y - 1.5 * TRAFFIC_LIGHT_BLOCK_HEIGHT);
	rec->setFillColor(sf::Color::White);
	shape.push_back(rec);
}

void TrafficLight::update_light()
{
	if (state == 0)
		timeMax = greenTime;
	else if (state == 1)
		timeMax = yellowTime;
	else if (state == 2)
		timeMax = redTime;
	timer += 1.f;
	if (timer == timeMax)
	{
		state++;
		if (state == 3)
			state = 0;
		timer = 0;
	}
}

void TrafficLight::render(sf::RenderWindow* window)
{
	if (state == 0)
	{
		shape[2]->setFillColor(sf::Color::White);
		shape[4]->setFillColor(sf::Color::Green);
	}
	else if (state == 1)
	{
		shape[4]->setFillColor(sf::Color::White);
		shape[3]->setFillColor(sf::Color::Yellow);
	}
	else if (state == 2)
	{
		shape[3]->setFillColor(sf::Color::White);
		shape[2]->setFillColor(sf::Color::Red);
	}
	for (auto& i : shape)
		window->draw(*i);
}

int TrafficLight::get_state()
{
	return state;
}

void TrafficLight::save(std::ofstream& out)
{
	out << this->greenTime << '\n';
	out << this->redTime << '\n';
	out << this->state << '\n';
	out << this->timer << '\n';
}

void TrafficLight::load(std::ifstream& in)
{
	in >> this->greenTime;
	in >> this->redTime;
	this->yellowTime = 1000;
	in >> this->state;
	in >> this->timer;
}

TrafficLight::~TrafficLight()
{
	for (auto& c : shape)
		delete c;
}