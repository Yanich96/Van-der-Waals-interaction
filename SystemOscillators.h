//
// Created by yana on 14.10.2020.
//

#ifndef OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H
#define OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H


#include <vector>
#include "eigen/Eigen/Eigen"
#include "Oscillator.h"

/*
    В этом классе используются формулы из статьи "An Efficient Coupled Dipole Method
    for the Accurate Calculation of van der Waals Interactions at the Nanoscale"
    Hye-Young Kim
*   Каждая функция в классе сопровождается номером формулы из статьи.
*/
typedef double real;

class SystemOscillators {
private:
    std::vector<Oscillator> systemAtoms;
/*
 * Функции "forTwoAtoms" и "forSystemAtoms" формируют матрицу из формулы №12.
 * "forSystemAtoms" возвращает матрицу (Q+I) из формулы №17.
 */
    Eigen::Matrix3d forTwoAtoms(Eigen::Vector3d r);
    Eigen::MatrixXd forSystemAtoms();

public:
    SystemOscillators()
    {}
    SystemOscillators(const std::vector<Oscillator>& vector);
    void addAtom(const Oscillator& r);
    /*
     * В функции "TotalEnergy" находятся собственные значения матрицы (Q+I)
     * и возвращается полная энергия системы. Используется формулв №18.
     */
    double TotalEnergy();
    /*
     * Функция "EnergyVDW" возвращает энергию взаимодействия  Ван дер Ваальса системы.
     * Энергия получается путем вычета из полной энергии системы энергии отдельных атомов.
     */
    double EnergyVDW();
};



#endif //OSCILLATOR_QUANT_SYSTEMOSCILLATORS_H
