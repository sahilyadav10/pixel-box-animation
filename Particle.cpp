#include <cstdlib>
#include <math.h>
#include <SDL_timer.h>
#include "Particle.h"
#include "Screen.h"

namespace animation {

    // Constructor
    Particle::Particle(): mX(0), mY(0){
        mSpeed  =   (0.00008 *rand())/RAND_MAX ;
        mDirection = (double) 2.0 *M_PI*rand()/RAND_MAX;
    }

    // Updates coordinates of the particle after an interval of time
    void Particle::update(int interval) {
        // Speed in the x-coordinate
        double xSpeed = mSpeed * cos(mDirection);

        // Speed in the y-coordinate
        double ySpeed = mSpeed * sin(mDirection) ;


        // Updating x and y coordinates of one particle
        mX += xSpeed * interval;
        mY += ySpeed * interval;

        // Keep particles inside the window
        if(mX < -1.0 || mX > 1.0){
            mSpeed = -mSpeed;
        }

        if(mY < -1.0 || mY > 1.0){
            mSpeed = -mSpeed;
        }

    }
}