/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:42:56 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/19 19:00:14 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*renderworker(void *workerdata)
{
	t_workerData	*data;
	float			iter_cnt;
	int				color;
	t_ivec2d		iter;

	data = (t_workerData *)workerdata;
	iter = (t_ivec2d){.x = data->region.sx, .y = data->region.sy};
	while (iter.y++ < data->region.ey)
	{
		iter.x = data->region.sx;
		while (iter.x++ < data->region.ex)
		{
			iter_cnt = data->vars->function(data->vars, iter,
					data->vars->max_iterations, 0);
			color = which_colour(iter_cnt, data->vars->palette, data->vars->max_iterations);
			mlx_put_pixel(data->vars, iter.x, iter.y, color);
		}
	}
	return (0);
}
