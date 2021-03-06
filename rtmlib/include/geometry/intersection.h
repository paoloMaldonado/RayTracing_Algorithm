#ifndef INTERSECTION_H    
#define INTERSECTION_H

#include "primitives/surface.h"
#include <string>
#include <memory>

namespace rtm
{
class Intersection
{
    private:
        double m_t;
        Surface* m_object;

        bool is_equal(const Intersection& i) const;
    public:
        double u;
        double v;

        Intersection();
        Intersection(const double& t_val , const Surface* object_val);
        Intersection(const double& t_val , const Surface* object_val, const double& u, const double& v);

        double get_t() const;
        Surface* get_shape() const; 

        inline bool operator == (const Intersection& i) const {return this->is_equal(i);}

        // Useful for std::sort array of intersections 
        bool operator < (const Intersection& i) const;
};
} //namespace rtm

#endif