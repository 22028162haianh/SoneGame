#include "Player.h"

Player::Player()
{
    //khoi tao kich thuoc va van toc ban dau
    mPosX = 0;
    mPosY = 0;
    mVelX = 0;
    mVelY = 0;

    //mCollider.w = PLAYER_WIDTH;
    //mCollider.h = PLAYER_HEIGHT;
}
//tai anh cho player
bool Player::loadPlayer(std::string path, SDL_Renderer* ren)
{
    bool e = mPlayerTex.loadFromFile(path, ren);
    if(e){
        //mCollider.w = mPlayerTex.getWidth();
        //mCollider.h = mPlayerTex.getHeight();
    }
    return e;

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
    //mCollider.x = mPosX;
    //di qua gioi han hoac va cham
    if((mPosX < 0) || (mPosX + PLAYER_WIDTH > LEVEL_WIDTH) /*|| checkCollision(mCollider, wall)*/)
    {
        //lui lai
        mPosX -= mVelX;
        //mCollider.x = mPosX;
    }

    //player di chuyen huong Oy
    mPosY += mVelY;
    //mCollider.y = mPosY;
    //di qua gioi han
    if((mPosY < 0) || (mPosY + PLAYER_HEIGHT > LEVEL_HEIGHT) /*|| /*checkCollision(mCollider, wall)*/)
    {
        //lui lai
        mPosY -= mVelY;
        //mCollider.y = mPosY;
    }
}
//hien thi player
void Player::render(SDL_Renderer* ren, int camX, int camY)
{
    mPlayerTex.render(ren, mPosX - camX, mPosY - camY);
}

int Player::getPosX()
{
    return mPosX;
}

int Player::getPosY()
{
    return mPosY;
}
