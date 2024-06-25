/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/25 12:18:40 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <stdio.h>
#include <limits.h>
#include "interval.h"


t_color color(double r, double g, double b)
{
	t_color result;

	result.r = r;
	result.g = g;
	result.b = b;
	return result;
}

/*
write a pixel to a file
the format is PPM and this function is called from create_ppm_image
*/
void write_color(FILE *file, t_color pixel_color)
{
	// Write the translated [0,255] value of each color component
	double r = pixel_color.r;
	double g = pixel_color.g;
	double b = pixel_color.b;

	// Gamma correction
	r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
	
	t_interval intensity = interval(0.0, 0.999); 
	int rbyte = (int)(256 * clamp(intensity, r));
	int gbyte = (int)(256 * clamp(intensity, g));
	int bbyte = (int)(256 * clamp(intensity, b));
	fprintf(file, "%d %d %d\n", rbyte, gbyte, bbyte);
}

t_color creategradient(t_vec3 dir, t_color white, t_color blue)
{
	double a = 0.5 * (dir.y + 1.0);
	t_color white_scaled = vec3multscalar(white, 1.0 - a);
	t_color blue_scaled = vec3multscalar(blue, a);
	t_color raycolor = vec3add(white_scaled, blue_scaled);
	return raycolor;
}

t_color	backgroundcolor(t_vec3 dir)
{
	t_color blue;
	t_color white;
	t_color raycolor;
	
	white = vec3(1.0, 1.0, 1.0);
	blue = vec3(0.5, 0.7, 1.0);
	dir = unit_vector(dir);
	raycolor = creategradient(dir, white, blue);
	return raycolor;
}

/*
 * Generate a random color
 */
t_color		color_random()
{
	return color(random_double(0, 1), random_double(0, 1), random_double(0, 1));
}

/*
 * Generate a random color with components between min and max
 */
t_color		color_random_min_max(double min, double max)
{
	return color(random_double(min, max), random_double(min, max), random_double(min, max));
}