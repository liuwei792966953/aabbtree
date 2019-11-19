#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include"Tree.h"

Tree tree;

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), L"Dynamic AABB Tree");
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	sf::RectangleShape rect(sf::Vector2f(15.f,15.f));
	rect.setFillColor(sf::Color::Yellow);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					int MouseX = sf::Mouse::getPosition(window).x;
					int MouseY = sf::Mouse::getPosition(window).y;
					tree.insert_object(MouseX, MouseY);
				}
			}
			//if (event.type == sf::Event::KeyPressed) {
			//	if (event.key.code == sf::Keyboard::A) {
			//	}
			//}
			//if (event.type == sf::Event::KeyReleased) {
			//	if (event.key.code == sf::Keyboard::A) {
			//	}
			//}
		}

		//60fps
		if (accumulator > ups) {
			accumulator -= ups;
			rect.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

			std::map<int, Object*>::iterator iter;

			for (iter = tree.objects.begin();iter != tree.objects.end();++iter) {
				iter->second->step();
				Object *o = tree.query(rect.getGlobalBounds());
				if (o != NULL) 
					o->sprite.setFillColor(sf::Color::Blue);
				tree.update_object(iter->first);
				tree.update();
			}
			window.clear();
			std::map<int, Node*>::iterator iter2;
			for (iter2 = tree.nodes.begin(); iter2 != tree.nodes.end(); ++iter2) {
				sf::Vertex line[] = {
					sf::Vertex(sf::Vector2f(iter2->second->mask.left,iter2->second->mask.top)),
					sf::Vertex(sf::Vector2f(iter2->second->mask.left + iter2->second->mask.width,iter2->second->mask.top)),
					sf::Vertex(sf::Vector2f(iter2->second->mask.left + iter2->second->mask.width,iter2->second->mask.top + iter2->second->mask.height)),
					sf::Vertex(sf::Vector2f(iter2->second->mask.left,iter2->second->mask.top + iter2->second->mask.height)),
					sf::Vertex(sf::Vector2f(iter2->second->mask.left,iter2->second->mask.top)),
				};
				window.draw(line,5,sf::LineStrip);
			}
			for (iter= tree.objects.begin();iter != tree.objects.end();++iter)
				iter->second->draw(window);
			window.draw(rect);
			window.display();
		}
		accumulator += clock.restart();
	}

	return 0;
}