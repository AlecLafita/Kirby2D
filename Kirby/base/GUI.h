#pragma once

#include "TexturedQuad.h"
#include "Text.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "../characters/PowerType.h"

class GUI
{
public:
	GUI();
	~GUI() {}

	void init();
	void render();

	void addScore(int scoreToAdd){ scoreAct += scoreToAdd; }

	void setPlayerEnergy(int energy);
	void setLifes(int lifes); //TODO: Set lifes
	void setAbility(PowerType type);


private:
	void initShaders();
private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	int mHeight;
	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	TexturedQuad* abilityTexQuad;
	Texture abilityTexture;

	TexturedQuad* lifesQuad;
	Texture lifesTexture;
	Text lifesText;
	int lifesAct;

	TexturedQuad* energyQuad;
	Texture energyTexture;

	Text energyText;
	int energyAct;

	Text scoreText;
	unsigned int scoreAct;
};

