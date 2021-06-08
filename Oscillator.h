#ifndef OSCILLATOR_QUANT_OSCILLATOR_H
#define OSCILLATOR_QUANT_OSCILLATOR_H

typedef double real;
struct Oscillator {
    Eigen::Vector3d position;

    Oscillator(real x, real y, real z) {
        position = {x, y, z};
    }

    Oscillator(Eigen::Vector3d position) {
        this->position = position;
    }
};

#endif //OSCILLATOR_QUANT_OSCILLATOR_H