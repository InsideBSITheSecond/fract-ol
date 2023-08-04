/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:14 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/18 19:15:14 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main(int argc, char **argv)
{
	(void)argc;
	t_state	vars;

	if (round(sqrt(NUM_THREADS)) != sqrt(NUM_THREADS))
	{
		printf("sqrt(NUM_THREADS) must be an integer");
		return (0);
	}
	if(round(WIDTH / sqrt(NUM_THREADS)) != WIDTH / sqrt(NUM_THREADS))
	{
		printf("WIDTH must be dividable by sqrt(NUM_THREADS)");
		return (0);
	}
	if(round(HEIGHT / sqrt(NUM_THREADS)) != HEIGHT / sqrt(NUM_THREADS))
	{
		printf("WIDTH must be dividable by sqrt(NUM_THREADS)");
		return (0);
	}

	vars.screenblocks = dividescreen(WIDTH, HEIGHT, sqrt(NUM_THREADS), sqrt(NUM_THREADS));
	vars.render_size = (t_ivec2d){.x = WIDTH, .y = HEIGHT};
	//vars.constant = (t_vec2d){.x = -0.75, .y = 0.05};
	vars.max_iterations = ft_atoi(argv[1]);
	vars.virt_min = (t_vec2d){.x = -2, .y = -2};
	vars.virt_max = (t_vec2d){.x = 2, .y = 2};
	vars.zoom = 1.0f;
	vars.palette = 2;
	vars.fract = (t_fracts){.mandelbrot = 2, .julia = (t_vec2d){.x = 0, .y = 0}, .burning = 1};
	vars.render_lock = 0;
	switch_fract(&vars, julia);

	vars.debug.drawdebug = 0;
	vars.debug.drawgraph = 0;
	vars.debug.drawtext = 0;
	vars.debug.drawiter = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.render_size.x, vars.render_size.y, "UwU");
	vars.img= mlx_new_image(vars.mlx, vars.render_size.x, vars.render_size.y);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render, &vars);
	mlx_loop(vars.mlx);
}
