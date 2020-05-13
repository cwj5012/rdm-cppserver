#include "Random.h"

namespace rdm {

Random::Random()
        : device_(),
          seed_(device_()),
          generator_(seed_) {
    ;
}

Random::Random(uint32_t seed)
        : device_(),
          seed_(device_()),
          generator_(seed) {

}

Random::~Random() {

}

uint32_t Random::generate() {
    return generator_();
}

int32_t Random::generate(uint32_t min, uint32_t max) {
    std::uniform_int_distribution<uint32_t> dis(min, max);
    return dis(generator_);
}

float Random::generatef(float min, float max) {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(generator_);
}

double Random::generated(double min, double max) {
    std::uniform_real_distribution<double> dis(min, max);
    return dis(generator_);
}

long double Random::generateld(long double min, long double max) {
    std::uniform_real_distribution<long double> dis(min, max);
    return dis(generator_);
}

void Random::setSeed(uint32_t seed) {
    seed_ = seed;
    generator_.seed(seed_);
}

}