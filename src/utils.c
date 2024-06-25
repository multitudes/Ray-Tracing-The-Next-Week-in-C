/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:24:42 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 12:04:55 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>
#include <stdio.h>
#include "color.h"

/*
PPM format. as in wiki:
P3 means the colors are in ascii, and the first two numbers are 
the width and height of the image. Then RGB triplets follow
By convention, each of the red/green/blue components are represented 
internally by real-valued variables that range from 0.0 to 1.0. 
These must be scaled to integer values between 0 and 255 before 
we print them out. 
*/
void create_ppm_image(char *filename, int width, int height)
{
	FILE *file;
	char filepath[PATH_MAX];
	int image_width = width;
	int image_height = height;

	// render
	sprintf(filepath, "assets/%s", filename);

	file = fopen(filepath, "w");
	fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++) 
	{
		// write to std err
		fprintf(stderr, "\rScanlines remaining: %d\n", image_height - j);
		for (int i = 0; i < image_width; i++)
		{
			t_color pixel_color = vec3((float)i / (image_width - 1), (float)j / (image_height - 1), 0.0);
			write_color(file, pixel_color);
		}
	}
}

/*
PPM format. as in wiki:
P3 means the colors are in ascii, and the first two numbers are 
the width and height of the image. Then RGB triplets follow
By convention, each of the red/green/blue components are represented 
internally by real-valued variables that range from 0.0 to 1.0. 
These must be scaled to integer values between 0 and 255 before 
we print them out. 
*/
// void create_ppm_image2(char *filename, int width, int height)
// {
	// FILE *file;
	// char filepath[PATH_MAX];
	// int image_width = width;
	// int image_height = height;

	// // render
	// sprintf(filepath, "assets/%s", filename);

	// file = fopen(filepath, "w");
	// fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

	// for (int j = 0; j < image_height; j++) 
	// {
	// 	// write to std err
	// 	fprintf(stderr, "\rScanlines remaining: %d\n", image_height - j);
	// 	for (int i = 0; i < image_width; i++)
	// 	{
	// 		t_point3 pixel_center = 


	// 		// t_color pixel_color = vec3((float)i / (image_width - 1), (float)j / (image_height - 1), 0.0);
	// 		write_color(file, &pixel_color);
	// 	}
	// }
// }