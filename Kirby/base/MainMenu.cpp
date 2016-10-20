#include "MainMenu.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Defines.h"
#include <iostream>

using namespace std;

MainMenu::MainMenu()
{
}

void MainMenu::init() {
	index = 0; //Option by default
	numOptions = 3; 

	//Shader
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Texture quads
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glm::vec2 geomGUI[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };

	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);

	mainTexture.loadFromFile("images/mainMenu.png", TEXTURE_PIXEL_FORMAT_RGB);


	//text 
	//if (!habilityText.init("fonts/OpenSans-Regular.ttf"))
	if (!playText.init("fonts/OpenSans-Bold.ttf"))
		//if(!habilityText.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	//if (!scoreText.init("fonts/OpenSans-Regular.ttf"))
	if (!instructionsText.init("fonts/OpenSans-Bold.ttf"))
		//if(!scoreText.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	//if (!energyText.init("fonts/OpenSans-Regular.ttf"))
	if (!recordsText.init("fonts/OpenSans-Bold.ttf"))
		//if(!energyText.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
	//energyAct = MAX_ENERGY;
}

void MainMenu::update(int deltaTime) {
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



	playText.getProgram().setUniformMatrix4f("projection", projection);
	playText.getProgram().setUniformMatrix4f("modelview", modelview);

	/*if (index % numOptions == 0) {

	}
	else if (index %numOptions == 1) {

	}
	else if (index %numOptions == 2) {

	}*/
	playText.render("Play", glm::vec2(0, SCREEN_HEIGHT - GUI_HEIGHT / 2 + HABILITY_SIZE / 2), HABILITY_SIZE, glm::vec4(0, 0, 0, 1));
	instructionsText.render("Instructions", glm::vec2(2 * SCREEN_WIDTH / 3, SCREEN_HEIGHT - GUI_HEIGHT / 2 + HABILITY_SIZE / 2), HABILITY_SIZE, glm::vec4(0, 0, 0, 1));
	recordsText.render("Records", glm::vec2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - GUI_HEIGHT / 2 + HABILITY_SIZE / 2), HABILITY_SIZE, glm::vec4(0, 0, 0, 1));



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
