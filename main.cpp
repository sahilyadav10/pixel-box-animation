#include <iostream>
#include <math.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_timer.h>
#include "Screen.h"
#include "Stream.h"

using namespace animation;

int main() {
	SDL_SetMainReady();

    // Instance of class Screen
    Screen screen;

    // Initialize the program
    if(screen.init() == false){
        std::cout << "Error initializing SDL" << std::endl;
    }

    // Instance of class Stream
    Stream stream;

    int multiplier = 0;

    // Runs until
    while(true){

        int timeElapsed = SDL_GetTicks();

        // Clear previously drawn pixels (set their colour back to black)
        screen.clear();

        // Updates the location of particles
        stream.update(timeElapsed);

        // Colours for particles
        unsigned char red = 0;
        unsigned char blue = 0;
        unsigned char green = 0;

        // Check for pending events, processEvents() returns 0 when user clicks on the close button of the window and 2 when user clicks anywhere on the window
        int flag = screen.processEvents();

        if( flag == 0){
            break;
        }
        else if(flag == 2){
            multiplier += 2;
            if(multiplier >= 6) multiplier = 1;
        }

        // RGB colour scheme for pixels, changes with time elapsed
        red = (unsigned char) ((1 + sin(timeElapsed * multiplier * 0.0002)) * 127);
        green = (unsigned char) ((1 + cos(timeElapsed * multiplier * 0.0001)) * 127);
        blue = (unsigned char) ((1 + cos(timeElapsed * 0.0004)) * 127);


        // Pointer to Particle
        Particle *pParticle = stream.getParticles();

        // Set the same colour to all particles
        for(int i=0; i < Stream:: TOTALPARTICLES; i++) {
            Particle particle = pParticle[i];

            // Coordinates of particles from the center of the window
            int x = (particle.mX + 1) * Screen::SCREEN_WIDTH / 2;
            int y = (particle.mY + 1) *  Screen::SCREEN_HEIGHT/2;

            // Set the given colour to the pixel at given x and y coordinates
            screen.setPixelColour(x, y, red, green, blue);
        }

        // Draw the screen
        screen.update();
    }

    // Clear the buffer memory, destroy the renderer and texture, close the window and clean up all the initialized subsystems.
    screen.close();

    return 0;
}