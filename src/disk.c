/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:13:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/05 13:11:42 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"
#include "hittable.h"
#include <stdio.h>

t_disk disk(t_point3 q, t_vec3 u, t_vec3 v, t_material *mat)
{
	t_disk disk;

	disk.base.hit = hit_disk;
	disk.q = q;
	disk.u = u;
	disk.v = v;
	disk.mat = mat;
	t_vec3 n = cross(u, v);
    disk.normal = unit_vector(n);
    disk.d = dot(disk.normal, q);
	disk.w = vec3divscalar(n, dot(n, n));
	
	return (disk);
}

bool hit_disk(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec)
{
	// printf("hit_quad ----------------------********\n");
	const t_disk *disk = (t_disk *)self;
	double denom = dot(disk->normal, r->dir);
	// no hit if ray is parallel to the quad
	if (fabs(denom) < 1e-8)
		return false;

	// Return false if the hit point parameter t is outside the ray interval.
	double t = (disk->d - dot(disk->normal, r->orig)) / denom;
	if (!contains(&ray_t, t))
		return false;
	
	// Determine the hit point lies within the planar shape using its plane coordinates.
	// t_point3	point_at(const t_ray *ray, double t)
	t_point3 intersection = point_at(r, t);
	t_vec3 planar_hitpt_vector = vec3substr(intersection, disk->q);
	double alpha = dot(disk->w, cross(planar_hitpt_vector, disk->v));
	double beta = dot(disk->w, cross(disk->u, planar_hitpt_vector));

	if (!is_interior_disk(alpha, beta, rec, disk->u, disk->v))
		return false;

	// Ray hits the 2D shape; set the rest of the hit record and return true.
	rec->t = t;
	rec->p = intersection;
	rec->mat = disk->mat;
	set_face_normal(rec, r, disk->normal);

	return true;
}

bool is_interior_disk(double a, double b, t_hit_record *rec, t_vec3 u, t_vec3 v) 
{
    // The center of the disk in plane coordinates is (0.5, 0.5)
    double u_squared = (a - 0.5) * (a - 0.5);
    double v_squared = (b - 0.5) * (b - 0.5);
    double uv = (a - 0.5) * (b - 0.5);

    // The radius of the disk is 0.5 in plane coordinates
    double radius_squared = 0.25;

    // The angle between the vectors u and v
    double cos_theta = dot(u, v) / (length(u) * length(v));

    // The distance from the point to the center of the disk in the plane coordinates of the parallelogram
    double distance_squared = u_squared + v_squared - 2 * uv * cos_theta;

    if (distance_squared > radius_squared)
        return false;

    rec->u = a;
    rec->v = b;
    return true;
}