#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

extern int object_count;

class Object {
public:
	int id,node = -1;
	int image_index=-1, image_speed = -1;
	float xspeed, yspeed;
	//void *userdata;

	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	sf::FloatRect mask;

	Object(float x, float y);
	void step();
	void draw(sf::RenderWindow &window);
};