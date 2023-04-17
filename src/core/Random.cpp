#include "Random.h"

void Random::seed(unsigned int seed) {
    srand(seed);
}

int Random::randomInt(int minInclusive, int maxExclusive) {
    return rand() % (maxExclusive - minInclusive) + minInclusive;
}

float Random::randomFloat01() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Random::randomFloat(float minInclusive, float maxExclusive) {
    return minInclusive +
           static_cast<float>(rand()) /
               static_cast<float>(RAND_MAX / (maxExclusive - minInclusive));
}

bool Random::randomBool() {
    return rand() % 2;
}

Color Random::randomColor() {
    return ImColor(randomFloat01(), randomFloat01(), randomFloat01());
}

Color Random::randomColorHSV(float hMin,
                             float hMax,
                             float sMin,
                             float sMax,
                             float vMin,
                             float vMax) {
    return ImColor::HSV(randomFloat(hMin, hMax), randomFloat(sMin, sMax),
                        randomFloat(vMin, vMax));
}
