/*
 * collide.h
 * ----------------------------
 * Declares the collide function, which is the
 * heart of our app. It processes all the collisions by
 * type number. It alone is several hundred lines
 * long, thus the need for a separate file.
 */

#ifndef COLLIDE_H_INCLUDE
#define COLLIDE_H_INCLUDE

//Include stdlib for random
#include <stdlib.h>
//Include the global variables
#include "app.h"
//Include the points functions
#include "points.h"

void collide (int fp, int sp);

#endif
