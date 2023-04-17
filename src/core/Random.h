#pragma once

#include <stdlib.h>
#include "core/Colors.h"

namespace Random {
void seed(unsigned int seed);
int randomInt(int minInclusive, int maxExclusive);
float randomFloat01();
float randomFloat(float minInclusive, float maxExclusive);
bool randomBool();
Color randomColor();
Color randomColorHSV(float hMin = 0.0f,
                     float hMax = 1.0f,
                     float sMin = 0.0f,
                     float sMax = 1.0f,
                     float vMin = 0.0f,
                     float vMax = 1.0f);
} // namespace Random