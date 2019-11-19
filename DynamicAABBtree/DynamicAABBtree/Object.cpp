#include "Object.h"

int object_count=0;

Object::Object(float x, float y):id (object_count++) {
	sprite.setFillColor(sf::Color::Red);
	sprite.setSize(sf::Vector2f(15.f,15.f));
	sprite.setOrigin(sf::Vector2f(5.f, 5.f));
	sprite.setPosition(sf::Vector2f(x,y));
	mask = sprite.getGlobalBounds();
	xspeed = 1, yspeed = 1;
}

void Object::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}
void Object::step() {
	mask.left = sprite.getPosition().x - sprite.getOrigin().x;
	mask.top = sprite.getPosition().y - sprite.getOrigin().y;
	if (mask.left + xspeed < 0 || mask.left + mask.width + xspeed > 500)
		xspeed = -xspeed;
	if (mask.top + yspeed < 0 || mask.top + mask.height + yspeed > 500)
		yspeed = -yspeed;
	sprite.setPosition(sprite.getPosition() + sf::Vector2f(xspeed, yspeed));
	sprite.setFillColor(sf::Color::Red);
}