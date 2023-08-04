/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:35:23 by llegrand          #+#    #+#             */
/*   Updated: 2023/07/26 15:35:23 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	switch_fract(t_state *vars, t_fractals new)
{
	if (new == mandelbrot)
		vars->function = &mandelbrot_math;
	else if (new == julia)
		vars->function = &julia_math;
	else if (new == burning)
		vars->function = &burning_ship_math;
}
