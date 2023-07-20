/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:50:03 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/20 19:43:14 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	key_hook(int keycode, t_state *vars)
{
	vars->render_lock = 0;
	if (keycode == KEY_LEFT)
	{
		vars->virt_min.x -= 0.15 * vars->zoom;
		vars->virt_max.x -= 0.15 * vars->zoom;;
	}
	if (keycode == KEY_RIGHT)
	{
		vars->virt_min.x += 0.15 * vars->zoom;
		vars->virt_max.x += 0.15 * vars->zoom;;
	}
	if (keycode == KEY_UP)
	{
		vars->virt_min.y -= 0.15 * vars->zoom;
		vars->virt_max.y -= 0.15 * vars->zoom;;
	}
	if (keycode == KEY_DOWN)
	{
		vars->virt_min.y += 0.15 * vars->zoom;
		vars->virt_max.y += 0.15 * vars->zoom;;
	}
	if (keycode == NUMPAD_PLUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 1);
	if (keycode == NUMPAD_MINUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 0);
	if (keycode == NUMPAD_7)
		vars->max_iterations -= 10;
	if (keycode == NUMPAD_9)
		vars->max_iterations += 10;
	if (keycode == NUMPAD_4)
		vars->fract.mandelbrot -= 1;
	if (keycode == NUMPAD_6)
		vars->fract.mandelbrot += 1;
	if (keycode == KEY_ESC || keycode == KEY_X)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int mouse_hook(int code, t_state *vars)
{
	(void)code;
	(void)vars;
	ft_printf("Hello from mouse_hook!\n");
	return (0);
}