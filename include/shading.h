#ifndef SHADING_H
#define SHADING_H

#include "color.h"
#include "world.h"
#include "prepared_computation.h"

Color shade_hit(World &world, PreparedComputation &computation);

#endif