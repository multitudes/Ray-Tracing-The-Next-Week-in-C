/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:59:14 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 10:13:15 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
#define HITTABLE_H

#include "material.h"
#include "ray.h"
#include <stdbool.h>
#include "interval.h"

typedef struct s_material t_material;

typedef struct 	s_hit_record {
	t_material 	*mat;
    t_point3 	p;
    t_vec3 		normal;
    double 		t;
	bool 		front_face;
	double		u;
	double		v;
} 				t_hit_record;


/* translated from cpp - remains to see if I will incorporate this into every object*/
typedef struct 	s_hittable{
	bool (*hit)(const void *self, const t_ray* r, t_interval ray_t, t_hit_record* rec);
} 				t_hittable;

bool hit(const void *self, const t_ray* r, t_interval ray_t, t_hit_record* rec);


#endif


