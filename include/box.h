/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:38:14 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 10:17:03 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOX_H
# define BOX_H

#include "vec3.h"
#include "ray.h"
#include "quad.h"
#include "material.h"
#include "hittable_list.h"

typedef struct	s_box {
	t_hittable  base;
    t_quad 		q1;
    t_quad 		q2;
    t_quad 		q3;
    t_quad 		q4;
    t_quad 		q5;
    t_quad 		q6;
}				t_box;


t_box box(t_point3 a, t_point3 b, t_material *mat);
void create_box(t_box *box, t_point3 a, t_point3 b, t_material *mat);
bool hit_box(const void* self, const t_ray *r, t_interval ray_t,  t_hit_record *rec);

#endif