/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:06:49 by insidebsi         #+#    #+#             */
/*   Updated: 2023/09/06 17:05:44 by llegrand         ###   ########.fr       */
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

int	which_colour(int it, int palette, int max_it)
{
	t_mpmapping				mapping;
	t_mpmapping				mapping2;

	mapping = (t_mpmapping){7, getpalette1()};
	mapping2 = (t_mpmapping){7, getpalette2()};
	if (palette == 0)
		return (mappedlmap(&mapping2, linmap(it,
					(t_vec2d){.x = 1, .y = max_it},
				(t_vec2d){.x = 0, .y = 101})));
	else if (palette == 1)
		return (mappedlmap(&mapping, linmap(it,
					(t_vec2d){.x = 1, .y = max_it},
				(t_vec2d){.x = 0, .y = 101})));
	else if (palette == 2)
		return (create_argb(0, 
				(it * 2 % 255),
				(it * 15 % 255), 
				(it * 50 % 255)));
	else
		return (0);
}
