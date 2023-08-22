/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:49:45 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/22 15:50:13 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_zoom(int x, int y, t_state *vars, int isplus)
{
	t_vec2d	virt_pos;
	double	zoom_fact;

	if (isplus == 1)
		zoom_fact = 0.9f;
	else
		zoom_fact = 1.1f;
	if (!(vars->zoom > 1.7f && isplus == 0))
	{
		virt_pos = virtual_to_real(vars, x, y);
		vars->zoom *= zoom_fact;
		vars->virt_max.x = vars->virt_max.x * zoom_fact
			+ virt_pos.x * (1 - zoom_fact);
		vars->virt_max.y = vars->virt_max.y * zoom_fact
			+ virt_pos.y * (1 - zoom_fact);
		vars->virt_min.x = vars->virt_min.x * zoom_fact
			+ virt_pos.x * (1 - zoom_fact);
		vars->virt_min.y = vars->virt_min.y * zoom_fact
			+ virt_pos.y * (1 - zoom_fact);
	}
	render(vars);
}

void	mlx_put_pixel(t_state *vars, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < WIDTH)
	{
		if (y > 0 && y < HEIGHT)
		{
			dst = vars->addr
				+ (y * vars->line_length + x * (vars->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

t_region	*dividescreen(int screenwidth, int screenheight, int nbx, int nby)
{
	t_ivec2d	blocksize;
	t_ivec2d	iter;
	t_region	*blocks;
	int			i;

	iter = (t_ivec2d){.x = 0, .y = 0};
	blocksize = (t_ivec2d){.x = screenwidth / nbx, .y = screenheight / nby};
	blocks = (t_region *)malloc(nbx * nby * sizeof(t_region));
	i = 0;
	while (iter.y < nby)
	{
		while (iter.x < nbx)
		{
			blocks[i].sx = iter.x * blocksize.x;
			blocks[i].sy = iter.y * blocksize.y;
			blocks[i].ex = (iter.x + 1) * blocksize.x;
			blocks[i].ey = (iter.y + 1) * blocksize.y;
			i++;
			iter.x++;
		}
		iter.y++;
		iter.x = 0;
	}
	printf("%iB(%ix%i) -> %iW\n", i, blocksize.x, blocksize.y, nbx * nby);
	return (blocks);
}

void	renderdebugtext(t_state *vars)
{
	int	ystart;

	ystart = 25;
	mlx_string_put(vars->mlx, vars->win, DPADDING, ystart += DPADDING,
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
			vars->palette));
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
			(t_ivec2d){.x = crd.x + 15, .y = crd.y}, PURPLE, 3);
		drawline(vars, (t_ivec2d){.x = crd.x, .y = crd.y - 15},
			(t_ivec2d){.x = crd.x, .y = crd.y + 15}, PURPLE, 3);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	if (vars->debug.drawtext)
		renderdebugtext(vars);
	if (vars->debug.drawhelp)
		renderdebughelp(vars);
	mlx_string_put(vars->mlx, vars->win, 10, 20,
		RED, "DEBUG MODE");
}

int	render(t_state *vars)
{
	pthread_t		thread[NUM_THREADS];
	t_workerData	workerdata[NUM_THREADS];

	if (vars->render_lock == 0)
	{
		vars->render_lock = 1;
		ft_printf("render requested\n");
		for (int i = 0; i != NUM_THREADS; i++)
		{
			workerdata[i].region = vars->screenblocks[i];
			workerdata[i].vars = vars;
			if (pthread_create(&thread[i], NULL,
					&renderworker, (void *)&workerdata[i]) != 0)
				return (printf("ERROR : pthread create failed.\n"));
		}
		for (int i = 0; i != NUM_THREADS; i++)
			if (pthread_join(thread[i], NULL) != 0)
				return (printf("ERROR : pthread join failed.\n"));
		if (vars->debug.drawdebug == 1)
			renderdebug(vars);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	return (0);
}
