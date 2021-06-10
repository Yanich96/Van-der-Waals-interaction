#ifndef OSCILLATOR_QUANT_SHAPEFACTORY_H
#define OSCILLATOR_QUANT_SHAPEFACTORY_H


#include <vector>
#include "eigen/Eigen/Eigen"
#include "eigen/unsupported/Eigen/CXX11/Tensor"
#include "Oscillator.h"


typedef double real;

void move(std::vector<Oscillator> &shape, Eigen::Vector3d distance)
{
    for (int i = 0; i < shape.size(); ++i) {
        shape[i].position += distance;
    }
}

std::vector<Oscillator> join(const std::vector<Oscillator> &shape1, const std::vector<Oscillator> &shape2) {
    std::vector<Oscillator> result;
    result.insert(result.end(), shape1.begin(), shape1.end());
    result.insert(result.end(), shape2.begin(), shape2.end());
    return result;
}

std::vector<Oscillator> createCube(int atomsInEdge, real distance) {
    std::vector<Oscillator> atoms;
    for (int x = 0; x < atomsInEdge; ++x) {
        for (int y = 0; y < atomsInEdge; ++y) {
            for (int z = 0; z < atomsInEdge; ++z) {
                atoms.emplace_back(x * distance, y * distance, z * distance);
            }
        }
    }
    return atoms;
}

std::vector<Oscillator> createParallelepiped(int atomsInWidth, int atomsInHeight, int atomsInDepth, real distance) {
    std::vector<Oscillator> atoms;
    for (int x = 0; x < atomsInWidth; ++x) {
        for (int y = 0; y < atomsInHeight; ++y) {
            for (int z = 0; z < atomsInDepth; ++z) {
                atoms.push_back({x * distance, y * distance, z * distance});
            }
        }
    }
    return atoms;
}

std::vector<Oscillator> create_sphere(int atomsInRadius, real distance) {
    std::vector<Oscillator> system_atoms;
    float zenit = 180;
    float azimut = 360;
    system_atoms.push_back({0, 0, 0});
    for (int i = 1; i < atomsInRadius; i++) {
        for (int j = 1; j < azimut; ++j) {
            for (int k = 1; k < zenit; ++k) {
                system_atoms.push_back(
                        {i * sin(zenit) * cos(azimut) * distance, i * sin(zenit) * sin(azimut) * distance,
                         i * distance * cos(zenit)});
            }

        }
    }
    return system_atoms;
}

#endif //OSCILLATOR_QUANT_SHAPEFACTORY_H
