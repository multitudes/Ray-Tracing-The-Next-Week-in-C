/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:02:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/04 18:45:52 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "vec3.h"
#include "rtw_stb_image.h"

typedef struct s_texture
{
	t_color (*value)(const void *self, double u, double v, const t_point3 *p);
}               t_texture;

typedef struct s_solid_color
{
	t_texture base;
	t_color color_albedo;
}               t_solid_color;

typedef struct 		s_checker_texture
{
	t_texture 		base;
	double    		inv_scale;
	t_solid_color 	*even;
	t_solid_color 	*odd;
}               	t_checker_texture;

typedef struct		s_img_texture
{
	t_texture		base;
	char 			*filename;
	t_rtw_image		*img;

}					t_img_texture;

void 	solid_color_init(t_solid_color *solid_color_texture, t_color albedo);
t_color solid_color_value(const void *self, double u, double v, const t_point3 *p);

void	checker_texture_init(t_checker_texture *checker_texture, double scale, t_solid_color *even, t_solid_color *odd);
t_color checker_texture_value(const void *self, double u, double v, const t_point3 *p);

void	img_texture_init(t_img_texture *img_texture, t_rtw_image *img);
t_color img_texture_value(const void *self, double u, double v, const t_point3 *p);

#endif