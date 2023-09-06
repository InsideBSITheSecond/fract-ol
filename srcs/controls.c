/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:30:58 by llegrand          #+#    #+#             */
/*   Updated: 2023/08/15 17:30:58 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../includes/keycodes_osx.h"

void	kb_movement(int keycode, t_state *vars)
{
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
}

void	kb_modifiers(int keycode, t_state *vars)
{
	if (keycode == NUMPAD_7)
		vars->max_iterations -= 10;
	else if (keycode == NUMPAD_9)
		vars->max_iterations += 10;
	else if (keycode == NUMPAD_4)
		vars->fract.mandelbrot -= 1;
	else if (keycode == NUMPAD_6)
		vars->fract.mandelbrot += 1;
}

void	kb_debugmode(int keycode, t_state *vars)
{
	if (keycode == KEY_P)
		vars->palette = (vars->palette + 1) % 3;
	else if (keycode == KEY_D)
		vars->debug.drawdebug = 1 - vars->debug.drawdebug;
	else if (keycode == KEY_G)
		vars->debug.drawgraph = 1 - vars->debug.drawgraph;
	else if (keycode == KEY_T)
		vars->debug.drawtext = 1 - vars->debug.drawtext;
	else if (keycode == KEY_I)
	{
		vars->debug.drawiter = (vars->debug.drawiter + 1) % 4;
		printf("di: %i\n", vars->debug.drawiter);
	}
	else if (keycode == KEY_H)
		vars->debug.drawlasthit = 1 - vars->debug.drawlasthit;
	else if (keycode == KEY_QUESTIONMARK)
		vars->debug.drawhelp = 1 - vars->debug.drawhelp;
}

void	kb_misc(int keycode, t_state *vars)
{
	if (keycode == KEY_ESC || keycode == KEY_X)
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
	else if (keycode == KEY_4)
		switch_fract(vars, black);
}
