/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:43:42 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/25 16:16:05 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "hittable.h"
#include "rtweekend.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"


// Example of creating a lambertian material
// t_lambertian lambertian_material;

// Function to initialize a Lambertian material
void lambertian_init(t_lambertian *lambertian_material, t_color albedo) 
{
    lambertian_material->base.scatter = lambertian_scatter; // Assign the scatter function
    lambertian_material->albedo = albedo; // Set the albedo
}

void metal_init(t_metal *metal, t_color albedo, double fuzz)
{
	metal->base.scatter = metal_scatter;
	metal->albedo = albedo;
	metal->fuzz = fuzz < 1 ? fuzz : 1;
}


void dielectric_init(t_dielectric *dielectric, double refraction_index)
{
	dielectric->base.scatter = dielectric_scatter;
	dielectric->refraction_index = refraction_index;
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
    *attenuation = lamb->albedo;
        return true;
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
