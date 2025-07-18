#include "texture.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>


// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow{ nullptr };

// The renderer used to draw to the window
SDL_Renderer *gRenderer{ nullptr };

// The directional images
LTexture gDownTexture;
LTexture gLeftTexture;
LTexture gRightTexture;
LTexture gUpTexture;

int main(int argc, char *argv[])
{
    // Final exit code
    int exitCode{ 0 };

    // Initialize
    if (!init()) {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    } else {

        // Load media
        if (!loadMedia()) {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        } else {
            // The quit flag
            bool quit{ false };

            // The event data
            SDL_Event e;
            SDL_zero(e);

            // Pointer to the current texture
            LTexture *currentTexture{ &gUpTexture };
            // Background color defaults to white
            SDL_Color bgColor{ 0xFF, 0xFF, 0xFF, 0xFF };

            // The main loop
            while (!quit) {
                // Get event data
                while (SDL_PollEvent(&e)) {
                    // If event is quit type
                    if (e.type == SDL_EVENT_QUIT) {
                        // End the main loop
                        quit = true;

                    }
                    // On keyboard key press
                    else if (e.type == SDL_EVENT_KEY_DOWN) {
                        if (e.key.key == SDLK_A) {
                            currentTexture = &gLeftTexture;
                        } else if (e.key.key == SDLK_D) {
                            currentTexture = &gRightTexture;
                        } else if (e.key.key == SDLK_W) {
                            currentTexture = &gUpTexture;
                        } else if (e.key.key == SDLK_S) {
                            currentTexture = &gDownTexture;
                        }
                    }
                }

                // Fill the background with the selected color
                SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
                SDL_RenderClear(gRenderer);

                // Render image on screen
                currentTexture->render(gRenderer,
                                       // Center the texture on the screen
                                       (kScreenWidth - currentTexture->getWidth()) * 0.5f,
                                       (kScreenHeight - currentTexture->getHeight()) * 0.5f);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }

        // Clean up
        close();
    }

    return exitCode;
}

bool init()
{
    // Initialization flag
    bool success{ true };

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window with renderer
        if (!SDL_CreateWindowAndRenderer("SDL3 Tutorial: Textures and Extension Libraries",
                                         kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer)) {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool loadMedia()
{
    // File loading flag
    bool success{ true };

    // Load splash image
    if (!gUpTexture.loadFromFile(gRenderer, "assets/up.png")) {
        SDL_Log("Unable to load UP png image!\n");
        success = false;
    }

    // Load down image
    if (!gDownTexture.loadFromFile(gRenderer, "assets/down.png")) {
        SDL_Log("Unable to load DOWN png image!\n");
        success = false;
    }

    // Load left image
    if (!gLeftTexture.loadFromFile(gRenderer, "assets/left.png")) {
        SDL_Log("Unable to load LEFT png image!\n");
        success = false;
    }

    // Load right image
    if (!gRightTexture.loadFromFile(gRenderer, "assets/right.png")) {
        SDL_Log("Unable to load RIGHT png image!\n");
        success = false;
    }

    return success;
}

void close()
{
    // Clean up texture
    gUpTexture.destroy();
    gDownTexture.destroy();
    gLeftTexture.destroy();
    gRightTexture.destroy();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}