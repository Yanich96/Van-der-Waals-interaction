#include "SystemOscillators.h"
#include <iostream>

const real EIGEN_FREQUENCY = 5e16;
const real POLARIZATION = 2.03e-29;
const real PLANK = 1.05457266e-34; //Joule*sek



Eigen::Matrix3d SystemOscillators::forTwoAtoms(Eigen::Vector3d r) {
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity(3, 3);
    return (3 * r.normalized() * r.normalized().transpose() - I) / (r.norm() * r.norm() * r.norm());
}

Eigen::MatrixXd SystemOscillators::forSystemAtoms() {
    Eigen::MatrixXd Tensor(systemAtoms.size() * 3, systemAtoms.size() * 3);
    for (int i = 0; i < systemAtoms.size(); ++i) {
        for (int j = 0; j < systemAtoms.size(); ++j) {
            Eigen::Matrix3d tmp_matrix;
            if (i != j)
                tmp_matrix = forTwoAtoms(systemAtoms[i].position - systemAtoms[j].position);
            else
                tmp_matrix = Eigen::Matrix3d::Zero();

            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    Tensor(i * 3 + k, j * 3 + l) = tmp_matrix(k, l);
                }
            }
        }
    }
    Tensor = (-1) * POLARIZATION * Tensor;
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(systemAtoms.size() * 3, systemAtoms.size() * 3);
    return Tensor + I;
}


SystemOscillators::SystemOscillators(const std::vector<Oscillator> &vector) {
    systemAtoms = vector;
}

void SystemOscillators::addAtom(const Oscillator &r) {
    systemAtoms.push_back(r);
}

double SystemOscillators::TotalEnergy() {
    auto E = forSystemAtoms().eigenvalues();

    for (int i = 0; i < E.size(); ++i) {
        E(i) = sqrt(E(i)) * EIGEN_FREQUENCY;
    }
    std::cout << E;
    return 0.5 * PLANK * E.sum().real();
}

double SystemOscillators::EnergyVDW() {
    return TotalEnergy() - systemAtoms.size() * (1.5 * PLANK * EIGEN_FREQUENCY);
}


