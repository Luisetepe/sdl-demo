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

    // Remove copy constructor
    LTexture(const LTexture &) = delete;

    // Remove copy assignment
    LTexture &operator=(const LTexture &) = delete;

    // Remove move constructor
    LTexture(LTexture &&) = delete;

    // Remove move assignment
    LTexture &operator=(LTexture &&) = delete;

    // Loads texture from disk
    bool loadFromFile(SDL_Renderer *renderer, std::string path);

    // Cleans up texture
    void destroy();

    // Draws texture
    void render(SDL_Renderer *renderer, float x, float y);

    // Gets texture attributes
    inline int getWidth() { return mWidth; }
    inline int getHeight() { return mHeight; }
    inline bool isLoaded() { return mTexture != nullptr; }

  private:
    // Contains texture data
    SDL_Texture *mTexture;

    // Texture dimensions
    int mWidth;
    int mHeight;
};