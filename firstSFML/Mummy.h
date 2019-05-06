#pragma once
#include "pch.h"

class Mummy : public Actor {
	enum mummyMovement move;
public:
	Mummy(sf::Vector2f size) : Actor(size) { // ęîíńňđóęňîđ, ďîëó÷ŕĺě đŕçěĺđ
		object.setFillColor(sf::Color::White);
	}

};