//
// Created by quokka on 25/10/16.
//

#include "InstructionsScreen.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Defines.h"

#include <GL/glut.h>
#include "Game.h"

#include <iostream>

using namespace std;

InstructionsScreen::InstructionsScreen()
{
}


void InstructionsScreen::init() {

    //Shader
    initShaders();
    projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

    //Texture quads
    glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
    glm::vec2 geomGUI[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };

    mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
    mainTexture.loadFromFile("images/instructions_bg.png", TEXTURE_PIXEL_FORMAT_RGB);


    //if (!scoreText.init("fonts/OpenSans-Regular.ttf"))
    if (!instructionsText.init("fonts/OpenSans-Bold.ttf"))
        //if(!scoreText.init("fonts/DroidSerif.ttf"))
        cout << "Could not load font!!!" << endl;
}

void InstructionsScreen::update(int deltaTime) {
    //Change option
    if (Game::instance().getSpecialKey(27)) { //EScape

        cout << "Escape" << endl;
    }
}

void InstructionsScreen::render() {
    texProgram.use();
    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
    texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
    glm::mat4 modelview;

    //BACKGROUND
    texProgram.setUniformMatrix4f("modelview", modelview);
    mainTextureQuad->render(mainTexture);

    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int screen_height = vp[3] - vp[1];
    int screen_width = vp[2] - vp[0];
    int text_size = min(screen_height / 8,screen_width/8); //Value that makes the text to fit better on background
    int height_offset = 20;
    instructionsText.render("Instructions", glm::vec2(10, text_size), text_size, glm::vec4(1, 1, 1, 1));
}



void InstructionsScreen::initShaders(){
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