#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>

using namespace std;

class Block {
protected:
	sf::RectangleShape object;
	sf::Texture texture;
	sf::Sprite sprite;
	t_collided collision;
	t_texture skin = wall;
	bool coinCollected = false;
public:
	bool lockJump = true;
	
	Block() {}
	Block(sf::Vector2f size) { //
		object.setSize(size); //
		object.setFillColor(sf::Color::Green);
	}
	Block(sf::Vector2f size, string fname) { //
		object.setSize(size); //
		object.setFillColor(sf::Color::Green);
		// making sprite with the same parameters
		if (!texture.loadFromFile(fname)) {
			cout << "image load failed!" << endl;
		}
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		sprite.setTexture(texture);
		sprite.setScale({size.x / texture.getSize().x , size.y / texture.getSize().y });
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
		if (skin != noTexture) {
			if(xRay)
				window.draw(object);
			else
				window.draw(sprite);
		}
	}
	void setPos(sf::Vector2f newPosition) {
		object.setPosition(newPosition);
		if(skin == stairLeft || skin == stairLeftTop)
			sprite.setPosition({ newPosition.x + PLAYER_SIZE_X / 3, newPosition.y }); // not proper begin moving on stairs
		else if (skin == stairRight || skin == stairRightTop)
			sprite.setPosition({ newPosition.x - PLAYER_SIZE_X / 3, newPosition.y });
		else
			sprite.setPosition(newPosition);
	}
	sf::Vector2f getSize() {
		return object.getSize();
	}
	t_texture getTexture() {
		return skin;
	}
	void create(t_texture nskin, int current_level) { //
		skin = nskin;
		switch (skin) {
		case noTexture: {
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::White);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/empty.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case wall: {
			char wall[3][40] = { "images/brick_yellow.png", "images/brick_blue.png", "images/brick_green.png" };
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Yellow);
			// making the same parameters for sprites
			if (!texture.loadFromFile(wall[current_level])) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairLeftUnder: {
			string wall[3] = { "images/brick_yellow.png", "images/brick_blue.png", "images/brick_green.png" };
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Blue);
			// making the same parameters for sprites
			if (!texture.loadFromFile(wall[current_level])) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairLeft: {
			sf::Vector2f size(2 * BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Blue);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/stair_left.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairLeftTop: {
			sf::Vector2f size(2 * BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Blue);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/stair_left_top.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairRightUnder: {
			string wall[3] = { "images/brick_yellow.png", "images/brick_blue.png", "images/brick_green.png" };
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Cyan);
			// making the same parameters for sprites
			if (!texture.loadFromFile(wall[current_level])) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairRight: {
			sf::Vector2f size(2 * BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Cyan);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/stair_right.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case stairRightTop: {
			sf::Vector2f size(2 * BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Cyan);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/stair_right_top.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case hardWall: {
			string wall[3] = { "images/brick_yellow.png", "images/brick_blue.png", "images/brick_green.png" };
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Magenta);
			// making the same parameters for sprites
			if (!texture.loadFromFile(wall[current_level])) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		case coin: {
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::Magenta);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/treasure_1.png")) {
				cout << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		}
	}
	/*bool hideCoin() {
		if (!coinCollected) {
			cout << "Not collected" << endl;
			if (!texture.loadFromFile("images/empty.png")) {
				cout << "image load failed!" << endl;
			}
			cout << "Got that coin" << endl;
			coinCollected = true;
		}
		cout << "Now Collected" << endl;
		return coinCollected;
	}*/
	void hideCoin() {
		if (!texture.loadFromFile("images/empty.png")) {
			cout << "image load failed!" << endl;
		}
		skin = noTexture;
		cout << "Got that coin" << endl;
		cout << "Now Collected" << endl;
	}
};