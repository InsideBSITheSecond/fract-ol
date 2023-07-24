/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:32:53 by llegrand          #+#    #+#             */
/*   Updated: 2023/07/24 16:32:53 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_vec2d	mandelbrot_calc(t_fracts var, t_vec2d val, t_vec2d constant)
{
	val = power_vec2d(val, var.mandelbrot);
	val = add_vec2d(val, constant);
	return (val);
}

float	ft_mandelbrot_math(t_state *vars, int x, int y, int max_iterations)
{
	int			i;
	t_vec2d		val;
	t_vec2d		constant;

	i = 0;
	val.x = 0.0;
	val.y = 0.0;
	constant = virtual_to_real(vars, x, y);
	while (i < max_iterations)
	{
		val = mandelbrot_calc(vars->fract, val, constant);
		if (pow(val.x, 2) + pow(val.y, 2) > 2.0 * 2.0)
			break ;
		i++;
	}
	return (i);
}
