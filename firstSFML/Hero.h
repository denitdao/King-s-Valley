#include "pch.h"

class Hero : public Actor {
	enum heroMovement move;
	string playerTexture[2][3] = { { "images/player_left_0.png", "images/player_left_1.png", "images/player_left_2.png" }, 
								  { "images/player_right_0.png", "images/player_right_1.png", "images/player_right_2.png" } };
	t_textureDir tDirection = leftTexture;
	int textureCounter = 1;
	float lastPositionX;
	const float deltaPositionX = 10.f;
public:
	Hero(sf::Vector2f size, string fname) : Actor(size) { //
		object.setFillColor(sf::Color::Yellow);
		if (!texture.loadFromFile(fname)) {
			cout << "image load failed!" << endl;
		}
		isPlayer = true;
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
	}
	void chooseTexture() {
		if (inJump == true) {
			this->texture.loadFromFile(playerTexture[tDirection][0]);
		}
		else if(!leftArrowPressed && !rightArrowPressed){
			this->texture.loadFromFile(playerTexture[tDirection][1]);
			textureCounter = 0;
		}
		else {
			this->texture.loadFromFile(playerTexture[tDirection][textureCounter]);
		}
		if (abs(lastPositionX - this->getCoord().x) >= deltaPositionX) {
			lastPositionX = this->getCoord().x;
			textureCounter++;
			if (textureCounter >= 3)
				textureCounter = 0;
		}
	}
	void autoMoveOn(sf::Vector2f distance, t_direcrion autoDir) {
		distance.x *= autoDir;
		if (autoDir == toleft) {
			tDirection = leftTexture;
			leftArrowPressed = true;
			rightArrowPressed = false;
		}
		if (autoDir == toright) {
			tDirection = rightTexture;
			rightArrowPressed = true;
			leftArrowPressed = false;
		}
		object.move(distance);
		sprite.move(distance);
		chooseTexture();
	}
	void controle(sf::RenderWindow &window) {
		sf::Event _event;
		// keypress detection

		while (window.pollEvent(_event)) {
			switch (_event.type) {
			case sf::Event::Closed: {
				window.close();
				exit(0);
			}
			case sf::Event::KeyReleased: {
				if (sf::Keyboard::Up) 
					upArrowPressed = false;
				if (sf::Keyboard::Down) 
					downArrowPressed = false;
				if (sf::Keyboard::Left) {
					textureCounter = 1;
					leftArrowPressed = false;
				}
				if (sf::Keyboard::Right) {
					textureCounter = 1;
					rightArrowPressed = false;
				}
				break;
			}
			}
		}

		if (inJump == false && !lockJump) {
			setDir(none);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // go right
				setDir(toright);
				tDirection = rightTexture;
				rightArrowPressed = true;
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
				tDirection = leftTexture;
				leftArrowPressed = true;
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
			respawn();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			exit(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			xRay = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			xRay = false;
		}
		jump();
		this->chooseTexture();
	}
};