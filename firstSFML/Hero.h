#pragma once
#include "pch.h"

class Hero : public Actor {
	enum heroMovement move;
public:
	Hero(sf::Vector2f size) : Actor(size) { // конструктор, получаем размер
		object.setFillColor(sf::Color::Yellow);
	}
	void controle() {
		if (inJump == false) {
			setDir(none);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // go right
				setDir(toright);
				moveOn({ x_move_speed, 0 });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // go left
				setDir(toleft);
				moveOn({ x_move_speed, 0 });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // jump
				moveOn({ 0, -x_move_speed * 10.f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // jump
				inJump = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			setPos({ 500, 536 });
		}
		jump();
	}
};