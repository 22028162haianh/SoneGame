#include "LTexture.h"

LTexture::LTexture()
{
    //khoi tao
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* ren)
{
	//giai phong texture ton du
	free();
	//texture load vao
	SDL_Texture* newTexture = NULL;
	//load vao tam 1 surface
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if(loadedSurface == NULL)
	{
		std::cout << "Unable to load image ! SDL_image Error: " << IMG_GetError();
	}
	else
	{
		//Color key surface vua tao
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
		//tao texture
        newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if(newTexture == NULL)
		{
			std::cout << "Unable to create texture from ! SDL Error: " << SDL_GetError();
		}
		else
		{
			//set kich thuoc cho texture
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//giai phong surface da tao
		SDL_FreeSurface( loadedSurface );
	}
	//gan texture = texture da tao
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//giai phong texture
	if( mTexture != NULL )
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
//render mTexture len ren
void LTexture::render(SDL_Renderer* ren, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//vi tri o screen de render
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	//kich thuoc can render cua texture
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render texture ra ren
	SDL_RenderCopyEx(ren, mTexture, clip, &renderQuad, angle, center, flip);
}
int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LTexture::~LTexture()
{
    //Deallocate
	free();
}
