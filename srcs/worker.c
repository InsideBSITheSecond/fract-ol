/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:42:56 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/20 18:53:48 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void *renderWorker(void* workerData)
{
    t_workerData *data = (t_workerData *)workerData;
    for (int y = data->region.sy; y < data->region.ey; ++y)
    {
        for (int x = data->region.sx; x < data->region.ex; ++x)
        {
            float iterations = data->vars->function(data->vars, x, y, data->vars->max_iterations);
            int color = which_colour(iterations, data->vars->palette);
            my_mlx_pixel_put(data->vars, x, y, color);
            //printf("rendered %i %i %i %i\n", data->region.sx, data->region.sy, data->region.ex, data->region.ey);
        }
    }

}