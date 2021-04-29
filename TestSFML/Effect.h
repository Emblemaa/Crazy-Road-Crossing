#ifndef Effect_h
#define Effect_h

#include"CONSTANTS.h"

class Effect_Victory
{
private:
	sf::Sprite sprite;
	sf::RectangleShape rect;
	float scale, delay;
public:
	Effect_Victory();
	void loadTexture(sf::Texture* tx, int idx);
	void Update();
	float getDelay();
	void Reset();
	sf::Sprite getSprite();
	sf::RectangleShape getRect();
};

#endif // !Effect_h



