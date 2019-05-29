#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>

using namespace std;

class Block {
protected:
	sf::RectangleShape object;
	sf::Texture texture; // pointer to a picture
	sf::Sprite sprite;
	t_collided collision;
	t_texture skin = wall;
	bool coinCollected = false;
public:
	bool lockJump = true;
	
	// create instance of the class without initializing
	Block() {} 
	// initialize shape
	Block(sf::Vector2f size) { 
		object.setSize(size); 
		object.setFillColor(sf::Color::Green);
	}
	// initialize shape and set texture
	Block(sf::Vector2f size, string fname) { 
		object.setSize(size); 
		object.setFillColor(sf::Color::Green);
		// making sprite with the same parameters
		if (!texture.loadFromFile(fname)) {
			myLog(Logger::ERR) << "image load failed!" << endl;
		}
		sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)); // load full picture
		sprite.setTexture(texture);
		sprite.setScale({size.x / texture.getSize().x , size.y / texture.getSize().y });
	}
	//noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8
	// at the beginning of the lap, no collision
	void annulateCollision() { 
		collision = no;
	}
	// return the coords of the senter of shape
	sf::Vector2f getSenter() { 
		return { object.getPosition().x + object.getSize().x / 2 , object.getPosition().y + object.getSize().y / 2 };
	}
	// return the coords of the top left corner of shape
	sf::Vector2f getCoord() { 
 		return object.getPosition();
	}
	// draw shape or texture to the window
	void drawTo(sf::RenderWindow &window) { 
		if (skin != noTexture) {
			if(xRay)
				window.draw(object);
			else
				window.draw(sprite);
		}
	}
	// move the top left corner of shape 
	void setPos(sf::Vector2f newPosition) { 
		object.setPosition(newPosition);
		if(skin == stairLeft || skin == stairLeftTop)
			sprite.setPosition({ newPosition.x + PLAYER_SIZE_X / 3, newPosition.y }); // not proper begin moving on stairs
		else if (skin == stairRight || skin == stairRightTop)
			sprite.setPosition({ newPosition.x - PLAYER_SIZE_X / 3, newPosition.y });
		else
			sprite.setPosition(newPosition);
	}
	// get height and width
	sf::Vector2f getSize() { 
		return object.getSize();
	}
	// get enum of the current texture
	t_texture getTexture() { 
		return skin;
	}
	// initialize texture enum, shape, coose and set texture
	void create(t_texture nskin, int current_level) { 
		skin = nskin;
		switch (skin) {
		case noTexture: {
			sf::Vector2f size(BLOCK_SIZE_X, BLOCK_SIZE_Y);
			object.setSize(size);
			object.setFillColor(sf::Color::White);
			// making the same parameters for sprites
			if (!texture.loadFromFile("images/empty.png")) {
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
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
				myLog(Logger::ERR) << "image load failed!" << endl;
			}
			sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
			sprite.setTexture(texture);
			sprite.setScale({ size.x / texture.getSize().x , size.y / texture.getSize().y });
			break;
		}
		}
	}
	// set empty texture to coin
	void hideCoin() { 
		if (!texture.loadFromFile("images/empty.png")) {
			myLog(Logger::ERR) << "image load failed!" << endl;
		}
		skin = noTexture;
		myLog(Logger::INFO) << "Got that coin" << endl;
	}
};