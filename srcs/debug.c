/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:20:52 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/31 15:36:27 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	renderdebugtext(t_state *vars)
{
	int	ystart;

	ystart = 25;
	/*mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Iterations: %i", vars->max_iterations));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Last hit: %d - %d",
			vars->debug.lasthitreal.x, vars->debug.lasthitreal.y));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Virt min: %d - %d",
			vars->virt_min.x, vars->virt_min.y));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Virt max: %d - %d",
			vars->virt_max.x, vars->virt_max.y));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Zoom:    %d",
			vars->zoom));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("0sMeter: 0.123456789abcdef"));
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
		YELLOW, ft_strformat("Palette: %i",
			vars->palette));*/
}

void	renderdebughelp(t_state *vars)
{
	int	ystart;

	ystart = 25;
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("D : Toggle debug mode"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("? : Toggle commands display"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("G : Toggle graph display"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("H : Toggle lasthit display"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("I : Switch between iter display modes"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("T : Toggle text display"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("R : Reset view"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("1-2-3 : Switch fract mode"));
	mlx_string_put(vars->mlx, vars->win, WIDTH - DOFFSET, ystart += DPADDING,
		YELLOW, ft_strformat("P : Switch palette"));
}

void	renderdebug(t_state *vars)
{
	t_ivec2d	crd;
	int			ystart;

	crd = real_to_virtual(vars,
			vars->debug.lasthitreal.x, vars->debug.lasthitreal.y);
	if (vars->debug.drawgraph)
		drawgraph(vars, 5, 2);
	if (vars->debug.drawiter != 0)
		vars->function(vars, crd, vars->max_iterations, 1);
	if (vars->debug.drawlasthit)
	{
		drawcircle(vars, (t_circle){.x = crd.x, .y = crd.y,
			.rad = 15, .hollow = 0});
		drawline(vars, (t_ivec2d){.x = crd.x - 15, .y = crd.y},
			(t_ivec2d){.x = crd.x + 15, .y = crd.y}, PURPLE);
		drawline(vars, (t_ivec2d){.x = crd.x, .y = crd.y - 15},
			(t_ivec2d){.x = crd.x, .y = crd.y + 15}, PURPLE);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	if (vars->debug.drawtext)
		renderdebugtext(vars);
	if (vars->debug.drawhelp)
		renderdebughelp(vars);
	mlx_string_put(vars->mlx, vars->win, 10, 20,
		RED, "DEBUG MODE");
}
