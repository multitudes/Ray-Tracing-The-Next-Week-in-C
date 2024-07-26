/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotated.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:13:31 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 11:13:40 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATED_H
# define ROTATED_H

#include "hittable.h"
#include "material.h"


typedef struct s_rotated_y
{
	t_hittable  base;
	t_hittable 	*obj;
    double sin_theta;
    double cos_theta;
}				t_rotated_y;

t_rotated_y	rotated_y(t_hittable *obj, double angle);

bool		hit_rotated(const void* self, const t_ray *r, t_interval ray_t, t_hit_record *rec);


#endif
