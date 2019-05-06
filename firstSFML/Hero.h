#pragma once
#include "pch.h"

class Hero : public Actor {
	enum heroMovement move;
public:
	Hero(sf::Vector2f size) : Actor(size) { // конструктор, получаем размер
		object.setFillColor(sf::Color::Yellow);
	}
	void controle() {
		if (inJump == false && !lock) {
			setDir(none);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // go right
					setDir(toright);
				if (collision != rcoll && onGround) {
					moveOn({ x_move_speed, 0 });
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // go left				
					setDir(toleft);
				if (collision != lcoll && onGround) {
					moveOn({ x_move_speed, 0 });
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // jump
				if (collision != tcoll)
				moveOn({ 0, -x_move_speed * 5.0f });
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // jump
			//if (onGround)
			if (!lock)
			inJump = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			
			inJump = false;
			setPos({ 500, 536 });
		}
		jump();
		}
};