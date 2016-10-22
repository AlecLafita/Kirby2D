//
// Created by quokka on 12/10/16.
//

#ifndef KIRBY_CONSTANTS_H
#define KIRBY_CONSTANTS_H

//Operating system
#ifdef linux
	#define IS_UNIX 1
#else
	#define IS_UNIX 0
#endif


// Tile size
#define TILE_SIZE_X 32
#define TILE_SIZE_Y 32

//Character 
	//Energy
	#define MAX_ENERGY 5
	//Size of sprite
	#define CHARACTER_SIZE_X 32
	#define CHARACTER_SIZE_Y 32
	//Animations
	#define NUM_OF_FRAMES 8
	#define NUM_OF_FRAMES_SLOW 5
	//Movement
	#define MOVEMENT_DEFAULT 2 //How quick character moves
	//Damage
	#define DAMAGED_DISTANCE 4 //How far will character move when damaged per frame
	#define DAMAGED_TIME 15 //How many frames a character is being damaged
	#define DAMAGED_RATE 4 //Damage color to activate each (this define) frames 
	//Jump constants
	#define JUMP_ANGLE_STEP 4
	#define JUMP_HEIGHT 70
	#define FALL_STEP 4
	#define ANGLE_GROUND 180

//Kirby constants
#define INIT_PLAYER_X_TILES 2 //Initial Kirby position
#define INIT_PLAYER_Y_TILES 2
#define MAX_JUMPS 3 //How many times can Kirby jump
#define SWALLOW_DISTANCE 60 //How far can Kirby swallow
#define SWALLOW_Y_MAX_DISTANCE 20 //Max y distance that can be between Kirby and a character being swallowed
#define SWALLOW_VELOCITY_FACTOR 10 //Factor of enemies being swallowed: the smaller, the faster

//Camera size
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 300

//GUI
#define GUI_HEIGHT 60
#define HABILITY_SIZE 20
#define GUI_ABILITY_IMG_WIDTH 80 //Original is 40x32
#define GUI_ABILITY_IMG_HEIGHT 32

//OBJECTS
#define OBJECTS_SPRITESHEET_PATH "images/items.png"

//SOUND
#define NUM_OF_SOUNDS 4
enum {
	SOUND_JUMPING, SOUND_VACUUMING, SOUND_DEATH, SOUND_FIRE
};

#endif //KIRBY_CONSTANTS_H
