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
	void render();

	void addScore(int scoreToAdd){ scoreAct += scoreToAdd; }
	void changeHability(std::string hab) { habilityAct = hab; }

	void addEnergy() {}
	void substractEnergy();
	void addLife() {}
	void substractLife() {}

private:
	void initShaders();
private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	int mHeight;
	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	TexturedQuad* lifesQuad;
	Texture lifesTexture;

	TexturedQuad* energyQuad;
	Texture energyTexture;
	Text energyText;
	int energyAct;

	Text habilityText;
	std::string habilityAct;

	Text scoreText;
	unsigned int scoreAct;
};

