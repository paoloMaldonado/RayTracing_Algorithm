#include <lighting/light.h>
#include <mat_entities/vector.h>
#include <mat_entities/point.h>
#include <mat_entities/vector_utility.h>
#include <mat_entities/tuple_utility.h>
#include <mat_entities/color.h>
#include <lighting/pointLight.h>
#include <materials/material.h>
#include <cmath>

using namespace rtm;

Color rtm::lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv)
{
    Color effective_color = material.get_color() * light.get_intensity();
    
    // find the direction to the light source
    Vector lightv = normalize(light.get_position() - point);

    // compute the ambient contribution
    Color ambient = effective_color * material.get_ambient();
    Color diffuse;
    Color specular;

    auto light_dot_normal = dot(lightv, normalv);
    if(light_dot_normal < 0)
    {
        diffuse = Color(0, 0, 0);
        specular = Color(0, 0, 0);
    }
    else
    {
        diffuse = effective_color * material.get_diffuse() * light_dot_normal;
        
        // compute the reflection vector
        auto reflectv = reflect(lightv, normalv);
        auto reflect_dot_eye = dot(reflectv, eyev);

        if(reflect_dot_eye <= 0)
        {
            specular = Color(0, 0, 0);
        }
        else
        {
            float factor = pow(reflect_dot_eye, material.get_shininess());
            specular = light.get_intensity() * material.get_specular() * factor;
        }
    }

    return ambient + diffuse + specular;
}
