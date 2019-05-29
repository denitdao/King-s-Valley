#pragma once
#include "pch.h"

class Controle : public Block {
	int x_curr_map_size;
	int y_curr_map_size;
	int map_part = 1; // 1 or 2
public:
	int current_level = 1;
	int getMapSizeX() {
		return x_curr_map_size;
	}
	int getMapSizeY() {
		return y_curr_map_size;
	}
	int getMapPart() {
		return map_part;
	}
	void changeMapPart() {
		if (map_part == 1)
			map_part = 2;
		else
			map_part = 1;
	}
	void setMapPart(int i) {
		map_part = i;
	}
	//noTexture = 0, wall = 1, stairLeftUnder = 2, stairLeft = 3, stairLeftTop = 4, stairRightUnder = 5, stairRight = 6, stairRightTop = 7, hardWall = 8
	// read file and init blocks with sprites
	void openMap(Block **newMap, string level) {
		ifstream mapPtr(level);
		if (!mapPtr) {
			myLog(Logger::ERR) << "error opening file - not exists" << endl;
			exit(1);
		}
		mapPtr >> x_curr_map_size >> y_curr_map_size; // get map sizes
		myLog(Logger::INFO) << "map size is " << x_curr_map_size << " x " << y_curr_map_size << endl;
		char ch;
		for (int j = 0; j < y_curr_map_size; j++) {
			for (int i = 0; i < x_curr_map_size; i++) {
				mapPtr.get(ch);
				if(ch == '\n')
					mapPtr.get(ch);
				switch (ch) {
				case '0': {
					newMap[i][j].create(noTexture, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				case '1': {
					newMap[i][j].create(wall, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				case '2': {
					newMap[i][j].create(stairLeftUnder, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				case '3': {
					newMap[i][j].create(stairLeft, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ ((i - MAP_SIZE_X) * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					break;
				}
				case '4': {
					newMap[i][j].create(stairLeftTop, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ ((i - MAP_SIZE_X) * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					break;
				}
				case '5': {
					newMap[i][j].create(stairRightUnder, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				case '6': {
					newMap[i][j].create(stairRight, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ ((i - MAP_SIZE_X) * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					break;
				}
				case '7': {
					newMap[i][j].create(stairRightTop, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ (i * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ ((i - MAP_SIZE_X) * BLOCK_SIZE_X) - (BLOCK_SIZE_X / 2), j * BLOCK_SIZE_Y });
					break;
				}
				case '8': {
					newMap[i][j].create(hardWall, current_level);
					if (i < MAP_SIZE_X)
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				case '*': {
					newMap[i][j].create(coin, current_level);
					if (i < MAP_SIZE_X) // first map part
						newMap[i][j].setPos({ i * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					else  // second map part
						newMap[i][j].setPos({ (i - MAP_SIZE_X) * BLOCK_SIZE_X, j * BLOCK_SIZE_Y });
					break;
				}
				}
				myLog(Logger::INFO) << ch;
			}
			mapPtr.get(ch); // to read \n symbol
			myLog(Logger::INFO) << endl;
		}
		mapPtr.close();
	}
	// draw all map to the screen
	void drawTo(sf::RenderWindow &window, Block **newMap) {
		int iLimit = (map_part == 1) ? MAP_SIZE_X : x_curr_map_size; // set limitation depending on map part
		int iBegin = (map_part == 1) ? 0 : MAP_SIZE_X - 1; // set limitation depending on map part
		
		for (int j = 0; j < y_curr_map_size; j++) { // all except stair parts
			for (int i = iBegin; i < iLimit; i++) {
				if (newMap[i][j].getTexture() != stairLeftTop
					&& newMap[i][j].getTexture() != stairRightTop)
					newMap[i][j].drawTo(window);
			}
		}
		for (int j = 0; j < y_curr_map_size; j++) {
			for (int i = iBegin; i < iLimit; i++) { // only stair parts
				if (newMap[i][j].getTexture() == stairLeftTop
					|| newMap[i][j].getTexture() == stairRightTop)
					newMap[i][j].drawTo(window);
			}
		}
	}

};