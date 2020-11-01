/*
 * Random
 * Allan Legemaate
 * Random number generator
 * 11/08/2020
 */
#ifndef ENGINE_RANDOM_RANDOM_GENERATOR_H
#define ENGINE_RANDOM_RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
 public:
  static float randomFloat(const float min, const float max);
  static int randomInt(const int min, const int max);

 private:
  static std::mt19937 rng;
};

#endif  // ENGINE_RANDOM_RANDOM_GENERATOR_H
