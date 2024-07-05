/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:07:01 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/05 09:31:28 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUAD_H
# define QUAD_H

#include "vec3.h"
#include "material.h"

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
	t_point3	q;
	t_vec3		u;
	t_vec3		v;
	t_material	*mat;
	double		d;
	t_vec3		normal;
}				t_quad;



#endif