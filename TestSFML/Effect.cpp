#include "Effect.h"
Effect_Victory::Effect_Victory()
{
	scale = 0.f;
	delay = 0.f;
}
void Effect_Victory::loadTexture(sf::Texture* tx, int idx)
{
	sprite.setTexture(tx[idx]);
	sprite.setOrigin(tx[idx].getSize().x / 2, tx[idx].getSize().y / 2);
	sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	sprite.setScale(0, 0);

	rect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	rect.setFillColor(sf::Color(0, 0, 0, 50));
}
void Effect_Victory::Update()
{
	if (scale < 1.5f) {
		scale += GAMESPEED / 100.f;
		sprite.setScale(scale, scale);
	}
	delay += GAMESPEED;
}
float Effect_Victory::getDelay() {
	return delay;
}
void Effect_Victory::Reset() {
	scale = 0.f; delay = 0.f;
	sprite.setScale(0, 0);
}
sf::Sprite Effect_Victory::getSprite() {
	return sprite;
}
sf::RectangleShape Effect_Victory::getRect() {
	return rect;
}