#include "SystemOscillators.h"
#include <iostream>

const real EIGEN_FREQUENCY = 5e16;
const real POLARIZATION = 2.03e-29;
const real PLANK = 1.05457266e-34; //Joule*sek


SystemOscillators::SystemOscillators(const std::vector<Oscillator> &vector) {
    mAtoms = vector;
}

void SystemOscillators::addAtom(const Oscillator &r) {
    mAtoms.push_back(r);
}

Eigen::Matrix3d SystemOscillators::makeTensor(const Eigen::Vector3d& r) {
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity(3, 3);
    return (3 * r.normalized() * r.normalized().transpose() - I) / (r.norm() * r.norm() * r.norm());
}

Eigen::MatrixXd SystemOscillators::makeInteractionMatrix() {
    Eigen::MatrixXd tensor(mAtoms.size() * 3, mAtoms.size() * 3);
    for (int i = 0; i < mAtoms.size(); ++i) {
        for (int j = 0; j < mAtoms.size(); ++j) {
            Eigen::Matrix3d tmpMatrix;
            if (i != j)
                tmpMatrix = makeTensor(mAtoms[i].position - mAtoms[j].position);
            else
                tmpMatrix = Eigen::Matrix3d::Zero();

            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    tensor(i * 3 + k, j * 3 + l) = tmpMatrix(k, l);
                }
            }
        }
    }
    tensor = (-1) * POLARIZATION * tensor;
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(mAtoms.size() * 3, mAtoms.size() * 3);
    return tensor + I;
}

double SystemOscillators::totalEnergy() {
    auto E = makeInteractionMatrix().eigenvalues();

    for (int i = 0; i < E.size(); ++i) {
        E(i) = sqrt(E(i)) * EIGEN_FREQUENCY;
    }
    return 0.5 * PLANK * E.sum().real();
}

double SystemOscillators::vdwEnergy() {
    return totalEnergy() - mAtoms.size() * (1.5 * PLANK * EIGEN_FREQUENCY);
}
