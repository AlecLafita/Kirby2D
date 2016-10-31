#include "MainMenu.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Defines.h"

#include <GL/glut.h>
#include "Game.h"

#include <iostream>

using namespace std;

MainMenu::MainMenu()
{
}

void MainMenu::init() {
	index = 0; //Option by default
	numOptions = 3; 
	bUpPressed = false;
	bDownPressed = false;
	bEnterPressed = false;

	bCredits = false;
	bInstructions = false;
	bGameOver = false;
    bNewRecord = false;

	//Shader
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Texture quads
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glm::vec2 geomGUI[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };

	float posX = float(SCREEN_WIDTH - 200.f);
	float posY = 20.f;
	glm::vec2 geomLogo[2] = { glm::vec2(posX, posY), glm::vec2(posX + 120, posY + 73.2) };

	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	mainTexture.loadFromFile("images/mainMenu_hard.png", TEXTURE_PIXEL_FORMAT_RGB);

	instructionsQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	instruccionsTex.loadFromFile("images/instructions_bg_w_text.png", TEXTURE_PIXEL_FORMAT_RGBA);

    creditsQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	creditsTex.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);

    gameOverQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	gameOverTex.loadFromFile("images/game_over.png", TEXTURE_PIXEL_FORMAT_RGBA);

    winQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	winTex.loadFromFile("images/win_screen.png", TEXTURE_PIXEL_FORMAT_RGBA);


	//text 
	if (!playText.init("fonts/VCR_OSD_MONO.ttf"))
		cout << "Could not load font!!!" << endl;

    if (!scoreText.init("fonts/VCR_OSD_MONO.ttf"))
		cout << "Could not load font!!!" << endl;

	if (!instructionsText.init("fonts/VCR_OSD_MONO.ttf"))
		cout << "Could not load font!!!" << endl;

	if (!recordsText.init("fonts/VCR_OSD_MONO.ttf"))
		cout << "Could not load font!!!" << endl;
}


void MainMenu::update(int deltaTime) {
	//Change option
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !bUpPressed && !bInstructions && !bCredits) {
		--index;
		bUpPressed = true;
		Game::instance().playSound(MENU_SELECTION);
	}
	else if (!Game::instance().getSpecialKey(GLUT_KEY_UP)) bUpPressed = false;

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !bDownPressed && !bInstructions && !bCredits) {
		++index;
		bDownPressed = true;
        Game::instance().playSound(MENU_SELECTION);

	}
	else if(!Game::instance().getSpecialKey(GLUT_KEY_DOWN)) bDownPressed = false;

	if (index == -1) index = numOptions - 1;
	index = index % numOptions;


	if (Game::instance().getKey(13) && !bEnterPressed) { //enter key
		bEnterPressed = true;
		if (bInstructions) //At instructions screen
			bInstructions = false; //Exit instructions screen
		else if (bCredits) 
			bCredits = false; //May be different for records!
		else if (bGameOver)
			bGameOver = false;
		else if (bNewRecord) {
			bNewRecord = false;
		}
		else { //Main menu screen, check if options are selected
			switch (index){
			case 0: //start game
				Game::instance().nextLevel();
				break;
			case 1: //show instructions
                bInstructions = true;
                break;
			case 2: //show credits
				bCredits = true;
				break;
			}
		}
	}
	else if (!Game::instance().getKey(13))bEnterPressed = false;
}

void MainMenu::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	glm::mat4 modelview;

	//BACKGROUND
	texProgram.setUniformMatrix4f("modelview", modelview);
	mainTextureQuad->render(mainTexture);
//    logoTextureQuad->render(logoTexture);

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	int screen_height = vp[3] - vp[1];
	int screen_width = vp[2] - vp[0];
	int text_size = min(screen_height / 8,screen_width/8); //Value that makes the text to fit better on background
	int height_offset = 20;

//    scoreText.render("", glm::vec2(10, text_size), text_size, glm::vec4(1, 1, 1, 1));

	if (bInstructions) {//At instructions screen
		//Render instructions
        instructionsQuad->render(instruccionsTex);
	}
	else if (bCredits) {
		//render records
        creditsQuad->render(creditsTex);
    }
	else if (bGameOver) {
		//render game over
        gameOverQuad->render(gameOverTex);
	}
	else if (bNewRecord) {
        winQuad->render(winTex);
        scoreText.render(std::to_string(lastScore), glm::vec2(280, 260), text_size, glm::vec4(0, 0, 0, 1));
    }
	else { //Main menu screen
		switch (index)  { //This only renders the actual "selected" text with different color
		case 0:
			playText.render("*", glm::vec2(10, text_size), text_size, glm::vec4(1, 1, 1, 1));
			instructionsText.render("", glm::vec2(10, text_size + screen_height / numOptions), text_size, glm::vec4(0, 0, 0, 1));
			recordsText.render("", glm::vec2(10, text_size + 2 * screen_height / numOptions), text_size, glm::vec4(0, 0, 0, 1));
			break;
		case 1:
			playText.render("", glm::vec2(10, text_size), text_size, glm::vec4(0, 0, 0, 1));
			instructionsText.render("*", glm::vec2(10, text_size + screen_height / numOptions), text_size, glm::vec4(1, 1, 1, 1));
			recordsText.render("", glm::vec2(10, text_size + 2 * screen_height / numOptions), text_size, glm::vec4(0, 0, 0, 1));
			break;
		case 2:
			playText.render("", glm::vec2(10, text_size), text_size, glm::vec4(0, 0, 0, 1));
			instructionsText.render("", glm::vec2(10, text_size + screen_height / numOptions), text_size, glm::vec4(0, 0, 0, 1));
			recordsText.render("*", glm::vec2(10, text_size + 2 * screen_height / numOptions), text_size, glm::vec4(1, 1, 1, 1));
			break;

		}
	}
}


void MainMenu::activateGameOver() {
	bGameOver = true;
}

void MainMenu::activateNewRecord(int score) {
	bNewRecord = true;
    lastScore = score;
}


void MainMenu::initShaders(){
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
