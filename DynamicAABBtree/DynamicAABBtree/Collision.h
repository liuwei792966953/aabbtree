#pragma once
#include <SFML/Graphics.hpp>

bool contains(sf::FloatRect A, sf::FloatRect B);
bool overlap(sf::FloatRect A, sf::FloatRect B);
float area(sf::FloatRect A);
sf::FloatRect merge(sf::FloatRect A, sf::FloatRect B, float margin=0);