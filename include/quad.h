/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:07:01 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/05 10:44:54 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUAD_H
# define QUAD_H

#include "vec3.h"
#include "interval.h"
#include "material.h"
#include "ray.h"
#include "hittable.h"

/*
 * A quad is a 4-pointed polygon in 3D space
 * 
 * q: the center of the quad
 * u: the first vector of the quad
 * v: the second vector of the quad
 * mat: the material of the quad
 * 
 * The miniRT quad is defined by the center point q 
 * and a normalized vector and a color. This below is from the book
 * but can be adapted to the miniRT quad.
 */
typedef struct s_quad
{
	t_hittable  base;
	t_point3	q;
	t_vec3		u;
	t_vec3		v;
	t_material	*mat;
	double		d;
	t_vec3		normal;
	t_vec3		w;
}				t_quad;

t_quad	quad(t_point3 q, t_vec3 u, t_vec3 v, t_material *mat);
bool	hit_quad(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec);
bool	is_interior(double a, double b, t_hit_record *rec);

#endif