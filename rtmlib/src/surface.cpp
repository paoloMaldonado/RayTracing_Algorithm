#include "primitives/surface.h"

using namespace rtm;

Surface::Surface() : m_transform{Matrix(4, 4)}, m_material(Material())
{
    m_transform.set_identity();
    m_parent = nullptr;
    m_children = {};
}

Surface::Surface(const Surface& s)
{
    m_material = s.m_material;
    m_transform = s.m_transform;
    m_children = s.m_children;
}

bool Surface::compare(const Surface* s) const
{
    // compare two pointers (memory addresses of each surfaces)
    if(this == s)
        return  true;
    else
        return false;
}

// converts point from world space to object space
Point Surface::world_to_object(const Point& p) const
{
    auto point = p;
    if(this->has_parent())
    {
        // convert the point first from world space to parent space
        point = this->get_parent()->world_to_object(point);
    }

    return inverse(m_transform) * point;
}

// converts normal from object to world space
Vector Surface::normal_to_world(const Vector& normal_vector) const
{
    auto normal = normal_vector;

    normal = (inverse(m_transform)).transpose() * normal;
    normal.set_w(0);
    normal = normalize(normal);

    if(this->has_parent())
    {
        normal = this->get_parent()->normal_to_world(normal);
    }

    return normal;
}
