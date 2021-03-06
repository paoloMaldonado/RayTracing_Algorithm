#ifndef COMPUTATION_H    
#define COMPUTATION_H

#include "primitives/surface.h"

namespace rtm
{
struct Computation
{
    double tvalue;
    Surface* surface;
    Point point;
    Vector eyev;
    Vector normalv;
    Point over_point; // for acne effect - point moved slighly in the direction of normal 
    Vector reflectv;
    bool inside;
    Point under_point;
    // refractive indices
    double n1; 
    double n2;
};
} // namespace rtm

#endif