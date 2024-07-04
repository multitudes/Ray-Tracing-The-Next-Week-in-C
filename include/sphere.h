/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:52:56 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/04 15:01:44 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include <stdbool.h>
#include "hittable.h"
#include "material.h"

typedef struct	s_sphere
{
	t_hittable  base;
	t_point3	center;
	t_point3	center1;
	double		radius;
	t_material	*mat;
	bool		ismoving;
	t_vec3		center_vec;
}				t_sphere;

/*
 * a sort of initializer for a sphere
 */
t_sphere 	sphere(t_point3 center, double radius, t_material *mat);
t_sphere 	movingsphere(t_point3 center1, t_point3 center2, double radius, t_material *mat);

/* if the ray hits the sphere, return the t value */
bool		hit_sphere(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec);
void 		set_face_normal(t_hit_record *rec, const t_ray *r, const t_vec3 outward_normal);

t_point3 	sphere_center(t_sphere s, double time);
void		get_sphere_uv(t_vec3 normal, double* u, double* v);

#endif