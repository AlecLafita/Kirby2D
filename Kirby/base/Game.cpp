#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	levelAct = 0;
	playerLives = 4;
	mMainMenu.init();
	mGUI.init();

	initSoundHelper();

	mSoundHelper->playMusic("sounds/menu.wav");

}

void Game::initSoundHelper() {
	mSoundHelper = new SoundHelper(NUM_OF_SOUNDS);
	mSoundHelper->initSound(SOUND_JUMPING, "sounds/jumping.wav");
	mSoundHelper->initSound(SOUND_VACUUMING, "sounds/vacuuming.wav");
	mSoundHelper->initSound(SOUND_DEATH, "sounds/death.wav");
}

void Game::resetLevel() {
	playerLives--;
	if (playerLives == 0) {//Return to main menu
		levelAct = 0;
		//mGUi.reset();
	}
	else {
		switch (levelAct) {
		case 1:
			cout << "level 1" << endl;
			scene.init("levels/Cloudy_lvl.txt", "images/peppermint_palace.png");
			break;
		case 2:
			cout << "level2" << endl;
			scene.init("levels/kawaii.txt", "images/peppermint_palace.png");

			break;
		default:
			cout << "WIN!" << endl;
			break;
		}
		scene.setGUI(&mGUI);
		scene.setSoundHelper(mSoundHelper);
		mGUI.setPlayerEnergy(MAX_ENERGY);
	}

}

void Game::nextLevel() {
	++levelAct;
	resetLevel();
}

bool Game::update(int deltaTime)
{
	if (levelAct == 0)  //Main menu
		mMainMenu.update(deltaTime);
	else  
		scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (levelAct == 0) { //Main menu
		mMainMenu.render();
	}
	else{
		scene.render();
		mGUI.render();
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





