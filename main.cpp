#include "SystemOscillators.h"
#include <iostream>
#include "ShapeFactory.h"

const real NANO_M = 1e-9;

/*
 * Взаимодействие кубов из частиц
 */
void interactionOfCubes() {
    for (int i = 1; i < 100; ++i) {
        auto cube1 = createCube(3, 6 * NANO_M);
        auto cube2 = createCube(3, 6 * NANO_M);
        move(cube2, {(0.01 * i + 3) * NANO_M, 0, 0});
        SystemOscillators a = createCube(3, 1.5 * NANO_M);
        SystemOscillators systemCubes = join(cube1, cube2);
        std::cout << (0.01 * i) << "\t" << (systemCubes.totalEnergy() - 2 * a.totalEnergy()) * 1e17 << std::endl;
    }
}

/*
 * Взаимодействие вертикальных цепочек
 */
void interactionOfVertical() {
    std::vector<Oscillator> vertical1;
    std::vector<Oscillator> vertical2;
    for (int i = 0; i < 10; ++i) {
        vertical1.emplace_back(Oscillator{0, 0, i * 10 * NANO_M});
        vertical2.emplace_back(Oscillator{0, 0, (i * 10 + 5) * NANO_M});
    }
    SystemOscillators a = vertical2;
    for (int i = 1; i < 100; ++i) {
        move(vertical2, {(0.01 * i) * NANO_M, 0, 0});
        SystemOscillators systemVerticals = join(vertical1, vertical2);
        std::cout << 0.01 * i << "\t" << (systemVerticals.totalEnergy() - 2 * a.totalEnergy()) * 1e17 << std::endl;
    }
}

/*
 * Взаимодействие горизонтальных цепочек
 */
void interactionOfHorizontal() {
    std::vector<Oscillator> horizontal1;
    std::vector<Oscillator> horizontal2;
    for (int i = 0; i < 10; ++i) {
        horizontal1.emplace_back(Oscillator{NANO_M * i, 0, 0});
        horizontal2.emplace_back(Oscillator{NANO_M * i, 0, 0});
    }
    SystemOscillators a = horizontal2;
    move(horizontal2, {9 * NANO_M, 0, 0});
    for (int i = 1; i < 400; ++i) {
        move(horizontal2, {0.01 * i * NANO_M, 0, 0});
        SystemOscillators systemVerticals = join(horizontal1, horizontal2);
        std::cout << 0.01 * i << "\t" << (systemVerticals.totalEnergy() - 2 * a.totalEnergy()) * 1e17 << std::endl;
    }
}

int main() {
    std::cout.precision(15);

    // interactionOfHorizontal();
    // interactionOfVertical();
    interactionOfCubes();
}
