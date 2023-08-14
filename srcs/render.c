/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:49:45 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/14 18:35:52 by llegrand         ###   ########.fr       */
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

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	renderdebug(t_state *vars)
{
	t_ivec2d	crd;

	if (vars->debug.drawgraph)
		drawgraph(vars, 5, 2);
	if (vars->debug.drawiter)
		vars->function(vars, crd.x, crd.y, vars->max_iterations, 1);
	if (vars->debug.drawlasthit)
	{	
		crd = real_to_virtual(vars, vars->debug.lasthitreal.x, vars->debug.lasthitreal.y);
		drawcircle(vars, (t_circle){.x = crd.x, .y = crd.y, .rad = 15, .hollow = 0});
		draw_line_with_width(vars, (t_ivec2d){.x = crd.x - 15, .y = crd.y}, (t_ivec2d){.x = crd.x + 15, .y = crd.y}, 3);
		draw_line_with_width(vars, (t_ivec2d){.x = crd.x, .y = crd.y - 15}, (t_ivec2d){.x = crd.x, .y = crd.y + 15}, 3);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	if (vars->debug.drawtext)
	{
		mlx_string_put(vars->mlx, vars->win, 50, 50,
			YELLOW, ft_strformat("Iterations: %i", vars->max_iterations));
		mlx_string_put(vars->mlx, vars->win, 50, 60,
			YELLOW, ft_strformat("Last hit: %i - %i", vars->debug.lasthitreal.x, vars->debug.lasthitreal.y));
		mlx_string_put(vars->mlx, vars->win, 50, 70,
			YELLOW, ft_strformat("Virt min: %i - %i", vars->virt_min.x, vars->virt_min.y));
		mlx_string_put(vars->mlx, vars->win, 50, 80,
			YELLOW, ft_strformat("Virt max: %i - %i", vars->virt_max.x, vars->virt_max.y));
	}
	mlx_string_put(vars->mlx, vars->win, 35, 35,
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
			{
				printf("ERROR : pthread create failed.\n");
				return (0);
			}
		}
		for (int i = 0; i != NUM_THREADS; i++)
		{
			if (pthread_join(thread[i], NULL) != 0)
			{
				printf("ERROR : pthread join failed.\n");
				return (0);
			}
		}
		if (vars->debug.drawdebug == 1)
			renderdebug(vars);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	return (0);
}
