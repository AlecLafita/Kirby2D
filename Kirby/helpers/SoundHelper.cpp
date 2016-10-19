//
// Created by quokka on 15/10/16.
//


#include "SoundHelper.h"

using namespace std;

/**
 * Constructor.
 * @return  New SoundHelper object.
 */
SoundHelper::SoundHelper(int numOfSounds){
	soundBuffer = vector<sf::SoundBuffer>(numOfSounds);
	soundsPlayer = vector<sf::Sound>(numOfSounds);
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
    musicPlayer.setVolume(25.f);
    musicPlayer.play();
}

/**
 * Stops playing the music file.
 */
void SoundHelper::stopMusic(){

    musicPlayer.stop();
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

void SoundHelper::initSound(int soundIndex, string pathToFile) {

	if (!soundBuffer[soundIndex].loadFromFile(pathToFile)){
		cout << "could not load " << pathToFile;
	}

}
void SoundHelper::playSound(int soundIndex){
	soundsPlayer[soundIndex].setBuffer(soundBuffer[soundIndex]);
	soundsPlayer[soundIndex].play();
}

void SoundHelper::stopSound(int soundIndex){
	soundsPlayer[soundIndex].stop();
}

