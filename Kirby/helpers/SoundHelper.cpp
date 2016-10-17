//
// Created by quokka on 15/10/16.
//


#include "SoundHelper.h"

using namespace std;

/**
 * Constructor.
 * @return  New SoundHelper object.
 */
SoundHelper::SoundHelper(){
	//PROGAMERJARDCODER
	soundBuffer = vector<sf::SoundBuffer>(3);
	soundNamePosition["sounds/vacuuming.wav"] = 0;
	soundNamePosition["sounds/jumping.wav"] = 1;
	soundNamePosition["sounds/death.wav"] = 2;

	for (auto x : soundNamePosition) {
		initSound(x.first);
	}
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

void SoundHelper::initSound(string pathToFile) {
	int pos = soundNamePosition[pathToFile];

	if (!soundBuffer[pos].loadFromFile(pathToFile)){ 
		cout << "could not load " << pathToFile;
	}

}
void SoundHelper::playSound(string pathToFile){
	int pos = soundNamePosition[pathToFile];
	cout << pos << endl;
    soundPlayer.setBuffer(soundBuffer[pos]);
    soundPlayer.play();
}

void SoundHelper::stopSound(){
    soundPlayer.stop();
}

