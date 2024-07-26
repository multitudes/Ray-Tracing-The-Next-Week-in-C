/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translated.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:46:22 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 10:56:46 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATED_H
# define TRANSLATED_H

#include "hittable.h"

typedef struct 	s_translated
{
	t_hittable  base;
	t_hittable 	*obj;
	t_vec3 		offset;
} 				t_translated;

t_translated	translated(t_hittable *obj, t_vec3 offset);
bool			hit_translated(const void* self, const t_ray *r, t_interval ray_t, t_hit_record *rec);

#endif

