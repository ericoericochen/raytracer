#include "../include/shading.h"
#include "../include/world.h"
#include "../include/prepared_computation.h"
#include "../include/light.h"

Color shade_hit(World &world, PreparedComputation &comps)
{
    return lighting(
        comps.object->material,
        world.light,
        comps.point,
        comps.eyev,
        comps.normalv);
}
