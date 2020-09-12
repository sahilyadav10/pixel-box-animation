#ifndef ANIMATION_SCREEN_H
#define ANIMATION_SCREEN_H

#include <SDL.h>

namespace animation {

    class Screen{
    public:
        // Dimensions of the window
        static const int SCREEN_HEIGHT = 640;
        static const int SCREEN_WIDTH = 480;

    private:
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        SDL_Texture *mTexture;
        Uint32 *mBuffer;

    public:
        // Constructor
        Screen();

        // Create the window, renderer, and texture
        bool init();

        // Clear previously drawn pixels (set their colour back to black)
        void clear();

        // Set colour to a pixel
        void setPixelColour(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

        // Draw the screen
        void update();

        // Check for pending events (it can be done from the main loop and does not suspend the main loop while waiting on an event to be posted)
        int processEvents();

        // Close all the subprocesses
        void close();
    };

}

#endif //ANIMATION_SCREEN_H
