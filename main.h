#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<SDL_mixer.h>
#include<bits/stdc++.h>
#include <sstream>
#include <SDL_ttf.h>

//chieu dai va rong cua Window
const int SCREEN_WIDTH = 1200;
const  int SCREEN_HEIGHT = 696;
//vi tri ban dau cua vat
int vatdai = 125;
int vatrong = 400;
//chieu dai va rong cua nhan vat
const int chieudai = 60;
const int chieurong = 40;
//chieu rong va dai cua vat can
const int chieurongimage = 40;
const int imagewith=21;
const int sovatcantoida = 20;
const int sovatcantoida2 = 25;
const int Max_heath = 3;//so mang
const int chieurongheathy = 34;
//const int fbs = 60;
//vantoc
const float MOVE_SPEED = 20;
//thoi gian
Uint32 lastCollisionTime,dem = 0;
const Uint32 COOLDOWN_TIME = 1500;
int n = Max_heath;//so vat the ban dau

double barrierPositionsy[25];
int barrierPositionsx[25];
//khoi tao vi tri ban dau cho vat
void khoitao();
//toc do ban dau  :
double speed = 0.035,max_speed = 0.113;
double speed0 = 0.035;
double pace[25];
//mang song ban dau
int YourHeath = 3;
//window
SDL_Window* gWindow = NULL;
//render
SDL_Renderer* gRenderer = NULL;

SDL_Rect rect1 ;
SDL_Rect rect2 ;
//nhan vat
LTexture gFooTexture;
//nen
LTexture gBackgroundTexture;
//vat can
LTexture barrier[25];
//heath
LTexture heathy[Max_heath];
//trai tim rong
LTexture heathy2;
//nhac nen
Mix_Music* sound = NULL ;
//ttf
TTF_Font* gfont = NULL ;
//bool
bool kt ;
//Hamtaocuaso
bool init();

bool loadMedia();

void close();

void rendertext(const std::string &s ,int x ,int y );

void hieuungno(bool & quit , double &speed);

void resetGame();

void Menu(bool &quit);

double randomimage(int  a,int b);

bool checkCollision(SDL_Rect a, SDL_Rect b);

