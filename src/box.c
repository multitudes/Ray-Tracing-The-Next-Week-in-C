/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:40:26 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/25 11:41:31 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box.h"
#include "vec3.h"
#include "quad.h"
#include "material.h"

t_box box(t_quad q1, t_quad q2, t_quad q3, t_quad q4, t_quad q5, t_quad q6)
{
	t_box box;

	box.q1 = q1;
	box.q2 = q2;
	box.q3 = q3;
	box.q4 = q4;
	box.q5 = q5;
	box.q6 = q6;
	return (box);
}


void create_box(t_box *box, t_point3 a, t_point3 b, t_material *mat)
{
  	t_point3 min = point3(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
    t_point3 max = point3(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));

    t_vec3 dx = vec3(max.x - min.x, 0, 0);
    t_vec3 dy = vec3(0, max.y - min.y, 0);
    t_vec3 dz = vec3(0, 0, max.z - min.z);

    box->q1 = quad(point3(min.x, min.y, max.z),  dx,  dy, mat); // front
    box->q2 = quad(point3(max.x, min.y, max.z), vec3negate(dz),  dy, mat); // right
    box->q3 = quad(point3(max.x, min.y, min.z), vec3negate(dx),  dy, mat); // back
    box->q4 = quad(point3(min.x, min.y, min.z),  dz,  dy, mat); // left
    box->q5 = quad(point3(min.x, max.y, max.z),  dx, vec3negate(dz), mat); // top
    box->q6 = quad(point3(min.x, min.y, min.z),  dx,  dz, mat); // bottom
}
