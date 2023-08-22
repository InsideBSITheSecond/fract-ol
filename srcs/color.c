/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:06:49 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/22 23:18:00 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

/*int	get_a(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}*/

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

double	linmap(double val, double lower1,
	double upper1, double lower2, double upper2)
{
	return (((val - lower1) / (upper1 - lower1)) * (upper2 - lower2) + lower2);
}

int	colorlinmap(int a, int b, float ratio)
{
	return (create_argb(0,
			linmap(ratio, 0, 255, get_r(a), get_r(b)),
			linmap(ratio, 0, 255, get_g(a), get_g(b)),
			linmap(ratio, 0, 255, get_b(a), get_b(b))));
}

int	which_colour(int it, int palette, int max_it)
{
	t_mappingpoint *points;
	t_mappingpoint *points2;
	t_mpmapping	mapping;
    t_mpmapping	mapping2;
	
	points = (t_mappingpoint *)ft_calloc(sizeof(t_mappingpoint), 7);
	points[0] = (t_mappingpoint){0.0, create_argb(0, 12, 5, 130)};
	points[1] = (t_mappingpoint){15, create_argb(0, 143, 106, 29)};
	points[2] = (t_mappingpoint){30, create_argb(0, 41, 247, 1)};
	points[3] = (t_mappingpoint){65, create_argb(0, 129, 0, 245)};
	points[4] = (t_mappingpoint){90, create_argb(0, 255, 254, 0)};
	points[5] = (t_mappingpoint){95, create_argb(0, 255, 0, 0)};
	points[6] = (t_mappingpoint){100, create_argb(0, 5, 5, 5)};

	points2 = (t_mappingpoint *)ft_calloc(sizeof(t_mappingpoint), 7);
	points2[0] = (t_mappingpoint){0.0, create_argb(0, 255, 184, 0)};
	points2[1] = (t_mappingpoint){10, create_argb(0, 250, 103, 229)};
	points2[2] = (t_mappingpoint){25, create_argb(0, 188, 83, 249)};
	points2[3] = (t_mappingpoint){50, create_argb(0, 88, 129, 251)};
	points2[4] = (t_mappingpoint){90, create_argb(0, 32, 182, 254)};
	points2[5] = (t_mappingpoint){95, create_argb(0, 12, 229, 236)};
	points2[6] = (t_mappingpoint){100, create_argb(0, 8, 237, 122)};

	mapping = (t_mpmapping){7, points};
	mapping2 = (t_mpmapping){7, points2};
	
	if (palette == 0)
		return (mappedlmap(&mapping2, linmap(it, 1, max_it, 0, 110)));
	else if (palette == 1)
		return (mappedlmap(&mapping, linmap(it, 1, max_it, 0, 110)));
	else if (palette == 2)
		return (create_argb(0, 
				(it * 2 % 255),
				(it * 15 % 255), 
				(it * 50 % 255)));
	else
		return (0);
}
