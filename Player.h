#include "Common.h"
#include "LTexture.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        //kich thuoc va van toc player
        static const int PLAYER_WIDTH = 20;
        static const int PLAYER_HEIGHT = 20;
        static const int PLAYER_VEL = 1;

        Player();
        bool loadPlayer(std::string path, SDL_Renderer* ren);
        void handleEvent(SDL_Event& e);
        void move();
        void render(SDL_Renderer* ren, int camX, int camY);

        int getPosX();
		int getPosY();

    private:
        //vi tri player
        int mPosX, mPosY;
        //van to theo huong Ox va Oy
        int mVelX, mVelY;
        //texture cua player
        LTexture mPlayerTex;
        //Rect bao phu player
        //SDL_Rect mCollider;
};

#endif // PLAYER_H
