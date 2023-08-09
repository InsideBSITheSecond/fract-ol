/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:35:42 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/09 16:32:27 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
