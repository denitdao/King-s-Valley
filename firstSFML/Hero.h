#include "pch.h"

class Hero : public Actor {
	enum heroMovement move;
public:
	Hero(sf::Vector2f size) : Actor(size) { //
		object.setFillColor(sf::Color::Yellow);
	}
	void controle(sf::RenderWindow &window) {
		sf::Event _event;
		// keypress detection

		while (window.pollEvent(_event)) {
			switch (_event.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyReleased: {
				if (sf::Keyboard::Up)
					upArrowPressed = false;
				if (sf::Keyboard::Down)
					downArrowPressed = false;
				break;
			}
			}
		}

		if (inJump == false && !lockJump) {
			setDir(none);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // go right
				setDir(toright);
				if (onRightStair) {
					moveOn({ x_move_speed, -x_move_speed }); // up right
				}
				else if (onLeftStair) {
					moveOn({ x_move_speed, x_move_speed }); // down right
				}
				else {
					if (collision != rColl && collision == bColl) {
						moveOn({ x_move_speed, 0 }); // right
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // go left				
				setDir(toleft);
				if (onLeftStair) {
					moveOn({ x_move_speed, -x_move_speed }); // up left
				}
				else if (onRightStair) {
					moveOn({ x_move_speed, x_move_speed }); // down left
				}
				else {
					if (collision != lColl && collision == bColl) {
						moveOn({ x_move_speed, 0 }); // left
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // go stair up
				upArrowPressed = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // go stair down
				downArrowPressed = true;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // jump
			if (!onLeftStair && !onRightStair)
				inJump = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			inJump = false;
			onLeftStair = false;
			onRightStair = false;
			upArrowPressed = false;
			downArrowPressed = false;
			setPos({ 450, 250 });
		}
		jump();
	}
};