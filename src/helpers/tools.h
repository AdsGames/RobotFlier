/*
 * Tools
 * Allan Legemaate
 * 13/01/2017
 * Functions that may be needed by multiple files
 */
#ifndef HELPERS_TOOLS_H
#define HELPERS_TOOLS_H

/**
 * @brief Bounding box collision between two objects
 *
 * @param xMin1 Min x of entity 1
 * @param xMax1 Max x of entity 1
 * @param xMin2 Min x of entity 2
 * @param xMax2 Max x of entity 2
 * @param yMin1 Min y of entity 1
 * @param yMax1 Max y of entity 1
 * @param yMin2 Min y of entity 2
 * @param yMax2 Max y of entity 2
 * @return True if colliding, false otherwise
 */
extern bool collision(const float xMin1,
                      const float xMax1,
                      const float xMin2,
                      const float xMax2,
                      const float yMin1,
                      const float yMax1,
                      const float yMin2,
                      const float yMax2);

#endif  // HELPERS_TOOLS_H
