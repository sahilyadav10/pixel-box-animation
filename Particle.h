#ifndef ANIMATION_PARTICLE_H
#define ANIMATION_PARTICLE_H

namespace animation {

    struct Particle {
        // x-coordinate
        double mX;
        // y-coordinate
        double mY;

        // Speed of the particle
        double mSpeed;
        // Direction of the particle
        double mDirection;

    public:
        // Constructor
        Particle();

        // Updates coordinates of a particle after an interval of time
        void update(int interval);
    };

}

#endif //ANIMATION_PARTICLE_H
