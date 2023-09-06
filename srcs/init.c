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

void	init_system(t_state *vars, int max_iterations)
{
	vars->screenblocks = dividescreen(WIDTH, HEIGHT,
			sqrt(NUM_THREADS), sqrt(NUM_THREADS));
	vars->render_size = (t_ivec2d){.x = WIDTH, .y = HEIGHT};
	vars->max_iterations = max_iterations;
	vars->virt_min = (t_vec2d){.x = -2, .y = -2};
	vars->virt_max = (t_vec2d){.x = 2, .y = 2};
	vars->zoom = 1.0f;
	vars->palette = 1;
	vars->fract = (t_fracts){.mandelbrot = 2,
		.julia = (t_vec2d){.x = 0, .y = 0}, .burning = 1};
	vars->render_lock = 0;
	vars->debug.drawdebug = 0;
	vars->debug.drawgraph = 0;
	vars->debug.drawtext = 0;
	vars->debug.drawiter = 0;
	vars->debug.drawlasthit = 0;
	vars->debug.drawhelp = 0;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx,
			vars->render_size.x, vars->render_size.y, "UwU");
	vars->img = mlx_new_image(vars->mlx,
			vars->render_size.x, vars->render_size.y);
	vars->addr = mlx_get_data_addr(vars->img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
}

void	switch_fract(t_state *vars, t_fractals new)
{
	if (new == mandelbrot)
		vars->function = &mandelbrot_math;
	else if (new == julia)
		vars->function = &julia_math;
	else if (new == burning)
		vars->function = &burning_ship_math;
	else if (new == black)
		vars->function = &empty;
}
