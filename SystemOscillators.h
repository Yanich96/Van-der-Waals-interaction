#ifndef OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H
#define OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H

#include <vector>
#include "eigen/Eigen/Eigen"
#include "Oscillator.h"

typedef double real;

/*
    В этом классе используются формулы из статьи "An Efficient Coupled Dipole Method
    for the Accurate Calculation of van der Waals Interactions at the Nanoscale"
    Hye-Young Kim
*   Каждая функция в классе сопровождается номером формулы из статьи.
*/
class SystemOscillators {
private:
    std::vector<Oscillator> mAtoms;

    /*
     * Функции "makeTensor" и "forSystemAtoms" формируют матрицу из формулы №12.
     * "makeInteractionMatrix" возвращает матрицу (Q+I) из формулы №17.
     */
    Eigen::Matrix3d makeTensor(const Eigen::Vector3d& r);
    Eigen::MatrixXd makeInteractionMatrix();

public:
    SystemOscillators() = default;

    SystemOscillators(const std::vector<Oscillator>& vector);

    void addAtom(const Oscillator& r);

    /*
     * В функции "totalEnergy" находятся собственные значения матрицы (Q+I)
     * и возвращается полная энергия системы. Используется формулв №18.
     */
    double totalEnergy();

    /*
     * Функция "vdwEnergy" возвращает энергию взаимодействия  Ван дер Ваальса системы.
     * Энергия получается путем вычета из полной энергии системы энергии отдельных атомов.
     */
    double vdwEnergy();
};



#endif //OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H
