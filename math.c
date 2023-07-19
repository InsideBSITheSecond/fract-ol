/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:35:42 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/19 15:46:29 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vec2d add_vec2d(t_vec2d a, t_vec2d b)
{
    t_vec2d added;

    added.x = a.x + b.x;
    added.y = a.y + b.y;
    return (added);
}


t_vec2d	virtual_to_real(t_vars vars, int x, int y)
{
	t_cpx	res;

	res.x = vars.virt_min.x + ((x * (vars.virt_max.x - vars.virt_min.x)) / WIDTH);
	res.y = vars.virt_min.y + ((y * (vars.virt_max.y - vars.virt_min.y)) / WIDTH);
	return (res);
}