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

    // Load surface
    if (SDL_Surface *loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
    } else {
        // Create texture from surface
        if (mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); mTexture == nullptr) {
            SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
        } else {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    // Return success if texture loaded
    return mTexture != nullptr;
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