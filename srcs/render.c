/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:49:45 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/27 16:42:20 by insidebsi        ###   ########.fr       */
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

int	render(t_state *vars)
{
	pthread_t		thread[NUM_THREADS];
	t_workerData	workerdata[NUM_THREADS];
	int				i;

	i = 0;
	if (vars->render_lock == 0)
	{
		vars->render_lock = 1;
		while (i != NUM_THREADS)
		{
			workerdata[i].region = vars->screenblocks[i];
			workerdata[i].vars = vars;
			if (pthread_create(&thread[i++], NULL,
					&renderworker, (void *)&workerdata[i]) != 0)
				return (printf("ERROR : pthread create failed.\n"));
		}
		i = 0;
		while (i != NUM_THREADS)
			if (pthread_join(thread[i++], NULL) != 0)
				return (printf("ERROR : pthread join failed.\n"));
		if (vars->debug.drawdebug == 1)
			renderdebug(vars);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
}
