#include "texture.hpp"

LTexture::LTexture() : // Initialize texture variables
                       mTexture{ nullptr },
                       mWidth{ 0 },
                       mHeight{ 0 }
{
}

LTexture::~LTexture()
{
    // Clean up texture
    destroy();
}

bool LTexture::loadFromFile(SDL_Renderer *renderer, std::string path)
{
    // Clean up texture if it already exists
    destroy();

    SDL_Surface *loadedSurface{ nullptr };

    // Load surface
    if (loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    // Color key image
    if (!SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0x00, 0xFF, 0xFF))) {
        SDL_Log("Unable to color key! SDL error: %s", SDL_GetError());
        SDL_DestroySurface(loadedSurface);
        return false;
    }

    // Create texture from surface
    if (mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); mTexture == nullptr) {
        SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
        SDL_DestroySurface(loadedSurface);
        return false;
    }

    // Get image dimensions
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    // Clean up loaded surface
    SDL_DestroySurface(loadedSurface);

    // Return success if texture loaded
    return true;
}

void LTexture::render(SDL_Renderer *renderer, float x, float y)
{
    // Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

    // Render texture
    SDL_RenderTexture(renderer, mTexture, nullptr, &dstRect);
}

void LTexture::destroy()
{
    // Clean up texture
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}