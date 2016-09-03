#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Shader.h"
#include "Drawing.h"
#include "Input.h"

using namespace std;
using namespace glm;

class Game
{

public:
	Game(string windowTitle, int width, int height);
	void initGame();
	void execGame();
	void exitGame();

private:
	string windowTitle;
	int windowWidth;
	int windowHeight;
	SDL_Window *gameWindow;
	SDL_GLContext glContext;
	Input *event;
	bool endingGame;
	mat4 modelview;
	mat4 projection;
	unsigned int frameRate;
	Uint32 beginWhile = 0, endingWhile = 0, timeWhile = 0;
};

