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

	void activateGameOver();
	void activateNewRecord();

	void setInstructions(bool value){ bInstructions = value; }


private:
	void initShaders();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	int index;
	int numOptions;
	bool bUpPressed, bDownPressed, bEnterPressed;

	Text playText;
	Text instructionsText;
	Text recordsText;

    TexturedQuad* instructionsQuad; //Instructions Background
    Texture instruccionsTex;

    TexturedQuad* creditsQuad; //Credits Background
    Texture creditsTex;

    TexturedQuad* gameOverQuad; //Game over Background
    Texture gameOverTex;

	bool bCredits; //Go to credits screen
	bool bInstructions; //Go to instructions scree
	bool bGameOver; //Go to game over screen
	bool bNewRecord; //go to record screen with possibility with adding new record
};

