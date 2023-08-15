/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:06:49 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/15 17:21:44 by llegrand         ###   ########.fr       */
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

int	which_colour(int it, int palette)
{
	if (palette == 0)
		return (create_argb(0, 255 - (it % 255) * 10,
				255 - (it % 255) * 10, 255 - (it % 255) * 10));
	else if (palette == 1)
		return (create_argb(0, (it * 7 % 255), (it % 255), (it % 255)));
	else if (palette == 2)
		return (create_argb(0, (it * 2 % 255),
				(it * 15 % 255), (it * 50 % 255)));
	else
		return (0);
}
