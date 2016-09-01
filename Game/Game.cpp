#include "Game.h"


Game::Game(string title, int width, int height)
{
	cout << "Starting game: " << title.c_str() << endl;
	windowTitle = title;
	windowWidth = width;
	windowHeight = height;
	gameWindow = 0;
	glContext = 0;
	endingGame = false;
}

void Game::initGame()
{
	cout << "Game initializing..." << endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Initialisation SDL impossible: " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
	cout << "Configure openGL 3.1..." << endl;
	// Set OPENGL version, Buffer & Depth size
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	cout << "Create SDL window... (" << windowWidth << "x" << windowHeight<<")"<<endl;
	gameWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(gameWindow);

	if (gameWindow == 0)
	{
		cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}

	if (glContext == 0)
	{
		cout << SDL_GetError() << endl;
		SDL_DestroyWindow(gameWindow);
		SDL_Quit();
		return;
	}
	
	cout << "Glew init..." << endl;
	GLenum initialisationGlew(glewInit());
	if (initialisationGlew != GLEW_OK)
	{
		cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGlew) <<endl;
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(gameWindow);
		SDL_Quit();
	}
	else {
		glEnable(GL_DEPTH_TEST);
	}
}

void Game::execGame()
{
	cout << "Init projection & modelview..." << endl;
	projection = perspective(70.0, (double)windowWidth / windowHeight, 1.0, 100.0);
	modelview = mat4(1.0);

	Drawing draw("COUCOU");

	cout << "Game while starting..." << endl;

	while (!endingGame)
	{
		SDL_WaitEvent(&sdlEvent);
		if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			endingGame = true;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelview = lookAt(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		draw.afficher(modelview, projection);

		SDL_GL_SwapWindow(gameWindow);
		modelview = mat4(1.0);
	}

	exitGame();

}

void Game::exitGame()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}