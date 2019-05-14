#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;

int main() {
	sf::Clock clock;
	float elapsed = 0, avg = 0;
	Block controller;
	Block map[MAP_SIZE_X][MAP_SIZE_Y];
	controller.openMap(map, "level_1_blocks.txt");
	//Sleep(5000);

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
	window.setFramerateLimit(100);

	Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	player.setPos({ 200.f, 200.f });

	Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	bot1.setPos({ 200.f,500.f });
	Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	bot2.setPos({ 350.f, 320.f });

	// Gravity variables:

	int i = 10;
	while (window.isOpen()) {
		cout << "_______New Lap________" << endl;
		
		player.controle(window);

		player.annulateCollision(); // if won't be any collisions, value won't change fron 'no'
		bot1.annulateCollision();
		bot2.annulateCollision();

		int xMap = player.senterGet().x / BLOCK_SIZE_X;
		int yMap = player.senterGet().y / BLOCK_SIZE_X;

		cout << "xMap = " << xMap << " yMap = " << yMap << endl;

		// checking collision of player
		//player.checkCollision(map[xMap][yMap]); //pos of the player
		player.checkCollision(map[xMap][yMap + 1]); // bottom
		if (!player.onLeftStair && !player.onRightStair) {
			if (player.inJump == false) {
				player.checkCollision(map[xMap - 1][yMap - 1]); // left top
				player.checkCollision(map[xMap + 1][yMap - 1]); // right top
				player.checkCollision(map[xMap][yMap - 1]); // top
				player.checkCollision(map[xMap + 1][yMap]); // rigth
				player.checkCollision(map[xMap - 1][yMap]); // left
			}
			player.checkCollision(map[xMap + 1][yMap + 1]);// r b 
			player.checkCollision(map[xMap - 1][yMap + 1]); // b l
		}
		
		//player.checkCollision(bot1);
		//player.checkCollision(bot2);

		window.clear();

		controller.drawTo(window, map);
		//bot1.drawTo(window);
		//bot2.drawTo(window);
		player.drawTo(window);

		/*
		elapsed = clock.restart().asMilliseconds();
		gravity_speed = GRAVITY_SPEED_CONST * elapsed;
		x_move_speed = X_MOVE_SPEED_CONST * elapsed;
		jump_change_step = JUMP_CHANGE_STEP_CONST * elapsed;
		cout << elapsed << endl;
		*/

		/**/
		//Denys
		gravity_speed = GRAVITY_SPEED_CONST;
		x_move_speed = X_MOVE_SPEED_CONST;
		jump_change_step = JUMP_CHANGE_STEP_CONST;
		stair_move_speed = ((int)x_move_speed / 2 * 2 > 0) ? (int)x_move_speed / 2 * 2 : 1 ;
		//Alex
		//gravity_speed = GRAVITY_SPEED_CONST1;
		//x_move_speed = X_MOVE_SPEED_CONST1;
		//jump_change_step = JUMP_CHANGE_STEP_CONST1;
		window.display();
		i++;
	}
	return 0;
}