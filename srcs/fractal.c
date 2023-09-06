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

float	empty(t_state *vars, t_ivec2d vector,
		int max_iterations, int displaychain)
{
	if (displaychain)
		mandelbrot_math(vars, vector, max_iterations, displaychain);
	return (0);
}

void	drawiter(t_state *vars, t_vec2d val, t_vec2d bkp, int i)
{
	if (vars->debug.drawiter == 1 || vars->debug.drawiter == 3)
		drawline(vars, 
			real_to_virtual(vars, val.x, val.y),
			real_to_virtual(vars, bkp.x, bkp.y),
			which_colour(i, vars->palette, vars->max_iterations));
	if (vars->debug.drawiter == 2 || vars->debug.drawiter == 3)
		drawcircle(vars, (t_circle){
			.x = real_to_virtual(vars, val.x, val.y).x, 
			.y = real_to_virtual(vars, val.x, val.y).y, 
			.color = which_colour(i,
				vars->palette, vars->max_iterations), .rad = 2});
}

float	mandelbrot_math(t_state *vars, t_ivec2d vector,
		int max_iterations, int displaychain)
{
	int			i;
	t_vec2d		val;
	t_vec2d		constant;
	t_vec2d		bkp;

	i = 0;
	val.x = 0.0;
	val.y = 0.0;
	constant = virtual_to_real(vars, vector.x, vector.y);
	while (i < max_iterations)
	{
		bkp = val;
		val = vec2d_pow_add(vars->fract, val, constant);
		if (displaychain)
			drawiter(vars, val, bkp, i);
		if (pow(val.x, 2) + pow(val.y, 2) > 2.0 * 2.0)
			break ;
		i++;
	}
	return (i);
}

float	julia_math(t_state *vars, t_ivec2d vector,
		int max_iterations, int displaychain)
{
	int			i;
	t_vec2d		val;
	t_vec2d		constant;
	t_vec2d		bkp;

	i = 0;
	val = virtual_to_real(vars, vector.x, vector.y);
	constant = vars->fract.julia;
	while (i < max_iterations)
	{
		bkp = val;
		val = vec2d_pow_add(vars->fract, val, constant);
		if (displaychain)
			drawiter(vars, val, bkp, i);
		if (pow(val.x, 2) + pow(val.y, 2) > 2.0 * 2.0)
			break ;
		i++;
	}
	return (i);
}

float	burning_ship_math(t_state *vars, t_ivec2d vector,
		int max_iterations, int displaychain)
{
	int			i;
	t_vec2d		val;
	t_vec2d		constant;
	t_vec2d		bkp;

	i = 0;
	val.x = 0.0;
	val.y = 0.0;
	constant = virtual_to_real(vars, vector.x, vector.y);
	while (i < max_iterations && vars->fract.julia.x == 0.0)
	{
		bkp = val;
		val = vec2d_pow_add(vars->fract, val, constant);
		val.x = fabsl(val.x);
		val.y = fabsl(val.y);
		if (displaychain)
			drawiter(vars, val, bkp, i);
		if (pow(val.x, 2) + pow(val.y, 2) > 2.0 * 2.0)
			break ;
		i++;
	}
	return (i);
}
