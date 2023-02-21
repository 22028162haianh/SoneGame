#include "Common.h"
#include "LTexture.h"
#include "Player.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

Player p;
LTexture bg;

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
    if(!bg.loadFromFile("img/bg.png", gRenderer))
    {
        std::cout << "Failed to load background texture! ";
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
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            bool quit = false;
            SDL_Event e;
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) quit = true;
                    p.handleEvent(e);
                }
                p.move();
                //Center the camera over the dot
				camera.x = (p.getPosX() + Player::PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
				camera.y = (p.getPosY() + Player::PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

				//Keep the camera in bounds
				if( camera.x < 0 ){
					camera.x = 0;
				}
				if( camera.y < 0 ){
					camera.y = 0;
				}
				if( camera.x > LEVEL_WIDTH - camera.w ){
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if( camera.y > LEVEL_HEIGHT - camera.h ){
					camera.y = LEVEL_HEIGHT - camera.h;
				}
                //background tam thoi mau trang
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                bg.render(gRenderer, 0, 0, &camera);

                p.render(gRenderer, camera.x, camera.y);

                SDL_RenderPresent(gRenderer);

                SDL_Delay(1);
            }
        }
    }
    close();
    return 0;
}
