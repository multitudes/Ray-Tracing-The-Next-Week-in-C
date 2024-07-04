/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:52:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/04 15:01:34 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include "sphere.h"
#include "ray.h"
#include "vec3.h"

/*
 * a sort of initializer for a sphere
 */
t_sphere sphere(t_point3 center, double radius, t_material *mat)
{
	t_sphere s;

	s.base.hit = hit_sphere;
	s.center = center;
	s.center1 = center;
	s.radius = fmax(0,radius);
	s.mat = mat;
	s.ismoving = false;
	s.center_vec = vec3(0,0,0);
	return s;
}

t_sphere movingsphere(t_point3 center1, t_point3 center2, double radius, t_material *mat)
{
	t_sphere s;

	s.base.hit = hit_sphere;
	s.center = center1;
	s.center1 = center2;
	s.radius = fmax(0,radius);
	s.center_vec = vec3substr(center2, center1);
	s.mat = mat;
	s.ismoving = true;
	return s;
}
/*
 * The formula for a sphere is derived from the equation of a sphere
 * (p - c) * (p - c) = r * r
 * The func takes a first param of type void* to be able to be used in 
 * the hittable list (sort of polymorphic behaviour)
 * in the body oc is the vector from origin of the ray 
 * to the center of the sphere
 * At first the formula was derived from the quadratic formula
 * double b = -2.0 * dot(&(r->dir), &oc);
 * double c = dot(&oc, &oc) - s->radius * s->radius;
 * but this has been refactored using double h 
 */
bool hit_sphere(const void *self, const t_ray *r, t_interval ray_t, t_hit_record *rec) 
{
	const t_sphere *s = (t_sphere *)self;
	t_point3 center = s->center;
	if (s->ismoving)
		center = sphere_center(*s, r->tm);
    t_vec3 oc = vec3substr(center, r->orig);
    double a = length_squared(r->dir); 
    double h = dot(r->dir, oc);
	double c = length_squared(oc) - s->radius * s->radius;
    double discriminant = h*h - a*c;
	rec->mat = s->mat;
	if (discriminant < 0)
		return (false);
	double sqrtd = sqrt(discriminant);
	double root = (h - sqrtd) / a;
	if (!surrounds(&ray_t, root))
	{
		root = (h + sqrtd) / a;
		if (!surrounds(&ray_t, root))
			return false;
    }
	rec->t = root;
	rec->p = point_at(r, rec->t);
	t_vec3 inters_minus_center = vec3substr(rec->p, center);
	rec->normal = vec3divscalar(inters_minus_center, s->radius);
	set_face_normal(rec, r, rec->normal);
	get_sphere_uv(rec->normal, &rec->u, &rec->v);
	rec->mat = s->mat;

	return (true);
}


void set_face_normal(t_hit_record *rec, const t_ray *r, const t_vec3 outward_normal)
{
	rec->front_face = dot(r->dir, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : vec3negate(outward_normal);
}

/*
 * sphere_center
 * 
 * time: time
 * 
 * returns: the center of the sphere at a given time
 * Linearly interpolate from center1 to center2 according to time, where t=0 yields
 * center1, and t=1 yields center2.
 */
t_point3 sphere_center(t_sphere s, double time) 
{
    return vec3add(s.center1, vec3multscalar(s.center_vec, time));
}

/*
 * get_sphere_uv
 * 
 * p: point / the outward normal on the sphere
 * u: u
 * v: v
 * 
 * returns: the uv coordinates of a sphere
 */
void	get_sphere_uv(t_vec3 normal, double* u, double* v)
{
    double theta;
    double phi;

	theta = acos(-normal.y);
	phi = atan2(-normal.z, normal.x) + M_PI;
    *u = phi / (2 * M_PI);
    *v = theta / M_PI;
}