//
// Created by quokka on 15/10/16.
//

#include <iostream>
#include "SoundHelper.h"
#include <SFML/Audio.hpp>

using namespace std;

/**
 * Constructor.
 * @return  New SoundHelper object.
 */
SoundHelper::SoundHelper(){

}

/**
 * Destructor.
 * Destroys SoundHelper instance.
 */
SoundHelper::~SoundHelper(){

    musicPlayer.stop();
}

/**
 * Plays a music file (i.e. a song)
 * @param pathFile  Path to the music file to be played.
 */
void SoundHelper::playMusic(string pathFile){
    if (!musicPlayer.openFromFile(pathFile)){
        cout << "Error while loading music file..." << endl;
        return;
    }
    musicPlayer.setLoop(true);
    musicPlayer.play();
}

/**
 * Stops playing the music file.
 */
void SoundHelper::stopMusic(){

}

/**
 * Pauses the music.
 * Useful when pausing the game (?)
 */
void SoundHelper::pauseMusic(){

}

/**
 * Plays a sound.
 * @param pathToFile  Path to the file.
 */
void SoundHelper::playSound(string pathToFile){

    if(!soundBuffer.loadFromFile(pathToFile)){
        return;
    }
    soundPlayer.setBuffer(soundBuffer);
    soundPlayer.play();
}
