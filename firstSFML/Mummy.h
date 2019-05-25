#pragma once
#include "pch.h"

class Mummy : public Actor {
	enum mummyMovement move;
	string mummyTexture[2][3] = { { "images/mummy_left_0.png", "images/mummy_left_1.png", "images/mummy_left_2.png" },
	{ "images/mummy_right_0.png", "images/mummy_right_1.png", "images/mummy_right_2.png" } };
	t_textureDir tDirection = leftTexture;
	int textureCounter = 1;
	float lastPositionX;
	const float deltaPositionX = 10.f;
public:
	Mummy(sf::Vector2f size, string fname) : Actor(size) { // 
		object.setFillColor(sf::Color::White);
		if (!texture.loadFromFile(fname)) {
			myLog(Logger::ERR) << "image load failed!" << endl;
		}
		dir = toleft;
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		skin = bot;
		sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
	}
	void chooseTexture() {
		if (inJump == true) {
			this->texture.loadFromFile(mummyTexture[tDirection][0]);
		}
		else if (!leftArrowPressed && !rightArrowPressed) {
			this->texture.loadFromFile(mummyTexture[tDirection][1]);
			textureCounter = 0;
		}
		else {
			this->texture.loadFromFile(mummyTexture[tDirection][textureCounter]);
		}
		if (abs(lastPositionX - this->getCoord().x) >= deltaPositionX) {
			lastPositionX = this->getCoord().x;
			textureCounter++;
			if (textureCounter >= 3)
				textureCounter = 0;
		}
	}
	void autoMoveOn(sf::Vector2f distance) {
		if (rand() % 700 == 2) 
			dir = (dir == toleft) ? toright : toleft;
		if (dir == toleft) {
			tDirection = leftTexture;
			leftArrowPressed = true;
			rightArrowPressed = false;
		}
		if (dir == toright) {
			tDirection = rightTexture;
			rightArrowPressed = true;
			leftArrowPressed = false;
		}
		moveOn(distance);
		chooseTexture();
	}
};