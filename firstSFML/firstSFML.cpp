#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;

int main() {
	sf::Clock clock;
	float elapsed;

	Block controller;
	Block map[MAP_SIZE_X][MAP_SIZE_Y];
	controller.openMap(map, "level_1_blocks.txt");
	//Sleep(5000);

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
	window.setFramerateLimit(200);

	Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	player.setPos({ 200.f, 200.f });

	Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	bot1.setPos({ 200.f, 300.f });
	Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y });
	bot2.setPos({ 550.f, 200.f });

	// Gravity variables:
	const int groundHeight = 600;

	Block ground({ WINDOW_SIZE_X , WINDOW_SIZE_Y - groundHeight });
	ground.setPos({ 0, (float)groundHeight });

	float i = 0;
	while (window.isOpen())	{
		cout << "_______New Lap________" << endl;
		sf::Event _event;
		// keypress detection

		// parameters
		while (window.pollEvent(_event)) {
			switch (_event.type) {
				case sf::Event::Closed:
					window.close();
			}
		}
		
		player.controle();

		player.annulateCollision(); // if won't be any collisions, value won't change fron 'no'

		player.checkCollision(ground);
		player.checkCollision(bot1);

		window.clear();

		bot1.drawTo(window);
		//bot2.drawTo(window);
		//controller.drawTo(window, map);
		player.drawTo(window);
		//ground.drawTo(window);
		
		/*
		elapsed = clock.restart().asMilliseconds();
		gravity_speed = GRAVITY_SPEED_CONST * elapsed;
		x_move_speed = X_MOVE_SPEED_CONST * elapsed;
		jump_change_step = JUMP_CHANGE_STEP_CONST * elapsed;
		cout << elapsed << endl;
		*/
		gravity_speed = GRAVITY_SPEED_CONST;
		x_move_speed = X_MOVE_SPEED_CONST;
		jump_change_step = JUMP_CHANGE_STEP_CONST;

		window.display();
		
	}
	return 0;
}