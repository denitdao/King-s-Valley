#include "pch.h"
#include <fstream>
#include <iostream>
#include "windows.h"

using namespace std;

void botCheckCollision(Actor &bot, Block **map, int mapPart) {
	bot.xMap = bot.getSenter().x / BLOCK_SIZE_X;
	bot.yMap = bot.getSenter().y / BLOCK_SIZE_X;
	if (mapPart == 2)
		bot.xMap += 32;
	if (bot.checkCollision(map[bot.xMap + 1][bot.yMap + 1]) == 4) // r b 
		bot.setDir(toleft);
	if(bot.checkCollision(map[bot.xMap - 1][bot.yMap + 1]) == 4) // b l
		bot.setDir(toright);
	if(bot.checkCollision(map[bot.xMap + 1][bot.yMap]) == 1) // right
		bot.setDir(toleft);
	if(bot.checkCollision(map[bot.xMap - 1][bot.yMap]) == 1) // left
		bot.setDir(toright);
	if (bot.xMap >= 61)
		bot.setDir(toleft);
	if (bot.xMap <= 1)
		bot.setDir(toright);
	bot.annulateCollision();
}

void changeScreen(sf::RenderWindow &window, string sceneName) {
	sf::Event _event;
	sf::Texture sceneTexture;
	sf::Sprite sceneScreen;
	if (!sceneTexture.loadFromFile(sceneName)) {
		myLog(Logger::ERR) << "image load failed!" << endl;
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
			myLog(Logger::INFO) << "Returning from the ending screen" << endl;
			GameMusic soundOneUp("sounds/OneUp.wav", false);
			soundOneUp.playSound();
			Sleep(1000);
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
	GameMusic soundStartGame("sounds/StartGame.wav", false);
	soundStartGame.playSound();
	GameMusic soundPlaying("sounds/Playing.wav", true);
	GameMusic soundTreasure("sounds/Treasure.wav", false);
	GameMusic soundNextMap("sounds/NextMap.wav", false);
	GameMusic soundCaught("sounds/Caught.wav", false);
	GameMusic soundCollectedAll("sounds/CollectedAll.wav", false);

	Hero player({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/player_left_1.png");
	Mummy bot1({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
	Mummy bot2({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
	Mummy bot3({ PLAYER_SIZE_X, PLAYER_SIZE_Y }, "images/mummy_left_1.png");
	Block **map = new Block*[MAX_MAP_SIZE_X];
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		map[i] = new Block[MAP_SIZE_Y];
	}
	lives = LIVES_CONST;
	player.respawn();
	changeScreen(window, "images/title_screen.png");
	soundStartGame.stopSound();
	soundPlaying.playSound();
	bool nextLevel = true; // load level
	bool loadedNextLevel = false;
	level.current_level = 0; // first level - 0
	int coinAmount = 0;
	while (window.isOpen() && lives > 0) {
		myLog(Logger::DEBUG) << "_______New Lap________" << endl;
		if (player.coinAmountIncrease == true) { // got one coin - increase
			soundTreasure.playSound();
			coinAmount++;
			board.addPoint(500);
			player.coinAmountIncrease = false;
		}
		if (coinAmount == 4) { // collected enough coins
			soundPlaying.stopSound();
			soundCollectedAll.playSound();
			level.current_level++;
			nextLevel = true; // load level
			coinAmount = 0;
			Sleep(3000);
		}
		if (loadedNextLevel) {
			loadedNextLevel = false;
			Sleep(3000);
			soundPlaying.playSound();
		}
		if (nextLevel) { // need to load
			myLog(Logger::INFO) << "NEXT LEVEL" << endl;
			switch (level.current_level) {
			case 0: { // first level
				player.setRespawn({ 16, 10 });
				player.respawn();
				bot1.setRespawn({ 7, 2 });
				bot1.respawn();
				bot2.setRespawn({ 7, 12 });
				bot2.respawn();
				bot3.setRespawn({ 7, 21 });
				bot3.respawn();
				level.setMapPart(1);
				level.openMap(map, "levels/level_1_blocks.txt");
				nextLevel = false;
				coinAmount = 0;
				break;
			}
			case 1: { // second level
				soundNextMap.playSound();
				loadedNextLevel = true;
				board.addPoint(2000);
				player.setRespawn({ 16, 9 });
				player.respawn();
				bot1.setRespawn({ 7, 2 });
				bot1.respawn();
				bot2.setRespawn({ 10, 10 });
				bot2.respawn();
				bot3.setRespawn({ 27, 20 });
				bot3.respawn();
				level.setMapPart(1);
				level.openMap(map, "levels/level_2_blocks.txt");
				nextLevel = false;
				coinAmount = 0;
				break;
			}
			case 2: { // third level
				soundNextMap.playSound();
				loadedNextLevel = true;
				board.addPoint(2000);
				player.setRespawn({ 16, 11 });
				player.respawn();
				bot1.setRespawn({ 7, 2 });
				bot1.respawn();
				bot2.setRespawn({ 28, 11 });
				bot2.respawn();
				bot3.setRespawn({ 27, 20 });
				bot3.respawn();
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
			myLog(Logger::DEBUG) << "LOADED" << endl;
		}

		player.controle(window); // get user input
		bot1.autoMoveOn({ x_move_speed, 0 });
		bot2.autoMoveOn({ x_move_speed, 0 });
		bot3.autoMoveOn({ x_move_speed, 0 });
		botCheckCollision(bot1, map, level.getMapPart());
		botCheckCollision(bot2, map, level.getMapPart());
		botCheckCollision(bot3, map, level.getMapPart());

		player.xMap = player.getSenter().x / BLOCK_SIZE_X;
		player.yMap = player.getSenter().y / BLOCK_SIZE_X;

		if (level.getMapSizeX() > 32) { // if map consists of 2+ parts
			if (player.xMap == 31 && level.getMapPart() == 1) { // to second part
				player.setPos({ player.getSize().x, player.getCoord().y });
				player.xMap = player.getSenter().x / BLOCK_SIZE_X; // recalculate 
				if (level.current_level == 1) {
					player.setRespawn({ 13, 13 });
					bot1.setRespawn({ 16, 8 });
					bot1.respawn();
					bot2.setRespawn({ 27, 16 });
					bot2.respawn();
					bot3.setRespawn({ 17, 20 });
					bot3.respawn();
				}
				level.changeMapPart();
			}
			else if (player.xMap == 0 && level.getMapPart() == 2) { // to first part
				player.setPos({ WINDOW_SIZE_X - player.getSize().x * 2.f, player.getCoord().y });
				player.xMap = player.getSenter().x / BLOCK_SIZE_X; // recalculate
				if (level.current_level == 1) {
					player.setRespawn({ 16, 11 });
					bot1.setRespawn({ 7, 2 });
					bot1.respawn();
					bot2.setRespawn({ 10, 10 });
					bot2.respawn();
					bot3.setRespawn({ 27, 20 });
					bot3.respawn();
				}
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
		//clog << "xMap = " << player.xMap << " yMap = " << player.yMap << endl;
		myLog(Logger::INFO) << "xMap = " << player.xMap << " yMap = " << player.yMap << endl;

		player.annulateCollision(); // if won't be any collisions, value won't change from 'no'
		// checking collision of player
		player.checkCollision(map[player.xMap][player.yMap + 1]); // bottom
		if (!player.onLeftStair && !player.onRightStair) {
			if (player.inJump == false) {
				player.checkCollision(map[player.xMap - 1][player.yMap - 1]); // left top
				player.checkCollision(map[player.xMap + 1][player.yMap - 1]); // right top
				player.checkCollision(map[player.xMap + 1][player.yMap]); // right
				player.checkCollision(map[player.xMap - 1][player.yMap]); // left
			}
			player.checkCollision(map[player.xMap + 1][player.yMap + 1]);// r b 
			player.checkCollision(map[player.xMap - 1][player.yMap + 1]); // b l
		}
		if (player.checkCollision(bot1) == 2 || player.checkCollision(bot2) == 2 || player.checkCollision(bot3) == 2) {
			soundPlaying.stopSound();
			soundCaught.playSound();
			Sleep(1000);
			player.respawn();
			bot1.respawn();
			bot2.respawn();
			bot3.respawn();
			board.looseHeart();
			soundPlaying.playSound();
		}

		window.clear();

		level.drawTo(window, map);
		bot1.drawTo(window);
		bot2.drawTo(window);
		bot3.drawTo(window);
		player.drawTo(window);
		board.drawTo(window);

		//Denys
		gravity_speed = GRAVITY_SPEED_CONST;
		x_move_speed = X_MOVE_SPEED_CONST; // add const 1 for alex
		jump_change_step = JUMP_CHANGE_STEP_CONST;

		window.display();
	}
	// game ended with win or lives ended
	soundPlaying.stopSound();
	for (int i = 0; i < MAX_MAP_SIZE_X; i++) {
		delete[] map[i]; // delete sub-array
	}
	delete[] map; // delete main array
	
	GameMusic soundGameOver("sounds/GameOver.wav", false);
	soundGameOver.playSound();
	changeScreen(window, "images/game_over.png"); // play
	soundGameOver.stopSound();
	
	return level.current_level;
}

int main() {
	Scoreboard board;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "King's Valley", sf::Style::Default);
	//window.setFramerateLimit(100);
	window.setFramerateLimit(60);

	while (true) {
		board.annulatePoint();
		board.fillTable();
		gamePlay(window, board); // game won
	}
	return 0;
}