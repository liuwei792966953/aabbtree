#include "Collision.h"

bool contains(sf::FloatRect A, sf::FloatRect B) {
	return	B.top <= A.top &&
			B.left <= A.left &&
			A.top + A.height <= B.top + B.height &&
			A.left + A.width <= B.left + B.width;
}

bool overlap(sf::FloatRect A, sf::FloatRect B) {
	return !(B.top - (A.top + A.height) > 0.0f ||
			B.left - (A.left + A.width) > 0.0f ||
			A.top - (B.top + B.height) > 0.0f ||
			A.left - (B.left + B.width) > 0.0f);
}

float area(sf::FloatRect A) {
	return A.width + A.height;
}
sf::FloatRect merge(sf::FloatRect A, sf::FloatRect B,float margin) {
	int x = std::min(A.left, B.left);
	int y = std::min(A.top, B.top);
	return sf::FloatRect(x-margin,y-margin,
		std::max(A.left + A.width, B.left + B.width) - x + margin*2,
		std::max(A.top + A.height, B.top + B.height) - y + margin*2);
}