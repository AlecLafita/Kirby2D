#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	mMainMenu.init();
	mGUI.init();
	initSoundHelper();
	setMenustate();
}

void Game::setMenustate() {
	levelAct = 0;
	scoreAct = 0;
	playerLifes = 3; //Init number of lifes
	mSoundHelper->playMusic("sounds/menu.wav");
}

/*void Game::showInstructions() {
	cout << "level 1" << endl;
	scene.init("levels/Cloudy_lvl.txt", "images/peppermint_palace.png","levels/level01_enemies.txt","levels/level01_objects.txt");
	mSoundHelper->playMusic("sounds/song_green_greens.wav");
}*/

void Game::resetLevel() {
	playerLifes--;
	mGUI.setLifes(playerLifes);

	if (playerLifes == 0) {//Return to main menu
		setMenustate();
		mMainMenu.activateGameOver();
	}
	else {
		switch (levelAct) {
		case 1:
			cout << "level 1" << endl;
			scene.init("levels/Cloudy_lvl.txt", "images/peppermint_palace.png","levels/level01_enemies.txt","levels/level01_objects.txt");
			mSoundHelper->playMusic("sounds/song_green_greens.wav");
			break;
		case 2:
			cout << "level2" << endl;
			scene.init("levels/kawaii.txt", "images/forest_bg.png", "levels/level01_enemies.txt","levels/level01_objects.txt");
			mSoundHelper->playMusic("sounds/song_gourmet_race.wav");
			break;
		default:
			cout << "WIN!" << endl;
			break;
		}
		mGUI.setPlayerEnergy(MAX_ENERGY); //Start a new level with full energy
	}

}

void Game::setAbilityToShow(PowerType type){

	mGUI.setAbility(type);
}

void Game::addScore(int score) {
	scoreAct += score;
	mGUI.setScore(scoreAct);
}

void Game::nextLevel() {
	++levelAct; //Go to next level
	++playerLifes; //Per no perdre la vida de reset level (molt cutre,si xd)
	if (levelAct == 3) {//Num of total levels+1
		setMenustate();
		mMainMenu.activateNewRecord();
	}
	else resetLevel();
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

//Keyboard and mouse functions
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


void Game::winLife() {
	playerLifes++;
	mGUI.setLifes(playerLifes);
	playSound(SOUND_GET_LIFE);
}


//GUI functions
void Game::setPlayerEnergy(int energy) {
	mGUI.setPlayerEnergy(energy);
}

//Sound functions
void Game::initSoundHelper() {
	mSoundHelper = new SoundHelper(NUM_OF_SOUNDS);
	//Initialize here all the sound
	mSoundHelper->initSound(SOUND_JUMPING, "sounds/jumping.wav");
	mSoundHelper->initSound(SOUND_VACUUMING, "sounds/vacuuming.wav");
	mSoundHelper->initSound(SOUND_DEATH, "sounds/death.wav");
	mSoundHelper->initSound(SOUND_FIRE, "sounds/fire.wav");
	mSoundHelper->initSound(SOUND_GET_ENERGY, "sounds/energy_acquired.wav");
	mSoundHelper->initSound(SOUND_GET_LIFE, "sounds/new_life.wav");
}

void Game::playSound(int soundIndex) {
	mSoundHelper->playSound(soundIndex);
}
void Game::stopSound(int soundIndex) {
	mSoundHelper->stopSound(soundIndex);
}
void Game::playMusic(string pathToFile){
	mSoundHelper->playMusic(pathToFile);
}
void Game::stopMusic(){
	mSoundHelper->stopMusic();
}


