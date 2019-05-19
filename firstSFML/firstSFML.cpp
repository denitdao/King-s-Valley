#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;

int main() {
	sf::Clock clock;
	float elapsed = 0;
	
	Scoreboard board;
	Block **map = new Block*[MAX_MAP_SIZE_X];
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		map[i] = new Block[MAP_SIZE_Y];
	}
	Controle level;

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
	window.setFramerateLimit(100);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/player_left_1.png");
		player.setPos({ 500.f, 500.f });

		Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
		bot1.setPos({ 400.f, 288.f });
		Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
		bot2.setPos({ 350.f, 320.f });


		// Gravity variables:
		//bool gameBegin;
		bool nextLevel = true;
		level.current_level = 1;

		while (window.isOpen()) {
			if (coinAmount == 1) {
				level.current_level++;
				nextLevel = true;
			}
			cout << "_______New Lap________" << endl;
			if (nextLevel) {
				switch (level.current_level) {
				case 0: {
					level.openMap(map, "levels/level_1_blocks.txt");
					break;
				}
				case 1: {
					level.openMap(map, "levels/level_2_blocks.txt");
					break;
				}
				case 2: {
					level.openMap(map, "levels/level_3_blocks.txt");
					break;
				}
				}
				cout << "Change of the level" << endl;
				nextLevel = false;
				Sleep(2000);
			}

			player.controle(window);

			int xMap = player.getSenter().x / BLOCK_SIZE_X;
			int yMap = player.getSenter().y / BLOCK_SIZE_X;

			if (level.getMapSizeX() >= 32) {
				if (xMap == 31) {
					player.setPos({ player.getSize().x, player.getCoord().y });
					level.changeMapPart();
					xMap = 1;
				}
				else if (xMap == 0) {
					player.setPos({ WINDOW_SIZE_X - player.getSize().x * 2.f, player.getCoord().y });
					level.changeMapPart();
					xMap = 28;
				}
			}
			if (level.getMapPart() == 2) {
				xMap += 32;
			}
			cout << "xMap = " << xMap << " yMap = " << yMap << endl;
			cout << "In map part = " << level.getMapPart() << endl;

			player.annulateCollision(); // if won't be any collisions, value won't change from 'no'
			// checking collision of player
			player.checkCollision(map[xMap][yMap + 1]); // bottom
			if (!player.onLeftStair && !player.onRightStair) {
				if (player.inJump == false) {
					player.checkCollision(map[xMap - 1][yMap - 1]); // left top
					player.checkCollision(map[xMap + 1][yMap - 1]); // right top
					player.checkCollision(map[xMap][yMap - 1]); // top
					player.checkCollision(map[xMap + 1][yMap]); // right
					player.checkCollision(map[xMap - 1][yMap]); // left
				}
				if (player.checkCoin(map[xMap + 1][yMap + 1])) {
					board.addPoint();
				}
				player.checkCollision(map[xMap + 1][yMap + 1]);// r b 
				player.checkCollision(map[xMap - 1][yMap + 1]); // b l
			}

			if (player.checkCollision(bot1) == 2) {
				//player.respawn();
				// you lost
			}
			//if (player.checkCollision(bot2) == 2) {
				// you lost
			//}


			bot1.annulateCollision();
			bot2.annulateCollision();


			window.clear();

			level.drawTo(window, map);
			bot1.drawTo(window);
			//bot2.drawTo(window);
			player.drawTo(window);

			/*
			elapsed = clock.restart().asMilliseconds();
			gravity_speed = GRAVITY_SPEED_CONST * elapsed;
			x_move_speed = X_MOVE_SPEED_CONST * elapsed;
			jump_change_step = JUMP_CHANGE_STEP_CONST * elapsed;
			cout << elapsed << endl;
			*/

			/*//Alex
			gravity_speed = GRAVITY_SPEED_CONST1;
			x_move_speed = X_MOVE_SPEED_CONST1;
			jump_change_step = JUMP_CHANGE_STEP_CONST1;*/
			//Denys
			gravity_speed = GRAVITY_SPEED_CONST;
			x_move_speed = X_MOVE_SPEED_CONST;
			jump_change_step = JUMP_CHANGE_STEP_CONST;

			window.display();
		}
		/*
		for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
			 delete map[i];
		}
		delete map;*/
		return 0;
	}