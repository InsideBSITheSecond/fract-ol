/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:49:45 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/31 17:54:33 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void squareZone(t_state *vars, t_region region)
{
	for (int y = region.sy; y < region.ey; y++)
	{
		for (int x = region.sx; x < region.ex; x++)
		{
			if (region.hollow && ((y == region.sy || y == region.ey - 1) || (x == region.sx || x == region.ex - 1)))
					my_mlx_pixel_put(vars, x, y, create_argb(0, 127, 0, 127));
			else if (region.hollow == 0)
				my_mlx_pixel_put(vars, x, y, create_argb(0, 127, 0, 127));
		}
	}
}

void circleZone(t_state *vars, t_circle circle)
{
	const double pi = 3.1415926535;
	
	double x1, y1;
	for (double i = 0; i < 360; i += 0.1)
	{
		x1 = circle.rad * cos(i * pi / 180);
		y1 = circle.rad * sin(i * pi / 180);
		my_mlx_pixel_put(vars, circle.x + x1, circle.y + y1, create_argb(0, 127, 0, 127));
	}
}

void	ft_zoom(int x, int y, t_state *vars, int isplus)
{
	t_vec2d	virt_pos;
	double	zoom_fact;

	//ft_printf("%i - %i | %i\n", x, y, isplus);
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
	vars->debug.drawdebug = 1;
	render(vars);
}

void	my_mlx_pixel_put(t_state *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_region	*dividescreen(int screenwidth, int screenheight, int nbx, int nby)
{
	t_ivec2d	blocksize;
	t_region	*blocks;
	int			i;

	blocksize = (t_ivec2d){.x = screenwidth / nbx, .y = screenheight / nby};
	blocks = (t_region *)malloc(nbx * nby * sizeof(t_region));
	i = 0;
	for (int y = 0; y < nby; y++)
	{
		for (int x = 0; x < nbx; x++)
		{
			blocks[i].sx = x * blocksize.x;
			blocks[i].sy = y * blocksize.y;
			blocks[i].ex = (x + 1) * blocksize.x;
			blocks[i].ey = (y + 1) * blocksize.y;
			i++;
		}
	}
	printf("Made %i blocks of size %ix%i for %i workers\n", i, blocksize.x,
		blocksize.y, nbx * nby);
	return (blocks);
}

void	renderdebug(t_state *vars)
{
	squareZone(vars, (t_region){.sx = 15, .sy = 15, .ex = 50, .ey = 50, .hollow = 1});
	circleZone(vars, (t_circle){.x = WIDTH / 2, .y = HEIGHT / 2, .rad = 125});
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

	// text after img
	mlx_string_put(vars->mlx, vars->win, 50, 50,
		YELLOW, ft_strjoin("Iterations: ", (char *)ft_itoa(vars->max_iterations)));
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
