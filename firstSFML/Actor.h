#include "pch.h"
//

class Actor : public Block {
protected:
	t_direcrion dir;
	float yJumpSpeed = gravity_speed;
public:
	bool inJump = false;
	bool onLeftStair = false;
	bool onRightStair = false;
	bool upArrowPressed = false;
	bool downArrowPressed = false;
	Actor(sf::Vector2f size) : Block(size) { //
		object.setFillColor(sf::Color::Blue);
		dir = none;
	}
	void moveOn(sf::Vector2f distance) {
		distance.x *= dir;
		object.move(distance);
	}
	void setDir(enum direction d) {
		dir = d;
	}
	void initJumpSpeed() {
		yJumpSpeed = gravity_speed;
	}
	void jump() {

		std::cout << "inJump - " << ((inJump) ? "true" : "false") << std::endl;
		if (inJump == true) {
			lockJump = true;
			//onGround = false;
			moveOn({ x_move_speed, yJumpSpeed });
			std::cout << "Jumping on { " << x_move_speed << " ; " << yJumpSpeed << " }" << std::endl;
			yJumpSpeed += jump_change_step;
			if (yJumpSpeed >= 10)
				yJumpSpeed = 0;
		}
		else {
			std::cout << "Falling down, Y  " << -gravity_speed << std::endl;
			lockJump = true;
			moveOn({ 0, -gravity_speed });
			if (collision == bColl) {
				initJumpSpeed();
			}
		}
		if (collision == bColl || collision == tColl || collision == rColl || collision == lColl) {
			inJump = false;
		}
	}

	void checkCollision(Block &obj2) {
		t_texture objSkin = obj2.getTexture();

		if (objSkin == 0)
			return;

		float deltaX = this->senterGet().x - obj2.senterGet().x;
		float deltaY = this->senterGet().y - obj2.senterGet().y;
		float intersectX = abs(deltaX) - (this->getSize().x / 2 + obj2.getSize().x / 2); // < 0
		float intersectY = abs(deltaY) - (this->getSize().y / 2 + obj2.getSize().y / 2); // < 0

		if (objSkin != stairLeft && objSkin != stairRight) {
			if (intersectX < 0.0f && intersectY < 0.0f) {
				std::cout << "Colliding | intersectX = " << intersectX << "| intersectY = " << intersectY << std::endl;

				if (intersectY < intersectX) {
					if (deltaX < 0) { // right intersect
						collision = rColl;
						std::cout << "right intersect, move X on " << intersectX << std::endl;
						setPos({ obj2.senterGet().x - (this->getSize().x + obj2.getSize().x / 2) , this->getCoord().y });
					}
					if (deltaX > 0) { // left intersect
						collision = lColl;
						std::cout << "left intersect, move X on " << intersectX << std::endl;
						setPos({ obj2.senterGet().x + obj2.getSize().x / 2, this->getCoord().y });
					}
				}
				else {
					if (deltaY < 0) { // bottom intersect
						collision = bColl;
						//inJump = false;
						lockJump = false;
						std::cout << "bottom intersect, move Y on " << intersectY << std::endl;
						setPos({ this->getCoord().x , obj2.senterGet().y - (this->getSize().y + obj2.getSize().y / 2) });
					}
					if (deltaY > 0) { // top intersect
						collision = tColl;
						std::cout << "top intersect, move Y on " << -intersectY << std::endl;
						setPos({ this->getCoord().x, obj2.senterGet().y + obj2.getSize().y / 2 });
					}
				}
				/*
				if (objSkin == stairLeftUnder && (int)this->getCoord().x == (int)obj2.senterGet().x) {
				if (this->upArrowPressed && this->dir == toleft) {
				this->onLeftStair = true;
				}
				else {
				this->onLeftStair = false;
				}
				cout << "change onLeftStair" << endl;
				}
				if (objSkin == stairRightUnder) {
				if (this->upArrowPressed && this->dir == toright) {
				this->onRightStair = true;
				}
				else {
				this->onRightStair = false;
				}
				cout << "change onRightStair" << endl;
				}
				if (objSkin == stairLeftTop) {
				if (this->downArrowPressed && this->dir == toright) {
				this->onLeftStair = true;
				}
				else {
				this->onLeftStair = false;
				}
				cout << "change onLeftStair" << endl;
				}
				if (objSkin == stairRightTop) {
				if (this->downArrowPressed && this->dir == toleft) {
				this->onRightStair = true;
				}
				else {
				this->onRightStair = false;
				}
				cout << "change onRightStair" << endl;
				}
				cout << "onLeftStair = " << this->onLeftStair << endl;
				cout << "onRightStair = " << this->onRightStair << endl;
				*/
				return;
			}
		}
		std::cout << "Not colliding" << std::endl;
		return;
	}
};