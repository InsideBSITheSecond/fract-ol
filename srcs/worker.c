/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:42:56 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/26 16:57:40 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*renderworker(void *workerdata)
{
	t_workerData	*data;
	float			iterations;
	int				color;

	data = (t_workerData *)workerdata;
	for (int y = data->region.sy; y < data->region.ey; ++y)
	{
		for (int x = data->region.sx; x < data->region.ex; ++x)
		{
			iterations = data->vars->function(data->vars, x, y,
					data->vars->max_iterations);
			color = which_colour(iterations, data->vars->palette);
			my_mlx_pixel_put(data->vars, x, y, color);
			//printf("rendered %i %i %i %i\n", data->region.sx, data->region.sy, data->region.ex, data->region.ey);
		}
	}
	return (0);
}
