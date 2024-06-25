/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:53:54 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 11:57:46 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

#include <stdbool.h>
#include <math.h>

/*
 * Used to represent a range of t values
 */
typedef struct	s_interval
{
	double		min;
	double		max;
}				t_interval;

/*
 * Initializer
 */
t_interval interval(double min, double max);

/*
 * Returns the size of the interval
 */
inline double size(const t_interval *i)
{
	return (i->max - i->min);
}

/*
 * Will return true for values including boundaries
 */
inline bool contains(const t_interval *i, double x)
{
	return (x >= i->min && x <= i->max);
}

/*
 * Will return true for values inside excluding boundaries
 */
inline bool surrounds(const t_interval *i, double x)
{
	return (x > i->min && x < i->max);
}

/*
 * Returns an empty interval
 */
inline t_interval empty_interval()
{
	return (t_interval){0, 0};
}

/*
 * Returns an interval that contains all values
 */
inline t_interval universe_interval()
{
	return (t_interval){-INFINITY, INFINITY};
}

inline double	clamp(t_interval t, double x) 
{
	if (x < t.min) return t.min;
	if (x > t.max) return t.max;
	return x;
}

#endif
