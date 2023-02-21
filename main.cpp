#include "Common.h"
#include "LTexture.h"
#include "Player.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

Player p;

bool init();
bool loadMedia();
void close();

bool init()
{
	bool sc = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize!" << SDL_GetError();
        sc = false;
	}
	else{
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            std::cout << "Warning: Linear texture filtering not enabled!";
        }
        gWindow = SDL_CreateWindow( "SONE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError();
			sc = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if( gRenderer == NULL )
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError();
				sc = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: ", IMG_GetError();
					sc = false;
				}
			}
		}
	}
	return sc;
}

bool loadMedia()
{
    bool sc = true;
    if(!p.loadPlayer("img/dot.bmp", gRenderer)){
        std::cout << "Failed to load texture image! ";
        sc = false;
    }
    return sc;
}

void close()
{
    //Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[])
{
    if(!init()){
        std::cout << "Failed to initialize";
    }
    else{
        if(!loadMedia()){
            std::cout << "Failed to load media";
        }
        else{
            bool quit = false;
            SDL_Event e;
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) quit = true;
                    p.handleEvent(e);
                }
                p.move();
                //background tam thoi mau trang
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                p.render(gRenderer);

                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}
