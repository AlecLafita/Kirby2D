//
// Created by quokka on 25/10/16.
//

#ifndef KIRBY_INSTRUCTIONSSCREEN_H
#define KIRBY_INSTRUCTIONSSCREEN_H

#include "TexturedQuad.h"
#include "Text.h"
#include "ShaderProgram.h"
#include "Texture.h"


class InstructionsScreen
{
public:
    InstructionsScreen();
    ~InstructionsScreen() {}

    void init();
    void update(int deltaTime);
    void render();

private:
    void initShaders();

private:

    ShaderProgram texProgram;
    glm::mat4 projection;

    TexturedQuad* mainTextureQuad; //GUI Background
    Texture mainTexture;

    Text instructionsText;
};


#endif //KIRBY_INSTRUCTIONSSCREEN_H
