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
    SoundHelper(int numOfSounds);//The parameter indicates how many sounds to load
    ~SoundHelper();

    void playMusic(string pathFile);
    void stopMusic();
    void pauseMusic();

	void initSound(int soundIndex, string pathToFile);//consistency between vector position and path file
    void playSound(int soundIndex); //Not implementing stop, sounds should be short.
	void stopSound(int soundIndex);

private:

    vector<sf::SoundBuffer> soundBuffer;
	vector<sf::Sound> soundsPlayer;


	//std::map<string, int> soundNamePosition;


    sf::Music musicPlayer;
};


#endif //PROJECT_SOUNDHELPER_H
