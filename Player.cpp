#include "Player.h"

Player::Player()
{
    //khoi tao kich thuoc va van toc ban dau
    mPosX = 0;
    mPosY = 0;
    mVelX = 0;
    mVelY = 0;
}
//tai anh cho player
bool Player::loadPlayer(std::string path, SDL_Renderer* ren)
{
    return mPlayerTex.loadFromFile(path, ren);

}
//xu ly khi an phim
void Player::handleEvent(SDL_Event& e)
{
    //an phim
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //dieu chinh van toc
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY -= PLAYER_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER_VEL; break;
            case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
        }
    }
    //tha phim
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //dieu chinh van toc
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += PLAYER_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
            case SDLK_LEFT: mVelX += PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
        }
    }
}

void Player::move()
{
    //player di chuyen huong Ox
    mPosX += mVelX;
    //di qua gioi han
    if((mPosX < 0) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH))
    {
        //lui lai
        mPosX -= mVelX;
    }

    //player di chuyen huong Oy
    mPosY += mVelY;
    //di qua gioi han
    if((mPosY < 0) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT))
    {
        //lui lai
        mPosY -= mVelY;
    }
}
//hien thi player
void Player::render(SDL_Renderer* ren)
{
    mPlayerTex.render(ren, mPosX, mPosY);
}
