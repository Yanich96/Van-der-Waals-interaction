#include "SystemOscillators.h"
#include <iostream>
#include "ShapeFactory.h"

const real NANO_M = 1e-9;

int main() {
    std::cout.precision(15);
    /*
     * Взаимодействие кубов из частиц
     */
    /*
    for (int i = 1; i < 200; ++i) {
        auto cube1 = create_cube(3, 5 * NANO_M);
        auto cube2 = create_cube(3, 5 * NANO_M);
        move(cube2, {0.05 * i * NANO_M, 0, 0});
        SystemOscillators systemCubes = join(cube1, cube2);
        std::cout << 0.05 * i * NANO_M << "\t" << systemCubes.EnergyVDW() << std::endl;
    }
     */

    /*
     * Взаимодействие вертикальных цепочек
     */
    std::vector<Oscillator> vertical1;
    for (int i = 0; i < 10; ++i) {
        vertical1.emplace_back(Oscillator{0, 0, i*NANO_M});
    }
    std::vector<Oscillator> vertical2;
    for (int i = 0; i < 10; ++i) {
        vertical2.emplace_back(Oscillator{0, 0, i*NANO_M});
    }

        move(vertical2, {0.01 * 2 * NANO_M, 0, 0});
        SystemOscillators systemVerticals = join(vertical1, vertical2);
        std::cout << 0.05 * 2 * NANO_M << "\t" << systemVerticals.TotalEnergy() << std::endl;



    /* for (int i = 1; i < 1000; ++i) {
          system_oscillators a;
          a.addAtom({0, 0, 0});
          a.addAtom({(0.01*NANO_M+0.01 * i*NANO_M), 0, 0});
          std::cout << (0.01 * i*NANO_M+ 0.01 * NANO_M) << "\t" << a.EnergyVDW() << std::endl;
      }*/



    /*float T = a.TotalEnergy();
    float W = a.EnergyVDW();
    std::cout << W << " ";
    for (int i = 0; i < 9; ++i) {
        std::cout << T[i] << " ";
        }
    for (int i = 0; i < 9; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < 9; ++j) {
            std::cout << R(i,j) << " ";
        }
    }*/

}