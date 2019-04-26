#pragma once
#include "pch.h"
// файл, хранящий описание класса "Персонаж"

class Actor : public Block {
protected:
	t_direcrion dir;
	float yJumpSpeed = gravity_speed;
	const int groundHeight = 600; // костыль
public:
	t_condition cond;
	bool inJump = false;
	Actor(sf::Vector2f size) : Block(size) { // конструктор, получаем размер
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
		std::cout << "inJump - " <<((inJump) ? "true" : "false") << std::endl;
		if (inJump == true) {
			moveOn({x_move_speed, yJumpSpeed});
			std::cout << "Jumping on { " << x_move_speed << " ; " << yJumpSpeed <<" }" << std::endl;
			yJumpSpeed += jump_change_step;
		}
		else {
			if (collision != colliding)
				std::cout << "Falling down, Y  " << -gravity_speed << std::endl;
				moveOn({0, -gravity_speed });
		}
		if (collision == colliding) {
			initJumpSpeed();
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
			collision = colliding;
			std::cout << "Colliding | intersectX = " << intersectX << "| intersectY = " << intersectY << std::endl;
			if (intersectY < intersectX) {
				if (deltaX < 0) { // right intersect
					std::cout << "right intersect, move X on " << intersectX << std::endl;
					this->moveOn({ intersectX, 0 });
				}
				if (deltaX > 0) { // left intersect
					std::cout << "left intersect, move X on " << -intersectX << std::endl;
					this->moveOn({ -intersectX, 0 });
				}
			}
			else {
				if (deltaY < 0) {
					std::cout << "bottom intersect, move Y on " << intersectY << std::endl; // bottom intersect
					this->moveOn({ 0, intersectY });
				}
				if (deltaY > 0) { // top intersect
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