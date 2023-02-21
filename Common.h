#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
//kich thuoc map
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;
//kich thuoc man hinh
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//kiem tra va cham 2 Rect
static bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //kich thuoc 2 Rect
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //set vien cho rect a
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //set vien cho rect b
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB){
        return false;
    }

    if(topA >= bottomB){
        return false;
    }

    if(rightA <= leftB){
        return false;
    }

    if(leftA >= rightB){
        return false;
    }
    //khong nam ngoai nhau thi va nhau
    return true;
}
