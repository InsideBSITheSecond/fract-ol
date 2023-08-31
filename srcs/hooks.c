/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:50:03 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/31 18:24:51 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	suicide(t_state *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	free(vars->screenblocks);
	exit(0);
}

void	consoleprint(t_state *vars)
{
	ft_printf("virt_max (x/y): %f/%f\n", vars->virt_max.x, vars->virt_max.y);
	ft_printf("virt_min (x/y): %f/%f\n", vars->virt_min.x, vars->virt_min.y);
	ft_printf("zoom: %f\n", vars->zoom);
	ft_printf("debug: %i\n", vars->debug.drawdebug);
}

int	key_hook(int keycode, t_state *vars)
{
	vars->render_lock = 0;
	ft_printf("key: %i\n", keycode);
	kb_movement(keycode, vars);
	kb_modifiers(keycode, vars);
	kb_debugmode(keycode, vars);
	kb_misc(keycode, vars);
	return (0);
}

/*
* IMPLEMENT DRAG ON RIGHT MOUSE & CENTER ON MIDDLE
* */
int	mouse_hook(int code, int x, int y, t_state *vars)
{
	vars->render_lock = 0;
	if (code == 1)
	{
		vars->debug.lasthitreal = virtual_to_real(vars, x, y);
		vars->debug.lhvmax = vars->virt_max;
		vars->debug.lhvmin = vars->virt_min;
		vars->fract.julia = vars->debug.lasthitreal;
	}
	if (code == 2)
		ft_printf("mouse right\n");
	else if (code == 3)
		ft_printf("mouse middle\n");
	else if (code == 4)
		ft_zoom(x, y, vars, 1);
	else if (code == 5)
		ft_zoom(x, y, vars, 0);
	return (0);
}
