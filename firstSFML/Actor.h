#pragma once
#include "pch.h"
// ôàéë, õðàíÿùèé îïèñàíèå êëàññà "Ïåðñîíàæ"

class Actor : public Block {
protected:
	t_direcrion dir;
	float yJumpSpeed = gravity_speed;
	const int groundHeight = 600; // êîñòûëü
public:
	t_condition cond;
	bool inJump = false;
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
	int k = 0;



	void jump() {

		std::cout << "inJump - " << ((inJump) ? "true" : "false") << std::endl;
		if (inJump == true) {
			onGround = false;
			moveOn({ x_move_speed, yJumpSpeed });
			std::cout << "Jumping on { " << x_move_speed << " ; " << yJumpSpeed << " }" << std::endl;
			yJumpSpeed += jump_change_step;
		}
		else {
			std::cout << "Falling down, Y  " << -gravity_speed << std::endl;

			moveOn({ 0, -gravity_speed });
			if (collision == bcoll || collision == tcoll || collision == rcoll || collision == lcoll) {
				initJumpSpeed();
				lock = true;
			}

		}
		if (collision == bcoll || collision == tcoll || collision == rcoll || collision == lcoll) {
			inJump = false;
		}
	}

	void checkCollision(Block &obj2) {
		this->senterCalc();
		obj2.senterCalc();
		float deltaX = this->senterCoord.x - obj2.senterCoord.x;
		float deltaY = this->senterCoord.y - obj2.senterCoord.y;
		float intersectX = abs(deltaX) - (this->getSizeX() / 2 + obj2.getSizeX() / 2); // < 0
		float intersectY = abs(deltaY) - (this->getSizeY() / 2 + obj2.getSizeY() / 2); // < 0

		if (intersectX < 0.0f && intersectY < 0.0f) {
			//collision = colliding;
			std::cout << "Colliding | intersectX = " << intersectX << "| intersectY = " << intersectY << std::endl;
			if (intersectY < intersectX) {
				if (deltaX < 0) { // right intersect
					collision = rcoll;
					std::cout << "right intersect, move X on " << intersectX << std::endl;
					setPos({ obj2.senterCoord.x - (this->getSizeX() + obj2.getSizeX() / 2) , this->getCoordY() });
					//this->moveOn({ x_move_speed, 0 });
					//comment
				}
				if (deltaX > 0) { // left intersect
					collision = lcoll;
					std::cout << "left intersect, move X on " << intersectX << std::endl;
					setPos({ obj2.senterCoord.x + obj2.getSizeX() / 2, this->getCoordY() });
					//this->moveOn({x_move_speed, 0 });
				}
			}
			else {
				if (deltaY < 0) {
					collision = bcoll;
					onGround = true;
					inJump = false;
					lock = false;
					std::cout << "bottom intersect, move Y on " << intersectY << std::endl; // bottom intersect
					this->moveOn({ 0, intersectY });
				}
				if (deltaY > 0) { // top intersect
					collision = tcoll;
					std::cout << "top intersect, move Y on " << -intersectY << std::endl;
					this->moveOn({ 0, -intersectY });
				}
			}
			return;
		}

		std::cout << "Not colliding" << std::endl;
		return;
	}
};