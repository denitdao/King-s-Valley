#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>

using namespace std;

class Block {
protected:
	sf::RectangleShape object;
	t_collided collision;
	t_texture skin = wall;
public:
	bool lockJump = true;
	Block() {}
	Block(sf::Vector2f size) { //
		object.setSize(size); //
		object.setFillColor(sf::Color::Green);
	}
	//noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8
	void annulateCollision() { // at the beginning of the lap, no collision
		collision = no;
	}
	sf::Vector2f getSenter() { // return center of shape
		return { object.getPosition().x + object.getSize().x / 2 , object.getPosition().y + object.getSize().y / 2 };
	}
	sf::Vector2f getCoord() {
		return object.getPosition();
	}
	void drawTo(sf::RenderWindow &window) {
		if (skin != noTexture)
			window.draw(object);
	}
	void setPos(sf::Vector2f newPosition) {
		object.setPosition(newPosition);
	}
	sf::Vector2f getSize() {
		return object.getSize();
	}
	t_texture getTexture() {
		return skin;
	}
	void create(t_texture nskin) { //
		skin = nskin;
		switch (skin) {
		case noTexture: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::White);
			break;
		}
		case wall: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Yellow);
			break;
		}
		case stairLeftUnder: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Blue);
			break;
		}
		case stairLeft: {
			object.setSize({ 2 * BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Blue);
			break;
		}
		case stairLeftTop: {
			object.setSize({ 2 * BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Blue);
			break;
		}
		case stairRightUnder: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Cyan);
			break;
		}
		case stairRight: {
			object.setSize({ 2 * BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Cyan);
			break;
		}
		case stairRightTop: {
			object.setSize({ 2 * BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Cyan);
			break;
		}
		case hardWall: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Magenta);
			break;
		}
		case coin: {
			object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
			object.setFillColor(sf::Color::Magenta);
			break;
		}
		}
	}
};