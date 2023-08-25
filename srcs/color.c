/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:06:49 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/23 21:46:29 by insidebsi        ###   ########.fr       */
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
	static t_mappingpoint	points[7] = {
	{0.0, 787842},
	{15, 9398813},
	{30, 2750209},
	{65, 8454389},
	{90, 16776704},
	{95, 16711680},
	{100, 328965}
	};
	static t_mappingpoint	points2[7] = {
	{0.0, 16758784},
	{15, 16410597},
	{30, 12342265},
	{65, 5800443},
	{90, 21433998},
	{95, 845292},
	{100, 585082}
	};
	t_mpmapping				mapping;
	t_mpmapping				mapping2;

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
