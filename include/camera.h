/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/24 17:14:59 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"


typedef struct	t_camera 
{
	// considered "public" 
	double 		aspect_ratio;
	int 		image_width;
	int 		samples_per_pixel;
	int			max_depth;		   // Maximum number of ray bounces into scene
	double		vfov;			   // Field of view
	t_point3 	lookfrom;   		// Point camera is looking from
    t_point3 	lookat;  			// Point camera is looking at
    t_vec3   	vup;     			// Camera-relative "up" direction
	double 		defocus_angle;  // Variation angle of rays through each pixel
    double 		focus_dist;    // Distance from camera lookfrom point to plane of perfect focus
	t_color		background;		 // Scene background color
	
	// considered private
	int    		image_height;   // Rendered image height
    t_point3 	center;         // Camera center
    t_point3	pixel00_loc;    // Location of pixel 0, 0
    t_vec3		pixel_delta_u;  // Offset to pixel to the right
    t_vec3		pixel_delta_v;  // Offset to pixel below
	double		pixel_samples_scale;
	t_vec3   	u, v, w;              // Camera frame basis vectors
	t_vec3  	defocus_disk_u;       // Defocus disk horizontal radius
    t_vec3  	defocus_disk_v;       // Defocus disk vertical radius
} 				t_camera;

t_camera	camera();
void		render(t_camera cam, const t_hittablelist world);
t_color		ray_color(t_camera cam, t_ray *r, int max_deph, const t_hittablelist *world);
t_ray		get_ray(t_camera *c, int u, int v);
t_vec3		sample_square();
t_point3	defocus_disk_sample(t_camera *c);

#endif
