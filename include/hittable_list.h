/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 10:08:26 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"


typedef struct 	s_hittablelist {
	t_hittable 	**list;
	int 		size;
	bool 		(*hit)(const void* self, const t_ray* r, t_interval ray_t, t_hit_record* rec);
} 				t_hittablelist; 

t_hittablelist hittablelist(t_hittable **list, int size);

#endif
