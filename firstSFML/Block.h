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
	bool onGround = true;
	bool lock = true;
	sf::Vector2f senterCoord;
	Block() {
		//object.setSize({ BLOCK_SIZE_X, BLOCK_SIZE_Y });
	}
	Block(sf::Vector2f size) { //
		object.setSize(size); //
		object.setFillColor(sf::Color::Green);
	}
	//noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8
	void annulateCollision() { // at the beginning of the lap, no collision
		collision = no;
		onGround = false;
		if (!lock)
			lock = false;
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
		}
	}
	sf::Vector2f senterCalc() { // return center of shape
		senterCoord.x = object.getPosition().x + object.getSize().x / 2;
		senterCoord.y = object.getPosition().y + object.getSize().y / 2;
		return { senterCoord.x , senterCoord.y };
	}
	float getCoordX() {
		return object.getPosition().x;
	}
	float getCoordY() {
		return object.getPosition().y;
	}
	void drawTo(sf::RenderWindow &window) {
		if (skin != noTexture)
			window.draw(object);
	}
	void setPos(sf::Vector2f newPosition) {
		object.setPosition(newPosition);
	}
	float getSizeX() {
		return object.getSize().x;
	}
	float getSizeY() {
		return object.getSize().y;
	}
	sf::Vector2f getSize() {
		return object.getSize();
	}
	t_texture getTexture() {
		return skin;
	}
	void drawTo(sf::RenderWindow &window, Block newMap[MAP_SIZE_X][MAP_SIZE_Y]) {
		for (int j = 0; j < MAP_SIZE_Y; j++) { // all except stair parts
			for (int i = 0; i < MAP_SIZE_X; i++) {
				if (newMap[i][j].getTexture() != stairLeftTop
					|| newMap[i][j].getTexture() != stairRightTop
					|| newMap[i][j].getTexture() != stairLeftUnder
					|| newMap[i][j].getTexture() != stairRightUnder)
					newMap[i][j].drawTo(window);
			}
		}
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			for (int i = 0; i < MAP_SIZE_X; i++) { // only stair parts
				if (newMap[i][j].getTexture() == stairLeftTop
					|| newMap[i][j].getTexture() == stairRightTop
					|| newMap[i][j].getTexture() == stairLeftUnder
					|| newMap[i][j].getTexture() == stairRightUnder)
					newMap[i][j].drawTo(window);
			}
		}
	}
	void openMap(Block newMap[MAP_SIZE_X][MAP_SIZE_Y], const char level[19]) {
		ifstream mapPtr(level);
		if (!mapPtr) {
			cout << "error opening file - not exists" << endl;
			exit(1);
		}
		char ch;
		for (int j = 0; j < 24; j++) {
			for (int i = 0; i < 32; i++) {
				mapPtr.get(ch);
				switch (ch) {
				case '0': {
					newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					newMap[i][j].create(noTexture);
					break;
				}
				case '1': {
					newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					newMap[i][j].create(wall);
					break;
				}
				case '2': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairLeftUnder);
					break;
				}
				case '3': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairLeft);
					break;
				}
				case '4': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairLeftTop);
					break;
				}
				case '5': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairRightUnder);
					break;
				}
				case '6': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairRight);
					break;
				}
				case '7': {
					newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					newMap[i][j].create(stairRightTop);
					break;
				}
				case '8': {
					newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					newMap[i][j].create(hardWall);
					break;
				}
				}
				cout << ch;
			}
			mapPtr.get(ch); // to read \n symbol
			cout << endl;
		}
		mapPtr.close();
	}
};