#pragma once
#include "pch.h"

class Mummy : public Actor {
	enum mummyMovement move;
public:
	Mummy(sf::Vector2f size) : Actor(size) { // конструктор, получаем размер
		object.setFillColor(sf::Color::White);
	}

};