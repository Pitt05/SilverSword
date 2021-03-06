#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <iostream>
#include <string>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Texture
{
public:
	Texture();
	Texture(Texture const &texture);
	Texture& operator=(Texture const &texture);
	bool loadTexture();
	void setImagePath(string path);
	GLuint getTextureID();
	~Texture();
private:
	string image_path;
	GLuint textureID;
	SDL_Surface *pixelReverse(SDL_Surface *surface);
};
#endif