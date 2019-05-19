#pragma once
#include "pch.h"

class Mummy : public Actor {
	enum mummyMovement move;
	string left_texture[3] = { "images/mummy_left_0.png", "images/mummy_left_1.png", "images/mummy_left_2.png" };
public:
	Mummy(sf::Vector2f size, string fname) : Actor(size) { // 
		object.setFillColor(sf::Color::White);
		if (!texture.loadFromFile(fname)) {
			cout << "image load failed!" << endl;
		}
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		skin = bot;
		sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
	}

};