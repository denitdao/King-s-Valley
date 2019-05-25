#pragma once
#include "pch.h"

class GameMusic {
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	GameMusic(string path, bool bloop) {
		if (!buffer.loadFromFile(path))
			myLog(Logger::ERR) << "Failed to load sound" << endl;
		sound.setBuffer(buffer);
		sound.setLoop(bloop);
	}
	void playSound() {
		sound.play();
	}
	void stopSound() {
		sound.stop();
	}
};