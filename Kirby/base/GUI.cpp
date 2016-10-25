#include "GUI.h"
#include "Defines.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
using namespace std;

GUI::GUI()
{
}


void GUI::init() {
	//Shader
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Texture quads
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glm::vec2 geomGUI[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH), 0.f),
			glm::vec2(float(SCREEN_WIDTH), GUI_HEIGHT)
	};
    glm::vec2 geomAbility[2] = {
			glm::vec2(float(0.f), 0.f),
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH), GUI_HEIGHT)
	};

	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	mainTexture.loadFromFile("images/menu_gui.png", TEXTURE_PIXEL_FORMAT_RGB);

    abilityTexQuad = TexturedQuad::createTexturedQuad(geomAbility, texCoords, texProgram);
    abilityTexture.loadFromFile("images/normal_ability.png", TEXTURE_PIXEL_FORMAT_RGB);

	//text
	if(!scoreText.init("fonts/OpenSans-Bold.ttf"))
	cout << "Could not load font!!!" << endl;
	scoreAct = 0;

	if (!energyText.init("fonts/OpenSans-Bold.ttf"))
		cout << "Could not load font!!!" << endl;
	//energyAct = MAX_ENERGY;

	if (!lifesText.init("fonts/OpenSans-Bold.ttf")) 
		cout << "Could not load font!!!" << endl;

}


void GUI::render(){
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	glm::mat4 modelview;

	//BACKGROUND
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, SCREEN_HEIGHT - GUI_HEIGHT, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	mainTextureQuad->render(mainTexture);

    //Ability
    abilityTexQuad->render(abilityTexture);

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	//cout << vp[0] << " " << vp[1] << " " << vp[2] << " " << vp[3] << endl;

	int screen_height = vp[3] - vp[1];
	int screen_width = vp[2]-vp[0];
	int gui_height = screen_height/5;
	int hab_size = gui_height / 3 < screen_width / 15 ? gui_height / 3 : screen_width / 15;

	scoreText.render("Score: " + std::to_string(scoreAct), glm::vec2(screen_width / 4, screen_height - gui_height / 2 + hab_size / 2), hab_size, glm::vec4(0, 0, 0, 1));

	energyText.render("Energy: " + std::to_string(energyAct), glm::vec2(2 * screen_width / 4, screen_height - gui_height / 2 + hab_size / 2), hab_size, glm::vec4(0, 0, 0, 1));

	lifesText.render("Lifes: " + std::to_string(lifesAct), glm::vec2(3 * screen_width / 4, screen_height - gui_height / 2 + hab_size / 2), hab_size, glm::vec4(0, 0, 0, 1));
}

void GUI::setPlayerEnergy(int energy) {
		energyAct = energy;
}

void GUI::setLifes(int lifes) {
	lifesAct = lifes;
}

void GUI::setAbility(PowerType type) {

	switch (type){

		case PowerType::Fire:
			cout << "Fire type" << endl;
			abilityTexture.loadFromFile("images/fire_ability.png", TEXTURE_PIXEL_FORMAT_RGB);
			break;

		case PowerType::Steam:
			abilityTexture.loadFromFile("images/normal_ability.png", TEXTURE_PIXEL_FORMAT_RGB);

			break;

		case PowerType::Electric:
			cout << "Electric type" << endl;
			abilityTexture.loadFromFile("images/electric_ability.png", TEXTURE_PIXEL_FORMAT_RGB);

			break;

        case PowerType ::Black:
            abilityTexture.loadFromFile("images/black_ability.png", TEXTURE_PIXEL_FORMAT_RGB);
            break;
		default:
		case PowerType::Normal:
			//Do nothing
			abilityTexture.loadFromFile("images/normal_ability.png", TEXTURE_PIXEL_FORMAT_RGB);
			break;
	}
}


void GUI::initShaders(){
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

