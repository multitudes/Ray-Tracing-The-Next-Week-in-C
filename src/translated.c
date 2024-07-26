/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translated.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:57 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 11:00:17 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translated.h"

t_translated translated(t_hittable *obj, t_vec3 offset)
{
	t_translated translated;

	translated.base.hit = hit_translated;
	translated.obj = obj;
	translated.offset = offset;

	return (translated);
}

bool		hit_translated(const void* self, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	t_translated *translated;
	
    t_ray offset_r;
	
	translated = (t_translated *)self;
	 // Move the ray backwards by the offset
	offset_r = ray(vec3substr(r->orig, translated->offset), r->dir, r->tm);

    // Determine whether an intersection exists along the offset ray (and if so, where)
    if (!translated->obj->hit(translated->obj, &offset_r, ray_t, rec))
		return false;

    // Move the intersection point forwards by the offset
    rec->p = vec3add(rec->p, translated->offset);

	return true;
}
