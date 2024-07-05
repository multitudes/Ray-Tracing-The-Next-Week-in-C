/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:13:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/05 11:20:40 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quad.h"
#include "hittable.h"
#include <stdio.h>

t_quad quad(t_point3 q, t_vec3 u, t_vec3 v, t_material *mat)
{
	t_quad qd;

	qd.base.hit = hit_quad;
	qd.q = q;
	qd.u = u;
	qd.v = v;
	qd.mat = mat;
	t_vec3 n = cross(u, v);
    qd.normal = unit_vector(n);
    qd.d = dot(qd.normal, q);
	qd.w = vec3divscalar(n, dot(n, n));
	
	return (qd);
}

bool hit_quad(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec)
{
	// printf("hit_quad ----------------------********\n");
	const t_quad *qd = (t_quad *)self;
	double denom = dot(qd->normal, r->dir);
	// no hit if ray is parallel to the quad
	if (fabs(denom) < 1e-8)
		return false;

	// Return false if the hit point parameter t is outside the ray interval.
	double t = (qd->d - dot(qd->normal, r->orig)) / denom;
	if (!contains(&ray_t, t))
		return false;
	
	// Determine the hit point lies within the planar shape using its plane coordinates.
	// t_point3	point_at(const t_ray *ray, double t)
	t_point3 intersection = point_at(r, t);
	t_vec3 planar_hitpt_vector = vec3substr(intersection, qd->q);
	double alpha = dot(qd->w, cross(planar_hitpt_vector, qd->v));
	double beta = dot(qd->w, cross(qd->u, planar_hitpt_vector));

	if (!is_interior(alpha, beta, rec))
		return false;

	// Ray hits the 2D shape; set the rest of the hit record and return true.
	rec->t = t;
	rec->p = intersection;
	rec->mat = qd->mat;
	set_face_normal(rec, r, qd->normal);

	return true;
}

bool is_interior(double a, double b, t_hit_record *rec) 
{
	t_interval unit_interval = interval(0, 1);
	// Given the hit point in plane coordinates, return false if it is outside the
	// primitive, otherwise set the hit record UV coordinates and return true.

	if (!contains(&unit_interval, a) || !contains(&unit_interval, b) )
		return false;
	rec->u = a;
	rec->v = b;
	return true;
}