#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;


void changeScreen(sf::RenderWindow &window, string nameScreen) {
	sf::Sprite startScreen;
	sf::Texture startTexture;
	if (!startTexture.loadFromFile(nameScreen)) {
		cout << "image load failed!" << endl;
	}
	startScreen.setTexture(startTexture);
	startScreen.setTextureRect(sf::IntRect(0, 0, startTexture.getSize().x, startTexture.getSize().y));
	startScreen.setScale(WINDOW_SIZE_X / startTexture.getSize().x, WINDOW_SIZE_Y / startTexture.getSize().y);
	window.clear();
	window.draw(startScreen);
	window.display();
	while (true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
			if (nameScreen == "images/ending_screen.png") {
				exit(1);
			}
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			exit(1);
		Sleep(10);
	}
}


int gamePlay(sf::RenderWindow &window) {
	sf::Clock clock;
	float elapsed = 0;
	window.clear();
	Scoreboard board;
	Block **map = new Block*[MAX_MAP_SIZE_X];
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		map[i] = new Block[MAP_SIZE_Y];
	}
	Controle level;
	changeScreen(window, "images/title_screen.png");
	lives = 3;
	while (lives > 0) {
		Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/player_left_1.png");
		player.setPos({ 500.f, 500.f });

		Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
		bot1.setPos({ 400.f, 288.f });
		Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
		bot2.setPos({ 350.f, 320.f });


		// Gravity variables:
		//bool gameBegin;
		bool nextLevel = true;
		level.current_level = 0;
		coinAmount = 0;
		while (window.isOpen() && lives>0) {
			if (coinAmount == 1) {
				level.current_level++;
				nextLevel = true;
				coinAmount = 0;
			}
			if (level.current_level == 3) {
				changeScreen(window, "images/ending_screen.png");
			}

			cout << "_______New Lap________" << endl;
			cout << "_____________LIVES_______" << lives << endl;
			if (nextLevel) {
				cout << "NEXT LEVEL" << endl;
				switch (level.current_level) {
				case 0: {
					level.setMapPart(1);
					level.openMap(map, "levels/level_1_blocks.txt");
					player.respawn();
					break;
				}
				case 1: {
					level.setMapPart(1);
					level.openMap(map, "levels/level_2_blocks.txt");
					player.respawn();
					break;
				}
				case 2: {
					level.setMapPart(1);
					level.openMap(map, "levels/level_3_blocks.txt");
					player.respawn();
					break;
				}
				}
				cout << "Change of the level" << endl;
				nextLevel = false;

				//Sleep(2000);
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
				player.checkCollision(map[xMap + 1][yMap + 1]);// r b 
				player.checkCollision(map[xMap - 1][yMap + 1]); // b l
			}

			if (player.checkCollision(bot1) == 2) {
				player.respawn();
				lives--;
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
			x_move_speed = X_MOVE_SPEED_CONST1;
			jump_change_step = JUMP_CHANGE_STEP_CONST;

			window.display();
		}
	}

	/*
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
	delete map[i];
	}
	delete map;*/
	
	changeScreen(window, "images/game_over.png");
	return level.current_level;
}







int main() {
		sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
		window.setFramerateLimit(100);
		while (true) {
			gamePlay(window);
			Sleep(100);
		}
		return 0;
	}