//
// Created by quokka on 15/10/16.
//

#ifndef PROJECT_SOUNDHELPER_H
#define PROJECT_SOUNDHELPER_H 

#include<SFML/Audio.hpp>
#include <iostream>

#include <map>

using namespace std;

class SoundHelper {

public:
    SoundHelper();
    ~SoundHelper();

    void playMusic(string pathFile);
    void stopMusic();
    void pauseMusic();

	void initSound(string pathToFile);//initilize an array of sound
    void playSound(string pathFile); //Not implementing stop, sounds should be short.
    void stopSound();

private:

    vector<sf::SoundBuffer> soundBuffer;
	std::map<string, int> soundNamePosition;

    sf::Sound soundPlayer;

    sf::Music musicPlayer;
};


#endif //PROJECT_SOUNDHELPER_H
