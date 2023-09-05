/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:20:52 by insidebsi         #+#    #+#             */
/*   Updated: 2023/09/05 16:31:35 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	printfree(t_state *vars, char *str, t_ivec2d crd)
{
	mlx_string_put(vars->mlx, vars->win, crd.x, crd.y, YELLOW, str);
	free(str);
}

void	renderdebugtext(t_state *vars)
{
	int	ystart;

	ystart = 25;
	printfree(vars, ft_strformat("Threads: %i", NUM_THREADS),
		(t_ivec2d){.x = DPADDING, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("Iterations: %i", vars->max_iterations),
		(t_ivec2d){.x = DPADDING, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("Last hit: %d - %d", vars->debug.lasthitreal.x,
			vars->debug.lasthitreal.y), (t_ivec2d){.x = DPADDING,
		.y = ystart += DPADDING});
	printfree(vars, ft_strformat("Virt min: %d - %d", vars->virt_min.x,
			vars->virt_min.y), (t_ivec2d){.x = DPADDING, .y = ystart
		+= DPADDING});
	printfree(vars, ft_strformat("Virt max: %d - %d", vars->virt_max.x,
			vars->virt_max.y), (t_ivec2d){.x = DPADDING, .y = ystart
		+= DPADDING});
	printfree(vars, ft_strformat("Zoom:    %d", vars->zoom),
		(t_ivec2d){.x = DPADDING, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("0sMeter: 0.123456789abcdef"),
		(t_ivec2d){.x = DPADDING, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("Palette: %i", vars->palette),
		(t_ivec2d){.x = DPADDING, .y = ystart += DPADDING});
}

void	renderdebughelp(t_state *vars)
{
	int	ystart;

	ystart = 25;
	printfree(vars, ft_strformat("D : Toggle debug mode"), (t_ivec2d){.x = WIDTH
		- DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("? : Toggle commands display"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("G : Toggle graph display"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("H : Toggle lasthit display"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("I : Switch between iter display modes"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("T : Toggle text display"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("R : Reset view"), (t_ivec2d){.x = WIDTH
		- DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("1-2-3 : Switch fract mode"),
		(t_ivec2d){.x = WIDTH - DOFFSET, .y = ystart += DPADDING});
	printfree(vars, ft_strformat("P : Switch palette"), (t_ivec2d){.x = WIDTH
		- DOFFSET, .y = ystart += DPADDING});
}

void	renderdebug(t_state *vars)
{
	t_ivec2d	crd;

	crd = real_to_virtual(vars,
			vars->debug.lasthitreal.x,
			vars->debug.lasthitreal.y);
	if (vars->debug.drawgraph)
		drawgraph(vars, 5);
	if (vars->debug.drawiter != 0)
		vars->function(vars, crd, vars->max_iterations, 1);
	if (vars->debug.drawlasthit)
	{
		drawcircle(vars, (t_circle){.x = crd.x, .y = crd.y, .rad = 15,
			.hollow = 0});
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
	mlx_string_put(vars->mlx, vars->win, 10, 20, RED, "DEBUG MODE");
}
