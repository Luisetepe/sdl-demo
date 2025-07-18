#pragma once

#include <SDL3_image/SDL_image.h>
#include <string>

class LTexture
{
  public:
    // Initializes texture variables
    LTexture();

    // Cleans up texture variables
    ~LTexture();

    // Loads texture from disk
    bool loadFromFile(SDL_Renderer *renderer, std::string path);

    // Cleans up texture
    void destroy();

    // Draws texture
    void render(SDL_Renderer *renderer, float x, float y);

    // Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

  private:
    // Contains texture data
    SDL_Texture *mTexture;

    // Texture dimensions
    int mWidth;
    int mHeight;
};