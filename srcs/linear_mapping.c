/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:03:30 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/27 18:58:15 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	linmap(double val, t_vec2d range1, t_vec2d range2)
{
	return (((val - range1.x) / (range1.y - range1.x))
		* (range2.y - range2.x) + range2.x);
}

int	colorlinmap(int a, int b, float ratio)
{
	return (create_argb(0,
			linmap(ratio, (t_vec2d){.x = 0, .y = 255},
			(t_vec2d){.x = get_r(a), .y = get_r(b)}),
			linmap(ratio, (t_vec2d){.x = 0, .y = 255},
			(t_vec2d){.x = get_g(a), .y = get_g(b)}),
			linmap(ratio, (t_vec2d){.x = 0, .y = 255},
			(t_vec2d){.x = get_b(a), .y = get_b(b)})));
}

// Function to perform linear mapping using multi-point mapping
double	mappedlmap(const t_mpmapping *mapping, double input)
{
	int				i;
	t_mappingpoint	*point1;
	t_mappingpoint	*point2;

	i = 0;
	point1 = NULL;
	point2 = NULL;
	if (mapping->numpoints < 2)
		return (create_argb(0, 0, 0, 0));
	while (i < mapping->numpoints - 1)
	{
		if (input >= mapping->points[i].input
			&& input <= mapping->points[i + 1].input)
		{
			point1 = &mapping->points[i];
			point2 = &mapping->points[i + 1];
			break ;
		}
		i++;
	}
	if (!point1 || !point2)
		return (create_argb(0, 0, 0, 0));
	return (colorlinmap(point1->output, point2->output, 
			linmap(input, (t_vec2d){.x = point1->input, .y = point2->input},
			(t_vec2d){.x = 0, .y = 255})));
}
