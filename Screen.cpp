#include <iostream>
#include "Screen.h"
namespace animation {

    // Constructor
    Screen::Screen() :
            mWindow(NULL), mRenderer(NULL), mTexture(NULL), mBuffer(NULL) {

    }


    // Create the window, renderer, and texture
    bool Screen::init(){
        // In case of Initialization fails
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "Initialization failed" << std::endl;
        }

        // Create a window
        mWindow = SDL_CreateWindow("Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_OPENGL);

        // Check if the window was created
        if(mWindow == NULL){
            std::cout << "Window can't be created";
            SDL_Quit();
            return false;
        }

        // Create a Renderer
        mRenderer = SDL_CreateRenderer(mWindow, -1,SDL_RENDERER_PRESENTVSYNC);

        // Create a Texture
        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Check if the renderer was created
        if(mRenderer == NULL){
            SDL_DestroyWindow(mWindow);
            SDL_Quit();
            return false;
        }

        // Check if the texture was created
        if(mTexture == NULL){
           SDL_DestroyRenderer(mRenderer);
           SDL_DestroyWindow(mWindow);
           SDL_Quit();
           return false;
        }

        // Buffer to store pixels and it stores 32 bits for each pixel ( 8 bits for each red, yellow, blue colours and transparency value)
        mBuffer = new Uint32[SCREEN_HEIGHT*SCREEN_WIDTH]; //Uint32 same as int but ensures 32 bits on all system

        // Set all pixels to black colour and remove any garbage value
        memset(mBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        return true;
    }



    // Clear previously drawn pixels (set their colour back to black)
    void Screen::clear() {
        memset(mBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    }



    // Set colour to a pixel
    void Screen::setPixelColour(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        // Prevent the program from drawing pixels that go out of the screen
        if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT){
            return;
        }

        Uint32 colour = 0;
        colour += red;
        colour <<= 8;
        colour += green;
        colour <<= 8;
        colour += blue;
        colour <<= 8;
        colour += 0xFF;
        mBuffer[(y * SCREEN_WIDTH ) + x] = colour;
    }



    // Draw the screen
    void Screen::update() {
        // Update texture with new pixel data
        SDL_UpdateTexture(mTexture, NULL, mBuffer, SCREEN_WIDTH*sizeof(Uint32));

        // To clear the window data
        SDL_RenderClear(mRenderer);

        // Copy the texture to the render
        SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);

        //The renderer is basically an SDL_Window* that is hidden from the user where the graphics are rendered at first, then
        // the rendered data gets switched with the window's data using SDL_RenderPresent
        SDL_RenderPresent(mRenderer);
    }



    // Check for pending events
    int Screen::processEvents(){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            // SDL_QUIT is generated when the close button of the window is clicked
            if(event.type == SDL_QUIT){
                return 0;
            }
            // SDL_MOUSEBUTTONUP is generated when a mouse button is clicked (released after pressing)
            else if(event.type == SDL_MOUSEBUTTONUP){
                int flag = 2;
                return flag;
            }
        }
        return 1;
    }



    // Close all the subprocesses
    void Screen::close(){
        //Clears the buffer
        delete []mBuffer;

        // Destroys the texture
        SDL_DestroyTexture(mTexture);

        // Destroys the renderer
        SDL_DestroyRenderer(mRenderer);

        // Close and destroy the window
        SDL_DestroyWindow(mWindow);

        // Clean up all the intialized subsystems
        SDL_Quit();

    }

}
