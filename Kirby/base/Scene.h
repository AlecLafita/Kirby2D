#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "../helpers/SoundHelper.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "../characters/Player.h"
#include "../characters/BlackKirby.h"
#include "../characters/FireKirby.h"
#include "../characters/Kirby.h"
#include "../characters/PinxoEnemy.h"
#include "../objects/ProjectileObject.h"
#include "../helpers/ColisionHelper.h"
#include "Defines.h"
#include "GUI.h"

#include <set>

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(std::string levelPathFile, std::string backgroundPathFile);//, std::string enemiesLocationPathFile, std::string itemsLocationPathFile
	
	void setGUI(GUI* gameGUI){ mGUI = gameGUI; }
	void setSoundHelper(SoundHelper* gameSoundHelper){ 
		mSoundHelper = gameSoundHelper; 	
		mSoundHelper->playMusic("sounds/song_green_greens.wav");//Set level music as parameter!
	}

	void update(int deltaTime);
	void render();

	void resetScene();
	void setSceneToReset() { bToReset = true; };

	//Collision functions
	bool collisionMoveRight(Character* character) const;
	bool collisionMoveLeft(Character* character) const;
	bool collisionMoveDown(Character* character) const;
	bool collisionMoveUp(Character* character) const;

	bool collisionMoveRightOnlyMap(Character* character) const;
	bool collisionMoveLeftOnlyMap(Character* character) const;

	bool playerCanSwallow(BaseEnemy* enemy) ;

	int getCameraLeftPosition() const { return cameraLeftXposition; }


	//GUI functions
	void setPlayerEnergy(int energy);
	
	//Sound functions
	void playSound(int soundIndex) {
		mSoundHelper->playSound(soundIndex);
	}
	void stopSound(int soundIndex) {
		mSoundHelper->stopSound(soundIndex);
	}
	void playMusic(string pathToFile){
		mSoundHelper->playMusic(pathToFile);
    }
	void stopMusic(){
        mSoundHelper->stopMusic();
    }

private:
	void initShaders();
	void initEnemies();//std::string enemiesLocationPathFile
	void initObjects();//std::string itemsLocationPathFile

private:
	bool bToReset;
	TileMap *map;
	TileMap *embellishmentMap;
    Sprite *mBackground;
	Texture spritesheetBg;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	set<PinxoEnemy*> mPinxoEnemies;
	set<ProjectileObject*> mProjectileObjects;
	ColisionHelper* mColisionHelper;
	SoundHelper* mSoundHelper;
	GUI* mGUI;

	int cameraLeftXposition;
};


#endif // _SCENE_INCLUDE
