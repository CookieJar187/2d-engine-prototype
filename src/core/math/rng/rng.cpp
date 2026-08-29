#include "rng.hpp"

uint32_t indexRNG = 0;

uint32_t randomFloatBase() {
    uint32_t i = (indexRNG | 314672065) * indexRNG << 5;
    i ^= !indexRNG & 814276494;
    i = i >> (indexRNG % 3);
    i += indexRNG * indexRNG ^ 3183430926 + (indexRNG * indexRNG + indexRNG & 91843) / 2;
    return i ^ 1853395471 + indexRNG * (indexRNG >> 4 + 1);
}
uint16_t randomIntBase() {
    uint16_t i = (indexRNG | 6291) * indexRNG << 5;
    i ^= !indexRNG & 12953;
    i = i >> (indexRNG % 3);
    i += indexRNG * indexRNG ^ 51294 + (indexRNG * indexRNG + indexRNG & 315) / 2;
    return i ^ 23176 + indexRNG * (indexRNG >> 4 + 1);
}

float rng::getFloat(uint16_t maxValue)
{
    uint32_t mantissa = randomFloatBase() >> 9;
    float finalValue = float(mantissa) / 8388608.0f;

    indexRNG++;
    return finalValue;
}
uint16_t rng::getInt(uint16_t maxValue)
{
    uint16_t finalValue = randomIntBase();
    uint16_t excessCount = finalValue / maxValue;

    finalValue -= excessCount * maxValue;

    indexRNG++;
    return finalValue;
}