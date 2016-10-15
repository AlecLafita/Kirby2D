//
// Created by quokka on 15/10/16.
//

#ifndef PROJECT_SOUNDHELPER_H
#define PROJECT_SOUNDHELPER_H

#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

class SoundHelper {

public:
    SoundHelper();
    ~SoundHelper();

    void playMusic(string pathFile);
    void stopMusic();
    void pauseMusic();

    void playSound(string pathFile); //Not implementing stop, sounds should be short.

private:

    sf::SoundBuffer soundBuffer;
    sf::Sound soundPlayer;

    sf::Music musicPlayer;
};


#endif //PROJECT_SOUNDHELPER_H
