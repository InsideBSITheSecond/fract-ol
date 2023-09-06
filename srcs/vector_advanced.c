/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:27:45 by llegrand          #+#    #+#             */
/*   Updated: 2023/08/09 16:27:45 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_vec2d	mult_vec2d(t_vec2d a, t_vec2d b)
{
	t_vec2d	mult;

	mult.x = (a.x * b.x) - (a.y * b.y);
	mult.y = (a.x * b.y) + (a.y * b.x);
	return (mult);
}

t_vec2d	div_vec2d(t_vec2d a, t_vec2d b)
{
	double		const_div;
	t_vec2d		to_div;

	const_div = 1 / (pow(b.x, 2) + pow(b.y, 2));
	to_div.x = (a.x * b.x) + (a.y * b.y);
	to_div.y = (a.y * b.x) - (a.x * b.y);
	real_const_vec2d(&to_div, const_div);
	return (to_div);
}

void	sqr_vec2d(t_vec2d *a, double real_c, double img_c)
{
	t_vec2d	tmp;

	tmp = *a;
	a->x = pow(tmp.x, 2) - pow(tmp.y, 2) + real_c;
	a->y = 2 * tmp.x * tmp.y + img_c;
}

t_vec2d	power_vec2d(t_vec2d a, int n)
{
	t_vec2d	tmp;

	tmp = a;
	if (n == 0)
	{
		tmp.x = 0;
		tmp.y = 0;
		return (tmp);
	}
	if (n == 1)
		return (tmp);
	tmp = power_vec2d(a, n / 2);
	if (n % 2 == 0)
		return (mult_vec2d(tmp, tmp));
	return (mult_vec2d(a, mult_vec2d(tmp, tmp)));
}

t_vec2d	vec2d_pow_add(t_fracts var, t_vec2d val, t_vec2d constant)
{
	val = power_vec2d(val, var.mandelbrot);
	val = add_vec2d(val, constant);
	return (val);
}
