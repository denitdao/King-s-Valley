#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;

void changeScreen(sf::RenderWindow &window, string sceneName) {
	sf::Event _event;
	sf::Texture sceneTexture;
	sf::Sprite sceneScreen;
	if (!sceneTexture.loadFromFile(sceneName)) {
		cout << "image load failed!" << endl;
	}
	sceneScreen.setTexture(sceneTexture);
	sceneScreen.setTextureRect(sf::IntRect(0, 0, sceneTexture.getSize().x, sceneTexture.getSize().y));
	sceneScreen.setScale(WINDOW_SIZE_X / sceneTexture.getSize().x, WINDOW_SIZE_Y / sceneTexture.getSize().y);
	window.clear();
	window.draw(sceneScreen);
	window.display();
	while (window.isOpen()) {
		window.pollEvent(_event);
		if (sceneName == "images/ending_screen.png") { // special behaviour on end screen
			Hero endGamePlayer({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/player_left_1.png");
			endGamePlayer.setPos({ -PLAYER_SIZE_X, WINDOW_SIZE_Y - 6.25f * BLOCK_SIZE_X });
			while (endGamePlayer.getCoord().x < WINDOW_SIZE_X - 2 * BLOCK_SIZE_X) {
				window.pollEvent(_event);
				if (_event.type == sf::Event::Closed) {
					window.close();
					exit(0);
				}
				endGamePlayer.autoMoveOn({ x_move_speed, 0 }, toright);
				window.clear();
				window.draw(sceneScreen);
				endGamePlayer.drawTo(window);
				window.display();
			}
			Sleep(200);
			cout << "Returning from the ending screen" << endl;
			return;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Sleep(200);
			return;
		}
		if (_event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
		Sleep(50);
	}
}

int gamePlay(sf::RenderWindow &window, Scoreboard &board) {
	window.clear();
	Controle level;
	Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/player_left_1.png");
	Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
	Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
	Block **map = new Block*[MAX_MAP_SIZE_X];
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		map[i] = new Block[MAP_SIZE_Y];
	}
	lives = 3;
	changeScreen(window, "images/title_screen.png");
	player.respawn();
	bot1.setPos({ 400.f, 288.f });
	bot2.setPos({ 350.f, 320.f });

	bool nextLevel = true; // load level
	level.current_level = 0; // first level
	int coinAmount = 0;
	while (window.isOpen() && lives > 0) {
		cout << "_______New Lap________" << endl;
		cout << "__________LIVES_______" << lives << endl;
		if (player.coinAmountIncrease == true) { // gor one coin - increase
			coinAmount++;
			board.addPoint(500);
			player.coinAmountIncrease = false;
		}
		if (coinAmount == 1) { // collected enough coins
			level.current_level++;
			nextLevel = true; // load level
			coinAmount = 0;
		}

		if (nextLevel) { // need to load
			cout << "NEXT LEVEL" << endl;
			switch (level.current_level) {
			case 0: { // first level
				player.respawn();
				level.setMapPart(1);
				level.openMap(map, "levels/level_1_blocks.txt");
				nextLevel = false;
				coinAmount = 0;
				break;
			}
			case 1: { // second level
				board.addPoint(2000);
				player.respawn();
				level.setMapPart(1);
				level.openMap(map, "levels/level_2_blocks.txt");
				nextLevel = false;
				coinAmount = 0;
				break;
			}
			case 2: { // third level
				board.addPoint(2000);
				player.respawn();
				level.setMapPart(1);
				level.openMap(map, "levels/level_3_blocks.txt");
				nextLevel = false;
				coinAmount = 0;
				break;
			}
			default: { // you won
				Sleep(1000);
				board.addPoint(3000);
				changeScreen(window, "images/ending_screen.png"); // you won screen
				coinAmount = 0;
				return level.current_level; // finish gameplay
			}
			}
			cout << "LOADED" << endl;
			Sleep(1000);
		}

		player.controle(window); // get user input

		player.xMap = player.getSenter().x / BLOCK_SIZE_X;
		player.yMap = player.getSenter().y / BLOCK_SIZE_X;

		if (level.getMapSizeX() > 32) { // if map consists of 2+ parts
			if (player.xMap == 31 && level.getMapPart() == 1) {
				player.setPos({ player.getSize().x, player.getCoord().y });
				player.xMap = player.getSenter().x / BLOCK_SIZE_X; // recalculate 
				level.changeMapPart();
			}
			else if (player.xMap == 0 && level.getMapPart() == 2) {
				player.setPos({ WINDOW_SIZE_X - player.getSize().x * 2.f, player.getCoord().y });
				player.xMap = player.getSenter().x / BLOCK_SIZE_X; // recalculate
				level.changeMapPart();
			}
		}
		else if (player.xMap >= 31 || player.xMap <= 0) { // if we jumped out from the one-screen map
			player.respawn();
			player.xMap = player.getSenter().x / BLOCK_SIZE_X; // recalculate
			player.yMap = player.getSenter().y / BLOCK_SIZE_X;
		}
		if (level.getMapPart() == 2) { // second half of map array
			player.xMap += 32;
		}
		cout << "xMap = " << player.xMap << " yMap = " << player.yMap << endl;
		cout << "In map part = " << level.getMapPart() << endl;

		player.annulateCollision(); // if won't be any collisions, value won't change from 'no'
		// checking collision of player
		player.checkCollision(map[player.xMap][player.yMap + 1]); // bottom
		if (!player.onLeftStair && !player.onRightStair) {
			if (player.inJump == false) {
				player.checkCollision(map[player.xMap - 1][player.yMap - 1]); // left top
				player.checkCollision(map[player.xMap + 1][player.yMap - 1]); // right top
				player.checkCollision(map[player.xMap][player.yMap - 1]); // top
				player.checkCollision(map[player.xMap + 1][player.yMap]); // right
				player.checkCollision(map[player.xMap - 1][player.yMap]); // left
			}
			player.checkCollision(map[player.xMap + 1][player.yMap + 1]);// r b 
			player.checkCollision(map[player.xMap - 1][player.yMap + 1]); // b l
		}
		if (player.checkCollision(bot1) == 2) {
			player.respawn();
			board.looseHeart();
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
		board.drawTo(window);

		/*//Alex
		gravity_speed = GRAVITY_SPEED_CONST1;
		x_move_speed = X_MOVE_SPEED_CONST1;
		jump_change_step = JUMP_CHANGE_STEP_CONST1;*/
		//Denys
		gravity_speed = GRAVITY_SPEED_CONST;
		x_move_speed = X_MOVE_SPEED_CONST; // add const 1 for alex
		jump_change_step = JUMP_CHANGE_STEP_CONST;

		window.display();
	}
	// game ended with win or lives ended
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		delete[] map[i]; // delete sub-array
	}
	delete[] map; // delete main array

	changeScreen(window, "images/game_over.png"); // play

	return level.current_level;
}

int main() {
	Scoreboard board;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
	window.setFramerateLimit(100);
	
	while (true) {
		board.annulatePoint();
		board.fillTable();
		gamePlay(window, board); // game won
	}
	return 0;
}