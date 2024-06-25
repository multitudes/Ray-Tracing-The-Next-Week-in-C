/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:04 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/19 13:16:53 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "rtweekend.h"

/*
 * This is the C equivalent of a C++ initializer
 */
t_vec3	vec3(double x, double y, double z)
{
	t_vec3 result;

	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

t_point3	point3(double x, double y, double z)
{
	t_point3 result;

	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}


t_vec3	vec3negate(const t_vec3 a)
{
	t_vec3 result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	return result;
}

t_vec3	vec3add(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

t_vec3	vec3substr(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

t_vec3	vec3mult(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;

}

t_vec3	vec3multscalar(const t_vec3 a, double t)
{
	t_vec3 result;

	result.x = a.x * t;
	result.y = a.y * t;
	result.z = a.z * t;
	return result;
}

t_vec3	vec3divscalar(const t_vec3 a, double t)
{
	t_vec3 result;

	result.x = a.x / t;
	result.y = a.y / t;
	result.z = a.z / t;
	return result;
}
  
double	length_squared(const t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	length(const t_vec3 v)
{
	return (sqrt(length_squared(v)));
}

// Vector Utility Functions
/*
 * to debug
 */
void	print_vec3(const t_vec3 *v)
{
	printf("%f %f %f\n", v->x, v->y, v->z);
}

/*
 * dot product of vectors a . b = a1*b1 + a2*b2 + a3*b3
 */
double	dot(const t_vec3 a, const t_vec3 b)
{
	double result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

/*
returns the cross product of a and b by value
*/
t_vec3	vec3cross(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

t_vec3 random_vec3() 
{
    return vec3(random_d(), random_d(), random_d());
}

t_vec3 random_vec3_min_max(double min, double max) 
{
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

bool near_zero(t_vec3 e) 
{
	// Return true if the vector is close to zero in all dimensions.
	const double s = 1e-8;
	return (fabs(e.x) < s) && (fabs(e.y) < s) && (fabs(e.z) < s);
}