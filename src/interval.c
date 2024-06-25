/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:59:43 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 12:05:14 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"

/*
 * initializer
 */
t_interval interval(double min, double max)
{
	t_interval i;

	i.min = min;
	i.max = max;
	return (i);
}
