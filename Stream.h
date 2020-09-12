#ifndef ANIMATION_STREAM_H
#define ANIMATION_STREAM_H

#include "Particle.h"

namespace animation {

    class Stream {
    public:
        // Total number of particles in the animation
        const static int TOTALPARTICLES = 1000;

    private:
        // Pointer (therefore cannot go out of scope until delete is used)
        Particle *mParticles;

        // Time elapsed till the last iteration
        int lastTime;

    public:
        // Constructor
        Stream();

        // Destructor
        ~Stream();

        // Return private member (mParticles) to be used outside of the class
        Particle *getParticles(){
            return mParticles;
        };

        // Calls particle update function on individual particle
        void update(int timeElapsed);
    };

}

#endif //ANIMATION_STREAM_H
