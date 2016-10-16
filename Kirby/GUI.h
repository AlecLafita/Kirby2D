#pragma once

#include "TexturedQuad.h"
#include "Text.h"
#include "ShaderProgram.h"
#include "Texture.h"

class GUI
{
public:
	GUI();
	~GUI() {}

	void init();
	void update();
	void render();

private:
	void initShaders();
private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	int mHeight;
	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	TexturedQuad* lifesQuad;
	Texture lifes;

	TexturedQuad* energyQuad;
	Texture energy;

	Text habilityText;
	std::string habilityAct;

	Text scoreText;
};

