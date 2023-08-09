/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:50:03 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/08 11:55:40 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../includes/keycodes_osx.h"

void suicide(t_state *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	//mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void consoleprint(t_state *vars)
{
	printf("virt_max (x/y): %f/%f\n", vars->virt_max.x, vars->virt_max.y);
	printf("virt_min (x/y): %f/%f\n", vars->virt_min.x, vars->virt_min.y);
	printf("zoom: %f\n", vars->zoom);
	printf("debug: %i\n", vars->debug.drawdebug);
}

int	key_hook(int keycode, t_state *vars)
{
	vars->render_lock = 0;
	ft_printf("key: %i\n", keycode);
	if (keycode == KEY_LEFT)
	{
		vars->virt_min.x -= 0.15 * vars->zoom;
		vars->virt_max.x -= 0.15 * vars->zoom;
	}
	else if (keycode == KEY_RIGHT)
	{
		vars->virt_min.x += 0.15 * vars->zoom;
		vars->virt_max.x += 0.15 * vars->zoom;
	}
	else if (keycode == KEY_UP)
	{
		vars->virt_min.y -= 0.15 * vars->zoom;
		vars->virt_max.y -= 0.15 * vars->zoom;
	}
	else if (keycode == KEY_DOWN)
	{
		vars->virt_min.y += 0.15 * vars->zoom;
		vars->virt_max.y += 0.15 * vars->zoom;
	}
	else if (keycode == NUMPAD_PLUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 1);
	else if (keycode == NUMPAD_MINUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 0);
	else if (keycode == NUMPAD_7)
		vars->max_iterations -= 10;
	else if (keycode == NUMPAD_9)
		vars->max_iterations += 10;
	else if (keycode == NUMPAD_4)
		vars->fract.mandelbrot -= 1;
	else if (keycode == NUMPAD_6)
		vars->fract.mandelbrot += 1;
		
	else if (keycode == KEY_ESC || keycode == KEY_X)
		suicide(vars);
	else if (keycode == KEY_R)
	{
		vars->virt_min = (t_vec2d){.x = -2, .y = -2};
		vars->virt_max = (t_vec2d){.x = 2, .y = 2};
		vars->zoom = 1.0f;
	}
	
	else if (keycode == KEY_1)
		switch_fract(vars, julia);
	else if (keycode == KEY_2)
		switch_fract(vars, mandelbrot);
	else if (keycode == KEY_3)
		switch_fract(vars, burning);
		
	else if (keycode == KEY_P)
		consoleprint(vars);
	else if (keycode == KEY_D)
		vars->debug.drawdebug = 1 - vars->debug.drawdebug;
	else if (keycode == KEY_G)
		vars->debug.drawgraph = 1 - vars->debug.drawgraph;
	else if (keycode == KEY_T)
		vars->debug.drawtext = 1 - vars->debug.drawtext;
	else if (keycode == KEY_I)
		vars->debug.drawiter = 1 - vars->debug.drawiter;
	else if (keycode == KEY_H)
		vars->debug.drawlasthit = 1 - vars->debug.drawlasthit;
	return (0);
}

int	mouse_hook(int code, int x, int y, t_state *vars)
{
	vars->render_lock = 0;
	if (code == 1)
	{
		//printf("mouse event\nx:%i y:%i\nrx:%f ry:%f\n", x, y, virtual_to_real(vars, x, y).x, virtual_to_real(vars, x, y).y);
		//vars->debug.drawiter = 1 - vars->debug.drawiter;
		vars->debug.lasthitreal = virtual_to_real(vars, x, y);
		vars->debug.lhvmax = vars->virt_max;
		vars->debug.lhvmin = vars->virt_min;

		vars->fract.julia = vars->debug.lasthitreal;
	}
	if (code == 2)
		printf("mouse right\n");
	else if (code == 3)
		printf("mouse middle\n");
	else if (code == 4)
		ft_zoom(x, y, vars, 1);
	else if (code == 5)
		ft_zoom(x, y, vars, 0);
	return (0);
}
