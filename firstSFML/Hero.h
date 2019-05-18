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
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
	}
	bool checkCoin(Block &obj2) {
		cout << "Checking ";
		if (obj2.getTexture() == coin) {
			cout << " coin" << endl;
			return obj2.hideCoin();
		}
		cout << " not coin" << endl;
		return false;
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
			inJump = false;
			onLeftStair = false;
			onRightStair = false;
			upArrowPressed = false;
			downArrowPressed = false;
			setPos({ 450, 250 });
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