#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<SDL_mixer.h>
#include<bits/stdc++.h>
#include <sstream>

//chieu dai va rong cua Window
const int SCREEN_WIDTH = 1200;
const  int SCREEN_HEIGHT = 696;
int vatdai = 125;
int vatrong = 300;
const int chieudai = 60;
const int chieurong = 40;
const int chieurongimage = 40;
const int imagewith=21;
const int sovatcantoida = 20;
int n=3;//so vat the ban dau

double *barrierPositionsy = new double [n];
void khoitao()
{
for(int i = 0; i < sovatcantoida; i++)
{
    barrierPositionsy[i] = 0;
}

}

//Texture
class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile( std::string path );

		void free();

		void render( int x, int y );

		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Hamtaocuaso
bool init();

bool loadMedia();

void close();

//window
SDL_Window* gWindow = NULL;

//render
SDL_Renderer* gRenderer = NULL;

LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture barrier[sovatcantoida];

//mixer nen
Mix_Music* sound = NULL ;
//
Mix_Chunk* bomno = NULL ;
Mix_Chunk* phim = NULL ;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	//Load anh
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		return false;
	}
	else
	{
		//phu mau cho anh chen (anh chen nen de mau tieu chuan RGB)
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
		     return false;
		}
		else
		{

            mWidth = loadedSurface -> w;
			mHeight = loadedSurface -> h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture ;
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y )
{
	//Dieu chinh render
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				success = false;
			}
			else
			{

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{

					success = false;
				}

				//mixer :
				if( Mix_OpenAudio( 48000, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	for(int i=0;i < sovatcantoida ; i++)
    {
        if( !barrier[i].loadFromFile("barrier.png") )
        {
            success=false;
        }
    }
	if( !gFooTexture.loadFromFile( "plane_fly.png" ) )
	{

		success = false;
	}

	if( !gBackgroundTexture.loadFromFile( "abcd.jpg" ) )
	{
		success = false;
	}

    //load music
    sound = Mix_LoadMUS( "8bit-music-for-game-68698.mp3" );
    if( sound == NULL )
	{
		success = false;
	}
    bomno = Mix_LoadWAV("8-bit-video-game-fail-version-2-145478.mp3");
    if(bomno == NULL)
    {
        success = false;
    }
    phim =Mix_LoadWAV("mech-keyboard-02-102918.mp3");
    if(phim ==  NULL)
    {
        success = false;
    }

	return success;
}

void close()
{
	for(int i=0;i<sovatcantoida;i++)
        barrier[i].free() ;
	gFooTexture.free();
	gBackgroundTexture.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//close music
    Mix_FreeMusic(sound);

    Mix_FreeChunk(bomno);
    Mix_FreeChunk(phim);

    Mix_CloseAudio();

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

double  randomimage(int a,int b)
{
    return rand()%(b-imagewith)+a;
}

double speed = 0.05;

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    // rect của a
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    //rect cua b
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    //co  va cham neu :
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    // day la khi khong va cham
    return true;
}

int main( int argc, char* args[] )
{

	if( !init() )
	{
		return 0;
	}
	else
	{

		if( !loadMedia() )
		{
			return 0;
		}
		else
		{
			// flag
			bool quit = false;

			//Event
			SDL_Event e;
			int barrierPositionsx[10];

			//nhac
            Mix_PlayMusic(sound,-1);

            for(int i=0;i<n;i++)
            {
                barrierPositionsx[i]=randomimage(0,SCREEN_WIDTH);
            }
			//tao vong lap vo han
			while( !quit )
			{

			   // bat su kien:
				while( SDL_PollEvent( &e ) != 0 )
				{


					//tat cua so:
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					else if(e.type==SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_UP : case SDLK_w :
                            vatrong -= chieurong/3;
                            Mix_PlayChannel(-1,phim,0);
                            if(vatrong < 0 ) vatrong = 0;
                            break;

                        case SDLK_DOWN : case SDLK_s :
                             vatrong += chieurong/3;
                             Mix_HaltChannel(0);
                             Mix_PlayChannel(-1,phim,0);
                            if(vatrong + chieurong >= SCREEN_HEIGHT) vatrong = SCREEN_HEIGHT-chieurong;
                             break;

                        case SDLK_RIGHT : case SDLK_d :
                            vatdai += chieudai/4;
                            Mix_PlayChannel(-1,phim,0);
                            if(vatdai + chieudai > SCREEN_WIDTH) vatdai = SCREEN_WIDTH-chieudai;
                            break;

                        case SDLK_LEFT : case SDLK_a :
                            vatdai -=  chieudai/4;
                            Mix_PlayChannel(-1,phim,0);
                            if(vatdai < 0) vatdai = 0;
                            break;

                        default :
                            Mix_PlayChannel(-1,phim,0);
                            break;

                         }
                     }
				  }

				// tao lai mau tren cua so
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//background
				gBackgroundTexture.render( 0, 0 );

				//lam cho no muot hon
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

				//vi tri cua main:
				gFooTexture.render( vatdai, vatrong );

				//Update :
                SDL_Rect rect1={vatdai,vatrong,chieudai,chieurong};
				for(int i=0;i<n;i++)
                {
                  barrierPositionsy[i]+=speed;

                  if(barrierPositionsy[i]>SCREEN_HEIGHT-chieurongimage)
                  {

                      barrierPositionsy[i] = randomimage(0,100);

                      barrierPositionsx[i] = randomimage(0,SCREEN_WIDTH);

                      barrierPositionsy[i] += randomimage(speed,speed*1.1);

                      n++;

                      if(n>sovatcantoida) {
                            n = sovatcantoida;
                      }

                  }

                  SDL_Rect rect2={barrierPositionsx[i],barrierPositionsy[i],imagewith,chieurongimage};
                  if(checkCollision(rect1,rect2))
                  {
                      Mix_PlayChannel(-1,bomno,0);
                      quit = true ;
                  }
                barrier[i].render(barrierPositionsx[i],barrierPositionsy[i]);
                }
                 SDL_RenderPresent(gRenderer);
			}
		}

	}

	//dong va giai phong bo nho
	close();

	return 0;
}
