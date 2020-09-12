#include "Stream.h"
#include "Particle.h"
namespace animation {

    // Constructor
    Stream::Stream():lastTime(0){
        // Dynamic memory allocation for the stream of particles
        mParticles = new Particle[Stream::TOTALPARTICLES];
    }

    // Update location of particles by calling particle update function on individual particle
    void Stream::update(int timeElapsed) {
        int interval = timeElapsed - lastTime;
        for(int i = 0; i < TOTALPARTICLES; i++) {
            mParticles[i].update(interval);
        }

        lastTime = timeElapsed;
    }

    // Destructor
    Stream::~Stream(){
        delete [] mParticles;
    }

}
