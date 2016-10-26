#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "MainMenu.h"
#include "Scene.h"
#include "GUI.h"
#include "../helpers/SoundHelper.h"
#include "../characters/PowerType.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void resetLevel();
	void nextLevel();
    //void showInstructions();

	//add or substract score
	void addScore(int score);

	//1 life obtained!
	void winLife();

	//GUI functions
	void setPlayerEnergy(int energy);
	void setAbilityToShow(PowerType type);

	//Sound functions
	void playSound(int soundIndex);
	void stopSound(int soundIndex);
	void playMusic(string pathToFile);
	void stopMusic();

private:
	void setMenustate();
	void initSoundHelper();
	
private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	MainMenu mMainMenu;
	GUI mGUI;					
	SoundHelper *mSoundHelper;

	int playerLifes;

	int levelAct;

	int scoreAct;

	bool keys[256], specialKeys[256]; // Store key states so that 
	// we can have access at any time

};


#endif // _GAME_INCLUDE


