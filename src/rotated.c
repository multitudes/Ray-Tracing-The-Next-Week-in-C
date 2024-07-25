/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotated.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:13:20 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/25 13:10:44 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotated.h"

t_rotated_y	rotated_y(t_hittable *obj, double angle)
{
	t_rotated_y rotated;

	rotated.base.hit = hit_rotated;
	rotated.obj = obj;
	rotated.sin_theta = sin(angle);
	rotated.cos_theta = cos(angle);
	return (rotated);
}

bool	hit_rotated(const void *self, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	t_rotated_y *rot_y;
	t_point3 origin;
	t_vec3 direction;


	rot_y = (t_rotated_y *)self;
	origin = r->orig;
	direction = r->dir;

	// Rotate the ray's origin and direction. this will be similar for the other rotations
	// on the other axes	
	origin.x = rot_y->cos_theta * r->orig.x - rot_y->sin_theta * r->orig.z;
	origin.z = rot_y->sin_theta * r->orig.x + rot_y->cos_theta * r->orig.z;

	direction.x = rot_y->cos_theta * r->dir.x - rot_y->sin_theta * r->dir.z;
	direction.z = rot_y->sin_theta * r->dir.x + rot_y->cos_theta * r->dir.z;

	t_ray rotated_r = ray(origin, direction, r->tm);

// Determine whether an intersection exists in object space (and if so, where)
	if (!rot_y->obj->hit(rot_y->obj, &rotated_r, ray_t, rec))
		return (false);

	// Change the intersection point from object space to world space
	rec->p.x = rot_y->cos_theta * rec->p.x + rot_y->sin_theta * rec->p.z;
	rec->p.z = -rot_y->sin_theta * rec->p.x + rot_y->cos_theta * rec->p.z;

	// Change the normal from object space to world space
	rec->normal.x = rot_y->cos_theta * rec->normal.x + rot_y->sin_theta * rec->normal.z;
	rec->normal.z = -rot_y->sin_theta * rec->normal.x + rot_y->cos_theta * rec->normal.z;
	


	return (true);
}