/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:28:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/26 10:54:22 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include <limits.h>
#include "rtweekend.h"
#include <stdio.h>

/*
 * camera
 * 
 * aspect_ratio: width / height
 * image_width: width of the image in pixels
 * image_height: height of the image in pixels
 * center: the point in 3D space from which all scene rays will originate
 * pixel00_loc: the location of the upper left pixel
 * pixel_delta_u: the offset to the first pixel center
 * pixel_delta_v: the offset to the pixel center
 */
t_camera camera()
{
	t_camera c;
	
	// public members
	c.aspect_ratio = (double)16.0 / 16.0; 	// Ratio of image width over height
	c.image_width = 200; 					// Rendered image width in pixel count
    c.samples_per_pixel = 200;				// Count of random samples for each pixel
	c.max_depth = 50;						// Maximum number of ray bounces into scene
	c.background = color(0,0,0);			// Scene background color

	c.vfov = 40; 							// Vertical view angle (field of view)
    c.lookfrom = point3(278, 278, -800);			// Point camera is looking from
    c.lookat = point3(278, 278, 0);				// Point camera is looking at
    c.vup = vec3(0,1,0);					// Camera-relative "up" direction
	
    c.defocus_angle = 0; 					// Variation angle of rays through each pixel
    c.focus_dist = 10;						// Distance from camera lookfrom point to plane of perfect focus


	// initialize the camera from public members
	c.image_height = (double)c.image_width / c.aspect_ratio;
	c.image_height = (c.image_height < 1) ? 1 : c.image_height;
  	
	c.pixel_samples_scale = 1.0 / c.samples_per_pixel;

	c.center = c.lookfrom;
	
	double theta = degrees_to_radians(c.vfov);
    double h = tan(theta/2);
    double viewport_height = 2 * h * c.focus_dist;
	double viewport_width = viewport_height * ((double)c.image_width/c.image_height);
	
	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    c.w = unit_vector(vec3substr(c.lookfrom, c.lookat));
    c.u = unit_vector(cross(c.vup, c.w));
    c.v = cross(c.w, c.u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewport_u = vec3multscalar(c.u, viewport_width);    // Vector across viewport horizontal edge
	t_vec3 viewport_v = vec3multscalar(vec3negate(c.v), viewport_height);  // Vector down viewport vertical edge

	 // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    c.pixel_delta_u  = vec3divscalar(viewport_u, c.image_width);
    c.pixel_delta_v = vec3divscalar(viewport_v, c.image_height);

    t_point3 viewport_upper_left = vec3substr(c.center, vec3multscalar(c.w, c.focus_dist));
	viewport_upper_left = vec3substr(viewport_upper_left, vec3divscalar(viewport_u, 2));
	viewport_upper_left = vec3substr(viewport_upper_left, vec3divscalar(viewport_v, 2));
	
	t_vec3 small_translation = vec3add(vec3multscalar(c.pixel_delta_u, 0.5), vec3multscalar(c.pixel_delta_v, 0.5));

    c.pixel00_loc = vec3add(viewport_upper_left, small_translation);

	// Calculate the camera defocus disk basis vectors.
	double defocus_radius = c.focus_dist * tan(degrees_to_radians(c.defocus_angle / 2));
	c.defocus_disk_u = vec3multscalar(c.u, defocus_radius);
	c.defocus_disk_v = vec3multscalar(c.v, defocus_radius);

	printf("pixel00_loc: ");
	print_vec3(&c.pixel00_loc);
	printf("camera initialized\n");
	return c;
}


void	render(t_camera c, const t_hittablelist world)
{
	// render
	// for the book course we create a ppm image
	// create_ppm_image("test.ppm", WIDTH, HEIGHT);
	printf("Rendering image...\n");
	FILE *file;
	char filepath[PATH_MAX];

	// render
	sprintf(filepath, "assets/%s", "test2.ppm");
	file = fopen(filepath, "w");
	fprintf(file, "P3\n%d %d\n255\n", c.image_width, c.image_height);

	for (int j = 0; j < c.image_height; j++) 
	{
		// write to std err
		// fprintf(stderr, "\rScanlines remaining: %d\n", image_height - j);
		for (int i = 0; i < c.image_width; i++)
		{	
			t_color pixel_color = color(0,0,0);
            for (int sample = 0; sample < c.samples_per_pixel; sample++) {
                    t_ray r = get_ray(&c, i, j);
					t_color partial = ray_color(c, &r, c.max_depth, &world);
                    pixel_color = vec3add(pixel_color, partial);
                }
			write_color(file, vec3multscalar(pixel_color, c.pixel_samples_scale));
		}
		printf("\rScanlines remaining: %d\n", c.image_height - j - 1);
	}
	printf("\nDone.\n");
	fclose(file);
}


t_color	ray_color(t_camera cam, t_ray *r, const int depth, const t_hittablelist *world)
{
	t_hit_record rec;
	
	if (depth <= 0)
        return color(0,0,0);
	
	if (!world->hit(world, r, interval(0.001, INFINITY), &rec))
		return cam.background; // it should be the cam beckground but since this is c and raycolor is not a member func i have no access to cam
	
	t_ray scattered;
	t_color attenuation;
	t_color color_from_emission = rec.mat->emit(rec.mat, rec.u, rec.v, rec.p);
	
	if (!rec.mat->scatter(rec.mat, r, &rec, &attenuation, &scattered))
		return color_from_emission;
		
	t_color color_from_scatter = vec3mult(attenuation, ray_color(cam, &scattered, depth-1, world));
	
	return vec3add(color_from_emission, color_from_scatter);
	
	// t_vec3 unit_direction = unit_vector(r->dir);
	// double a = 0.5 * (unit_direction.y + 1.0);
	// t_color start = vec3multscalar(color(1.0, 1.0, 1.0), 1.0 - a);
	// t_color end = vec3multscalar(color(0.5, 0.7, 1.0), a);
	// return vec3add(start, end);
}

/*
 * get_ray
 * 
 * c: camera
 * i: x coordinate
 * j: y coordinate
 * 
 * returns: a camera ray originating from the defocus disk and directed at a randomly 
 * sampled point around the pixel location i, j.
 */
t_ray get_ray(t_camera *c, int i, int j)  
{
	t_vec3	offset = sample_square();
	t_vec3	pixel_sample = vec3add(c->pixel00_loc, 
						vec3add(vec3multscalar(c->pixel_delta_u, (i + offset.x)),
						vec3multscalar(c->pixel_delta_v, (j + offset.y))));

	t_vec3 ray_origin = (c->defocus_angle <= 0) ? c->center : defocus_disk_sample(c);
	t_vec3 ray_direction = vec3substr(pixel_sample, ray_origin);
	double ray_time = random_double(0, 1);
	return ray(ray_origin, ray_direction, ray_time);
}

/*
 * sample_square
 * 
 * Returns a random point in the unit square.
 */
t_vec3	sample_square()
{
	return vec3(random_d() - 0.5, random_d() - 0.5, 0);
}

/*
 * defocus_disk_sample
 * 
 * Returns a random point in the camera defocus disk.
 */
t_point3 defocus_disk_sample(t_camera *c)
{
	t_point3 p = random_in_unit_disk();
	return vec3add(vec3add(c->center, vec3multscalar(c->defocus_disk_u, p.x)), vec3multscalar(c->defocus_disk_v, p.y));
}


