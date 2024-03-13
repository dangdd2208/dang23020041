#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

class LTexture {
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(SDL_Renderer* gRenderer , std::string path);
    void free();
    void render(SDL_Renderer* gRenderer,int x, int y);
    int getWidth();
    int getHeight();
    void giammau(Uint8 alpha);

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif
