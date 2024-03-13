#include "LTexture.h"

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

//load file
bool LTexture::loadFromFile(SDL_Renderer *gRenderer , std::string path )
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

void LTexture::render(SDL_Renderer* gRenderer , int x, int y )
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
//tao hieu ung trong suot
void LTexture:: giammau(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture,alpha);
}

