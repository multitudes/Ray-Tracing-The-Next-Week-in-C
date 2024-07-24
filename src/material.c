/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:43:42 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/24 17:07:04 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "hittable.h"
#include "rtweekend.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"

void lambertian_init_tex(t_lambertian *lambertian_material, t_texture *tex) 
{
    lambertian_material->base.scatter = lambertian_scatter; // Assign the scatter function
	lambertian_material->base.emit = emitzero;
    lambertian_material->albedo = color(0,0,0); // Set the albedo to null
	lambertian_material->texture = tex;
}


void metal_init(t_metal *metal, t_color albedo, double fuzz)
{
	metal->base.scatter = metal_scatter;
	metal->base.emit = emitzero;
	metal->albedo = albedo;
	metal->fuzz = fuzz < 1 ? fuzz : 1;
}


void dielectric_init(t_dielectric *dielectric, double refraction_index)
{
	dielectric->base.scatter = dielectric_scatter;
	dielectric->base.emit = emitzero;
	dielectric->refraction_index = refraction_index;
}

void diffuse_light_init(t_diffuse_light *light, t_texture *texture)
{
	light->base.scatter = noscatter;
	light->base.emit = emitlight;
	light->texture = texture;
}

bool noscatter(void *self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	(void)self;
	(void)r_in;
	(void)rec;
	(void)attenuation;
	(void)scattered;
	return false;
}
/*
 * scatter function for a lambertian material
 */
bool lambertian_scatter(void* self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered) 
{
	(void)r_in;
	t_lambertian *lamb = (t_lambertian *)self;
	t_vec3 scatter_direction = vec3add(rec->normal, random_unit_vector());
	if (near_zero(scatter_direction))
		scatter_direction = rec->normal;
    *scattered = ray(rec->p, scatter_direction, r_in->tm);
    if (lamb->texture && lamb->texture->value) {
         *attenuation = lamb->texture->value(lamb->texture, rec->u, rec->v, &rec->p);
   } else {
        // Fallback or error handling if texture or value function is not set
        *attenuation = lamb->albedo; // Example fallback color
    }

    return true; 
}

/*
 * scatter function for a metal material
 */
bool metal_scatter(void *self, const t_ray* r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_metal *metal = (t_metal *)self;
	t_vec3 reflected = reflect(r_in->dir, rec->normal);
	reflected = unit_vector(vec3add(reflected, vec3multscalar(random_unit_vector(), metal->fuzz)));
	*scattered = ray(rec->p, reflected, r_in->tm);
	*attenuation = metal->albedo;
	return (dot(scattered->dir, rec->normal) > 0);
}

/*
 * scatter function for a dielectric material
 */
bool dielectric_scatter(void *self, const t_ray* r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered)
{
	t_dielectric *dielectric = (t_dielectric *)self;
	*attenuation = color(1.0, 1.0, 1.0);
	double ri = rec->front_face ? (1.0 / dielectric->refraction_index) : dielectric->refraction_index;
	t_vec3 unit_direction = unit_vector(r_in->dir);
	
	double cos_theta = fmin(dot(vec3negate(unit_direction), rec->normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = ri * sin_theta > 1.0;
	t_vec3 direction;

	if (cannot_refract || reflectance(cos_theta, ri) > random_d())
		direction = reflect(unit_direction, rec->normal);
	else
		direction = refract(unit_direction, rec->normal, ri);

	*scattered = ray(rec->p, direction, r_in->tm);

	return true;
}

t_color		emitlight(void *self, double u, double v, t_point3 p)
{
	t_diffuse_light *light = (t_diffuse_light *)self;
	return light->texture->value(light->texture ,u, v, &p);
}

t_color		emitzero(void *self, double u, double v, t_point3 p)
{
	(void)self;
	(void)u;
	(void)v;
	(void)p;
	return color(0, 0, 0);
}