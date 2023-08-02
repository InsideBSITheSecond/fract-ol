/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:28:33 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/01 21:28:51 by insidebsi        ###   ########.fr       */
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

t_vec2d real_to_virtual(t_state *vars, float x, float y)
{
	t_vec2d res;

    double width = vars->virt_max.x - vars->virt_min.x;
    double height = vars->virt_max.y - vars->virt_min.y;

    res.x = (x - vars->virt_min.x) * WIDTH / width;
    res.y = (y - vars->virt_min.y) * WIDTH / height;

    return res;
}