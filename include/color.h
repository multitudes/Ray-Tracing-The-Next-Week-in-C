/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:47:37 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/25 12:18:52 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include <stdio.h>
# include <math.h>

t_color		color(double r, double g, double b);
void		write_color(FILE *file, t_color pixel_color);
t_color 	creategradient(t_vec3 dir, t_color white, t_color blue);
t_color		backgroundcolor(t_vec3 dir);
t_color		color_random();
t_color		color_random_min_max(double min, double max);

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}

#endif