#include "pch.h"

class Hero : public Actor {
	string playerTexture[2][3] = { { "images/player_left_0.png", "images/player_left_1.png", "images/player_left_2.png" }, 
								  { "images/player_right_0.png", "images/player_right_1.png", "images/player_right_2.png" } };
	t_textureDir tDirection = leftTexture; // enum to choose part of the first dimention of the texture array
	int textureCounter = 1; // counter to choose texture in the second dimention of the texture array
	float lastPositionX;
public:
	// initialize sprite whith a texture
	Hero(sf::Vector2f size, string fname) : Actor(size) { 
 		object.setFillColor(sf::Color::Yellow);
		if (!texture.loadFromFile(fname)) {
			myLog(Logger::ERR) << "image load failed!" << endl;
		}
		isPlayer = true;
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
	}
	// change textures while moving
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
		if (abs(lastPositionX - this->getCoord().x) >= CHANGE_TEXTURE_DELTA_X) {
			lastPositionX = this->getCoord().x;
			textureCounter++;
			if (textureCounter >= 3)
				textureCounter = 0;
		}
	}
	// auto move player
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
	// keypress detection
	void controle(sf::RenderWindow &window, Scoreboard &board) {
		sf::Event _event;

		while (window.pollEvent(_event)) {
			switch (_event.type) {
			case sf::Event::Closed: {
				window.close();
				exit(0);
			}
			case sf::Event::KeyReleased: {
				if (_event.key.code == sf::Keyboard::Up) {
					upArrowPressed = false;
					myLog(Logger::DEBUG) << "Key up released" << endl;
				}
				if (_event.key.code == sf::Keyboard::Down) {
					downArrowPressed = false;
					myLog(Logger::DEBUG) << "Key down released" << endl;
				}
				if (_event.key.code == sf::Keyboard::Left) {
					textureCounter = 1;
					leftArrowPressed = false;
					myLog(Logger::DEBUG) << "Key Left released" << endl;
				}
				if (_event.key.code == sf::Keyboard::Right) {
					textureCounter = 1;
					rightArrowPressed = false;
					myLog(Logger::DEBUG) << "Key Right released" << endl;
				}
				if (_event.key.code == sf::Keyboard::H) {
					this->respawn();
					board.looseHeart();
					myLog(Logger::DEBUG) << "Key H released" << endl;
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
					moveOn({ X_MOVE_SPEED, -X_MOVE_SPEED }); // up right
				}
				else if (onLeftStair) {
					moveOn({ X_MOVE_SPEED, X_MOVE_SPEED }); // down right
				}
				else {
					if (collision != rColl && collision == bColl) {
						moveOn({ X_MOVE_SPEED, 0 }); // right
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // go left				
				setDir(toleft);
				tDirection = leftTexture;
				leftArrowPressed = true;
				if (onLeftStair) {
					moveOn({ X_MOVE_SPEED, -X_MOVE_SPEED }); // up left
				}
				else if (onRightStair) {
					moveOn({ X_MOVE_SPEED, X_MOVE_SPEED }); // down left
				}
				else {
					if (collision != lColl && collision == bColl) {
						moveOn({ X_MOVE_SPEED, 0 }); // left
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