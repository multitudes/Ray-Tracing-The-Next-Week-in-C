/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:38:14 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/25 11:41:51 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOX_H
# define BOX_H

#include "vec3.h"
#include "ray.h"
#include "quad.h"
#include "material.h"


typedef struct s_box {
    t_quad q1;
    t_quad q2;
    t_quad q3;
    t_quad q4;
    t_quad q5;
    t_quad q6;
} t_box;


t_box box(t_quad q1, t_quad q2, t_quad q3, t_quad q4, t_quad q5, t_quad q6);
void create_box(t_box *box, t_point3 a, t_point3 b, t_material *mat);

#endif