#include "Common.h"

#ifndef LTEXTURE_H
#define LTEXTURE_H

//Texture voi cac tinh nang
class LTexture
{
    public:
		LTexture();
		~LTexture();

		//tai anh cho texture
		bool loadFromFile(std::string path, SDL_Renderer* ren);
		//giai phong texture
		void free();
		//Render texture tai vi tri x, y
		void render(SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		//Get kich thuoc texture
		int getWidth();
		int getHeight();

	private:
		//texture
		SDL_Texture* mTexture;
		//kich thuoc texture
		int mWidth;
		int mHeight;
};

#endif // LTEXTURE_H
