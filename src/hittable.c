/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:49:28 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/25 11:40:39 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include <stdbool.h>
#include "interval.h"

bool hit(const void *self, const t_ray* r, t_interval ray_t, t_hit_record* rec)
{
	 	t_hittablelist *hittablelist = (t_hittablelist *)self;
		t_hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = ray_t.max;
		int i = 0;

		if (!self)
			return (false);
		while (i < hittablelist->size)
		{
			if (hittablelist->list[i] && hittablelist->list[i]->hit(hittablelist->list[i], r, interval(ray_t.min, closest_so_far), &temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
			i++;
		} 
	return (hit_anything);
}

t_hittablelist hittablelist(t_hittable **list, int size)
{
	t_hittablelist hittablelist;

	hittablelist.list = list;
	hittablelist.size = size;
	hittablelist.hit = hit;
	return (hittablelist);
}