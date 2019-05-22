#pragma once
#include "pch.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

/*   SCORE-004000 HI-006000 REST-04   */
class Scoreboard {
	sf::Font gameFont;
	sf::Text gameData;
	sf::Vector2f position{ 0, WINDOW_SIZE_Y - BLOCK_SIZE_Y };
	sf::Vector2f size{ WINDOW_SIZE_X, BLOCK_SIZE_Y };
	int score = 0;
	int topScore = 0;
	int rest = 3;
	string str1 = "  SCORE-", str2 = " HI-", str3 = " REST-0", str_score, str_top_score, str_rest;
public:
	Scoreboard() {
		if (!gameFont.loadFromFile("fonts/ponderosa.regular.ttf"))
			cout << "Failed loading fonts" << endl;
		gameData.setFont(gameFont);
		gameData.setCharacterSize(BLOCK_SIZE_Y / 4 * 3);
		gameData.setFillColor(sf::Color::White);
		gameData.setOutlineColor(sf::Color::Black);
		gameData.setOutlineThickness(BLOCK_SIZE_Y / 8);
		gameData.setString(str1 + str_score + str2 + str_top_score + str3 + str_rest);
		gameData.setPosition(position);
	}
	void addPoint(int add) {
		score += add; // coin = 500, level = 2000
		fillTable();
	}
	void loseHeart(int add) {
		rest -= 1; // coin = 500, level = 2000
		fillTable();
	}
	void annulatePoint() {
		score = 0;
		fillTable();
	}
	void fillTable() {
		stringstream ss;
		ss.setf(ios::right);
		ss.width(6);
		ss.fill('0');
		ss << score;
		str_score = ss.str();
		if (score > topScore) {
			topScore = score;
			str_top_score = str_score;
		}
		gameData.setString(str1 + str_score + str2 + str_top_score + str3 + str_rest);
	}
	void drawTo(sf::RenderWindow &window) {
		window.draw(gameData);
	}
};