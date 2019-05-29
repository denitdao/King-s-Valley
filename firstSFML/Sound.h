#pragma once
#include "pch.h"

class GameMusic {
	sf::SoundBuffer buffer; // pointer to the sound file
	sf::Sound sound;
public:
	// initialize buffer and sound
	GameMusic(string path, bool bloop) {
		if (!buffer.loadFromFile(path))
			myLog(Logger::ERR) << "Failed to load sound" << endl;
		sound.setBuffer(buffer);
		sound.setLoop(bloop);
	}
	// start playing sound 
	void playSound() {
		sound.play();
	}
	// stop playing sound
	void stopSound() {
		sound.stop();
	}
};