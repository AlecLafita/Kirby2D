#pragma once

#include "TexturedQuad.h"
#include "Text.h"
#include "ShaderProgram.h"
#include "Texture.h"


class MainMenu
{
public:
	MainMenu();
	~MainMenu() {}

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
	
	int index;
	int numOptions;

	Text playText;
	Text instructionsText;
	Text recordsText;
};

