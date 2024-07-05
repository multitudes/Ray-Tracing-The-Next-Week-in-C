/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:13:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/05 09:45:07 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quad.h"
#include "hittable.h"

t_quad quad(t_point3 q, t_vec3 u, t_vec3 v, t_material *mat)
{
	t_quad qd;
	
	qd.q = q;
	qd.u = u;
	qd.v = v;
	qd.mat = mat;
	t_vec3 n = cross(u, v);
    qd.normal = unit_vector(n);
    qd.d = dot(qd.normal, q);
	return (qd);
}

bool hit_quad(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec)
{
	t_quad *qd = (t_quad *)self;
	double denom = dot(qd->normal, r->dir);
	// no hit if ray is parallel to the quad
	if (fabs(denom) < 1e-8)
		return false;
	double t = (qd->d - dot(q->normal, r->orig)) / denom;
	if (!contains(&ray_t, t))
		return false;
	// t_point3	point_at(const t_ray *ray, double t)
	t_point3 intersection = point_at(r, t);
	rec->t = t;
	rec->p = intersection;
	rec->mat = qd->mat;
	set_face_normal(rec, r, rec->normal);
	rec->normal = qd->normal;
	t_vec3 p = vec3substr(intersection, qd->q);
	return true;
}