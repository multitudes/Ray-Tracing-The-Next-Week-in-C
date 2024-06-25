/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/25 17:10:21 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtweekend.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "utils.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "material.h"
#include "hittable_list.h"
#include "interval.h"
#include <float.h>
#include <camera.h>


// int main(int argc, char **argv)
// {
// (void)argc;
// 	(void)argv;


// 	// world

// 	// double R = cos(M_PI / 4);
	
// 	// t_lambertian lambertian_material_left;
// 	// t_lambertian lambertian_material_right;

// 	// lambertian_init(&lambertian_material_left, color(0, 0, 1));
// 	// lambertian_init(&lambertian_material_right, color(1, 0, 0));

// 	// t_sphere s1 = sphere(point3(-R, 0, -1), R, (t_material*)&lambertian_material_left);
// 	// t_sphere s2 = sphere(point3(R, 0, -1), R, (t_material*)&lambertian_material_right);

// 	// t_hittable *list[2];
	
// 	// list[0] = (t_hittable*)(&s1);
// 	// list[1] = (t_hittable*)(&s2);
// 	// const t_hittablelist world = hittablelist(list, 2);
	
// 	t_lambertian lambertian_material_ground;
// 	t_lambertian lambertian_material_center;
// 	// t_metal metal_material_left;
// 	t_dielectric dielectric_material_left;
// 	t_dielectric dielectric_material_bubble;
// 	t_metal metal_material_right;

//    	lambertian_init(&lambertian_material_ground, color(0.8, 0.8, 0.0));
// 	lambertian_init(&lambertian_material_center, color(0.1, 0.2, 0.5));
//     // metal_init(&metal_material_left, color(0.8, 0.8, 0.8), 0.3);
// 	dielectric_init(&dielectric_material_left, 1.50);
// 	dielectric_init(&dielectric_material_bubble, 1.00 / 1.50);
// 	metal_init(&metal_material_right, color(0.8, 0.6, 0.2), 1.0);

// 	// Assuming t_lambertian and t_metal have a t_material as their first member,
// 	// you can safely cast their addresses to t_material*.
// 	t_sphere s1 = sphere(point3(0.0, -100.5, -1.0), 100.0, (t_material*)&lambertian_material_ground);
// 	t_sphere s2 = sphere(point3(0.0, 0.0, -1.2), 0.5, (t_material*)&lambertian_material_center);
// 	// t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_left);
	
// 	t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&dielectric_material_left);
// 	t_sphere s4 = sphere(point3(-1.0, 0.0, -1.0), 0.4, (t_material*)&dielectric_material_bubble);
// 	t_sphere s5 = sphere(point3(1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_right);

// 	t_hittable *list[5];

// 	list[0] = (t_hittable*)(&s1);
// 	list[1] = (t_hittable*)(&s2);
// 	list[2] = (t_hittable*)(&s3);
// 	list[3] = (t_hittable*)(&s4);
// 	list[4] = (t_hittable*)(&s5);
// 	const t_hittablelist world = hittablelist(list, 5);
	
// 	// init camera

//     t_camera c = camera();

// 	printf("camera init done ================ ");
// 	// render
// 	render(c, world);
// 	// params.mlx = mlx_init(WIDTH, HEIGHT, "in a weekend!", true);
// 	// params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);

// 	// if (mlx_image_to_window(params.mlx, params.img, 30, 30) == -1)
// 	// {
// 	// 	write(2, "mlx_image_to_window failed\n", 27);
// 	// 	return (1);
// 	// }

// 	// mlx_loop_hook(params.mlx, draw, &params);

// 	// mlx_loop(params.mlx);


// }


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	t_lambertian ground;
   	lambertian_init(&ground, color(0.5, 0.5, 0.5));
	t_sphere s1 = sphere(point3(0.0, -1000, 0), 1000.0, (t_material*)&ground);
	
	t_hittable *list[500];

	list[0] = (t_hittable*)(&s1);
	int i = 1;

	// to avoid mallocs on the stack which is slower also and can lead to difficulties in 
	// freeing the memory, we use a list of pointers to hittables
	t_lambertian sphere_materials_lambertian[22*22];
	t_metal sphere_materials_metal[22*22];
	t_dielectric sphere_materials_dielectric[22*22];
	t_sphere spheres[22*22+4];

	for (int a = -11; a < 11; a++) 
	{
        for (int b = -11; b < 11; b++) 
		{
            double choose_mat = random_d();
            t_point3 center = point3((double)a + 0.9 * random_d(), 0.2, (double)b + 0.9*random_d());
			t_point3 center2 = vec3add(center, vec3(0, random_double(0,.5), 0));
            if (length(vec3substr(center, point3(4, 0.2, 0))) > 0.9) 
			{
				if (choose_mat < 0.8) 
				{
					// diffuse
					t_color albedo = vec3cross(color_random(), color_random());
					lambertian_init(&sphere_materials_lambertian[i], albedo);
					spheres[i] = movingsphere(center, center2, 0.2, (t_material*)&sphere_materials_lambertian[i]); 
					list[i] = (t_hittable*)&spheres[i];
				} 
				else if (choose_mat < 0.95) 
				{
					// metal
					t_color albedo = color_random_min_max(0.5,1);
					double fuzz = random_double(0, 0.5);
					metal_init(&sphere_materials_metal[i], albedo, fuzz);
					spheres[i] = sphere(center, 0.2, (t_material*)&sphere_materials_metal[i]);
					list[i] = (t_hittable*)&spheres[i];
				} 
				else 
				{
					// glass
					dielectric_init(&sphere_materials_dielectric[i], 1.5);
					spheres[i] = sphere(center, 0.2, (t_material*)&sphere_materials_dielectric[i]);
					list[i] = (t_hittable*)&spheres[i];
				}
            }
			else
				list[i] = NULL;
			i++;
        }
    }


	t_dielectric material1;
	dielectric_init(&material1, 1.50);

	t_lambertian material2;
	lambertian_init(&material2, color(0.4, 0.2, 0.1));

	t_metal material3;
	metal_init(&material3, color(0.7, 0.6, 0.5), 0.0);

	t_sphere s2 = sphere(point3(0, 1, 0), 1.0, (t_material*)&material1);
	t_sphere s3 = sphere(point3(-4, 1, 0), 1.0, (t_material*)&material2);
	t_sphere s4 = sphere(point3(4, 1, 0), 1.0, (t_material*)&material3);

	list[i++] = (t_hittable*)(&s2);
	list[i++] = (t_hittable*)(&s3);
	list[i] = (t_hittable*)(&s4);
	
	const t_hittablelist world = hittablelist(list, i + 1);
	printf("world init done ================ ");
	
	// init camera
    t_camera c = camera();
	printf("camera init done ================ ");

	// render
	render(c, world);
	return (0);
}
