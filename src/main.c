/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/24 17:18:16 by lbrusa           ###   ########.fr       */
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
#include "texture.h"
#include "rtw_stb_image.h"
#include "quad.h"
#include "disk.h"

int main()
{
	t_solid_color left_red;
	t_solid_color back_green;
	t_solid_color right_blue;
	t_solid_color upper_orange;
	t_solid_color lower_teal;

	solid_color_init(&left_red, color(1.0, 0.2, 0.2));
	solid_color_init(&back_green, color(0.2, 1.0, 0.2));
	solid_color_init(&right_blue, color(0.2, 0.2, 1.0));
	solid_color_init(&upper_orange, color(1.0, 0.5, 0.2));
	solid_color_init(&lower_teal, color(0.2, 0.5, 1.0));


	t_lambertian left_red_lam;
	t_lambertian back_green_lam;
	t_lambertian right_blue_lam;
	t_lambertian upper_orange_lam;
	t_lambertian lower_teal_lam;
	
	lambertian_init_tex(&left_red_lam, (t_texture*)&left_red);
	lambertian_init_tex(&back_green_lam, (t_texture*)&back_green);
	lambertian_init_tex(&right_blue_lam, (t_texture*)&right_blue);
	lambertian_init_tex(&upper_orange_lam, (t_texture*)&upper_orange);
	lambertian_init_tex(&lower_teal_lam, (t_texture*)&lower_teal);

	t_disk q1 = disk(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), (t_material*)&left_red_lam);
	t_disk q2 = disk(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), (t_material*)&back_green_lam);
	t_disk q3 = disk(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), (t_material*)&right_blue_lam);
	t_disk q4 = disk(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), (t_material*)&upper_orange_lam);
	t_disk q5 = disk(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), (t_material*)&lower_teal_lam);

	t_hittable *list[5];

	list[0] = (t_hittable*)(&q1);
	list[1] = (t_hittable*)(&q2);
	list[2] = (t_hittable*)(&q3);
	list[3] = (t_hittable*)(&q4);
	list[4] = (t_hittable*)(&q5);
	
	const t_hittablelist world = hittablelist(list, 5);
	
	// init camera

    t_camera c = camera();
	c.background        = color(0.70, 0.80, 1.00);
	
	printf("camera init done ================ ");
	// render
	render(c, world);


	// world.add(make_shared<quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    // world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    // world.add(make_shared<quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    // world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    // world.add(make_shared<quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));


	return (0);
}


int main_earth()
{
	t_lambertian earth_surface;
	t_rtw_image img;
	init_rtw_image(&img,"rtw_image/earthmap.jpg");
	t_img_texture img_texture;
	img_texture_init(&img_texture, &img);
	lambertian_init_tex(&earth_surface, (t_texture*)&img_texture);
	t_sphere s1 = sphere(point3(0.0, 0, 0), 2.0, (t_material*)&earth_surface);
	t_hittable *list[1];
	list[0] = (t_hittable*)(&s1);
	const t_hittablelist world = hittablelist(list, 1);
		// init camera

    t_camera c = camera();

	printf("camera init done ================ ");
	// render
	render(c, world);
	return (0);
}

int main_two_spheres_checker()
{
	// auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
	t_lambertian lambertian_material;
	t_checker_texture checker_texture1;
	t_solid_color even1;
	t_solid_color odd1;
	solid_color_init(&even1, color(0.2, 0.3, 0.1));
	solid_color_init(&odd1, color(0.9, 0.9, 0.9));
	checker_texture_init(&checker_texture1, 0.32, &even1, &odd1);
	lambertian_init_tex(&lambertian_material, (t_texture*)&(checker_texture1));
	t_sphere s1 = sphere(point3(0.0, -10, 0), 10.0, (t_material*)&lambertian_material);
	t_sphere s2 = sphere(point3(0.0, 10, 0), 10, (t_material*)&lambertian_material);
	t_hittable *list[2];
	list[0] = (t_hittable*)(&s1);
	list[1] = (t_hittable*)(&s2);
	const t_hittablelist world = hittablelist(list, 2);
		// init camera

    t_camera c = camera();
 	c.background        = color(0.70, 0.80, 1.00);
	printf("camera init done ================ ");
	// render
	render(c, world);
	return (0);

}
int main_checker()
{
	t_lambertian lambertian_material_ground;
	t_checker_texture checker_texture;
	t_solid_color even;
	t_solid_color odd;
	solid_color_init(&even, color(0.5, 0.0, 0.5));
	solid_color_init(&odd, color(0.9, 0.9, 0.9));
	checker_texture_init(&checker_texture, 0.32, &even, &odd);
	lambertian_init_tex(&lambertian_material_ground, (t_texture*)&(checker_texture));
	
	t_lambertian lambertian_material_center;
	t_solid_color solid_color_texture2;
	solid_color_init(&solid_color_texture2, color(0.1, 0.2, 0.5));
	lambertian_init_tex(&lambertian_material_center, (t_texture*)&(solid_color_texture2));
	t_dielectric dielectric_material_left;
	t_dielectric dielectric_material_bubble;
	t_metal metal_material_right;

    // metal_init(&metal_material_left, color(0.8, 0.8, 0.8), 0.3);
	dielectric_init(&dielectric_material_left, 1.50);
	dielectric_init(&dielectric_material_bubble, 1.00 / 1.50);
	metal_init(&metal_material_right, color(0.8, 0.6, 0.2), 1.0);

	// Assuming t_lambertian and t_metal have a t_material as their first member,
	// you can safely cast their addresses to t_material*.
	t_sphere s1 = sphere(point3(0.0, -100.5, -1.0), 100.0, (t_material*)&lambertian_material_ground);
	t_sphere s2 = sphere(point3(0.0, 0.0, -1.2), 0.5, (t_material*)&lambertian_material_center);
	// t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_left);
	
	t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&dielectric_material_left);
	t_sphere s4 = sphere(point3(-1.0, 0.0, -1.0), 0.4, (t_material*)&dielectric_material_bubble);
	t_sphere s5 = sphere(point3(1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_right);

	t_hittable *list[5];

	list[0] = (t_hittable*)(&s1);
	list[1] = (t_hittable*)(&s2);
	list[2] = (t_hittable*)(&s3);
	list[3] = (t_hittable*)(&s4);
	list[4] = (t_hittable*)(&s5);
	const t_hittablelist world = hittablelist(list, 5);
	
	// init camera

    t_camera c = camera();

	printf("camera init done ================ ");
	// render
	render(c, world);
	return (0);
}


// this wasthe previous main function but computationally expensive
int bouncing()
{
	t_lambertian ground;
	t_solid_color ground_color;
	solid_color_init(&ground_color, color(0.5, 0.5, 0.5));
   	lambertian_init_tex(&ground, (t_texture*)&ground_color);
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
					t_color albedo = cross(color_random(), color_random());
					t_solid_color solid_color_albedo;
					solid_color_init(&solid_color_albedo, albedo);
					lambertian_init_tex(&sphere_materials_lambertian[i], (t_texture*)&solid_color_albedo);
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
	t_solid_color solid_color_material2;
	solid_color_init(&solid_color_material2, color(0.4, 0.2, 0.1));
	lambertian_init_tex(&material2,(t_texture*)&solid_color_material2);

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
