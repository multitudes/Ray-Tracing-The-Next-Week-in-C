
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:59:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/18 14:25:03 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <stdbool.h>
#include <math.h>
#include "rtweekend.h"

typedef struct 	s_vec3
{
	union {
        struct {
            double x;
            double y;
            double z;
        };
        struct {
            double r;
            double g;
            double b;
        };
	};
}				t_vec3, t_color, t_point3;

t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);

t_vec3		vec3negate(const t_vec3 a);
t_vec3		vec3add(const t_vec3 a, const t_vec3 b);
t_vec3		vec3substr(const t_vec3 a, const t_vec3 b);
t_vec3		vec3mult(const t_vec3 a, const t_vec3 b);
t_vec3		vec3multscalar(const t_vec3 a, double t);
t_vec3		vec3divscalar(const t_vec3 a, double t);
	
double		length_squared(const t_vec3 v);
double		length(const t_vec3 v);
void		print_vec3(const t_vec3 *v);
double		dot(const t_vec3 a, const t_vec3 b);
t_vec3		vec3cross(const t_vec3 a, const t_vec3 b);
t_vec3		random_vec3();
t_vec3		random_vec3_min_max(double min, double max);
bool 		near_zero(t_vec3 e); 

inline t_vec3 unit_vector(t_vec3 v)
{
	return vec3divscalar(v, length(v));
}

/*
 * Random vector in unit disk
 */
inline t_vec3 random_in_unit_disk() 
{
    while (1) 
	{
        t_vec3 p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (length_squared(p) < 1)
            return p;
    }
}

/*
 * Random vector in unit sphere
 */
inline t_vec3 random_in_unit_sphere() 
{
    while (1) {
        t_vec3 p = random_vec3_min_max(-1,1);
        if (length_squared(p) < 1)
            return p;
    }
}

/*
 * Random unit vector in unit 
 */
inline t_vec3 random_unit_vector() 
{
    return unit_vector(random_in_unit_sphere());
}

/*
 * Random vector on the correct hemisphere. We just need to check the dot product
 * of the random vector with the normal. If it is negative, we negate the vector.
 * We acually just care about having a random vector in the hemisphere of the normal.
 */
inline t_vec3 random_on_hemisphere(const t_vec3 normal) 
{
    t_vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return vec3negate(on_unit_sphere);
}

inline t_vec3	reflect(const t_vec3 v, const t_vec3 n) 
{
    return vec3substr(v, vec3multscalar(n, dot(v, n) * 2));
}

/*
 * Refract function
 * params: uv, n, etai_over_etat
 * uv: unit vector of the ray
 * n: normal of the surface
 * etai_over_etat: ratio of the refractive indices
 */
inline t_vec3 refract(const t_vec3 uv, const t_vec3 n, double etai_over_etat) 
{
    double cos_theta = fmin(dot(vec3negate(uv), n), 1.0);
    t_vec3 r_out_perp =  vec3multscalar(vec3add(uv, vec3multscalar(n, cos_theta)), etai_over_etat);
    t_vec3 r_out_parallel = vec3multscalar(n, -sqrt(fabs(1.0 - length_squared(r_out_perp))));
    return vec3add(r_out_perp, r_out_parallel);
}

/*
 * Schlick's approximation for reflectance
 */
inline double reflectance(double cosine, double refraction_index) {
	// Use Schlick's approximation for reflectance.
	double r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1 - cosine),5);
}

#endif