/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:35:42 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/20 19:43:14 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_vec2d	virtual_to_real(t_state *vars, int x, int y)
{
	t_vec2d	res;

	res.x = vars->virt_min.x + ((x * (vars->virt_max.x - vars->virt_min.x)) / WIDTH);
	res.y = vars->virt_min.y + ((y * (vars->virt_max.y - vars->virt_min.y)) / WIDTH);
	return (res);
}


t_vec2d	create_vec2d(double x, double y)
{
	t_vec2d	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2d	add_vec2d(t_vec2d a, t_vec2d b)
{
	t_vec2d	added;

	added.x = a.x + b.x;
	added.y = a.y + b.y;
	return (added);
}

t_vec2d	sub_vec2d(t_vec2d a, t_vec2d b)
{
	t_vec2d	sub;

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	return (sub);
}

void	real_const_vec2d(t_vec2d *a, double c)
{
	(*a).x *= c;
	(*a).y *= c;
}

t_vec2d	mult_vec2d(t_vec2d a, t_vec2d b)
{
	t_vec2d	mult;

	mult.x = (a.x * b.x) - (a.y * b.y);
	mult.y = (a.x * b.y) + (a.y * b.x);
	return (mult);
}

t_vec2d	div_vec2d(t_vec2d a, t_vec2d b)
{
	double	const_div;
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