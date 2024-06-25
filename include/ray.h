/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:44:14 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 11:41:17 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "vec3.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}				t_ray;

t_ray			ray(const t_point3 origin, const t_vec3 direction);
const t_point3	*ray_origin(const t_ray *ray);
const t_vec3	*ray_direction(const t_ray *ray);
t_point3		point_at(const t_ray *ray, double t);

#endif