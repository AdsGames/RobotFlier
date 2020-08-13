/*
 * Tools Class
 * Allan Legemaate
 * 13/01/2017
 * Functions that may be needed by multiple files
 */
#ifndef HELPERS_TOOLS_H
#define HELPERS_TOOLS_H

#include <string>

extern void abort_on_error(const std::string& message);

// Math related functions
extern bool collision(const float xMin1,
                      const float xMax1,
                      const float xMin2,
                      const float xMax2,
                      const float yMin1,
                      const float yMax1,
                      const float yMin2,
                      const float yMax2);

#endif  // HELPERS_TOOLS_H
