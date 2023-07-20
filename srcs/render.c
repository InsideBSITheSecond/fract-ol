/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:49:45 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/20 19:44:43 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_zoom(int x, int y, t_state *vars, int isplus)
{
	t_vec2d    virt_pos;
	double	zoom_fact;

	if (isplus == 1)
		zoom_fact = 0.9f;
	else
		zoom_fact = 1.1f;
	if (!(vars->zoom > 1.7f && isplus == 0))
	{
		virt_pos = virtual_to_real(vars, x, HEIGHT - y);
		vars->zoom *= zoom_fact;
		vars->virt_max.x = vars->virt_max.x * zoom_fact
					+ virt_pos.x * (1 - zoom_fact);
		vars->virt_max.y = vars->virt_max.y * zoom_fact
					+ virt_pos.y * (1 - zoom_fact);
		vars->virt_min.x = vars->virt_min.x * zoom_fact
					+ virt_pos.x * (1 - zoom_fact);
		vars->virt_min.y = vars->virt_min.y * zoom_fact
					+ virt_pos.y * (1 - zoom_fact);
		render(vars);
	}
}

void	my_mlx_pixel_put(t_state *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_region* divideScreen(int screenWidth, int screenHeight, int numBlocksX, int numBlocksY) {
    int blockWidth = screenWidth / numBlocksX;
    int blockHeight = screenHeight / numBlocksY;

    t_region* blocks = (t_region*)malloc(numBlocksX * numBlocksY * sizeof(t_region));

    int i = 0;

    for (int y = 0; y < numBlocksY; y++) {
        for (int x = 0; x < numBlocksX; x++) {
            blocks[i].sx = x * blockWidth;
            blocks[i].sy = y * blockHeight;
            blocks[i].ex = (x + 1) * blockWidth;
            blocks[i].ey = (y + 1) * blockHeight;

            i++;
        }
    }

	printf("Made %i blocks of size %ix%i for %i workers\n", i, blockWidth, blockHeight, numBlocksX*numBlocksY);
    return blocks;
}

int render(t_state *vars)
{
    //float scale = 1.0f / (float)(vars->render_size.y / 2);
    if (vars->render_lock == 0)
    {
        pthread_t thread[NUM_THREADS];
        t_workerData workerData[NUM_THREADS];
        
        //Create your threads(allocation).
        for (int i = 0; i != NUM_THREADS; i++) {
            
            workerData[i].region = vars->screenBlocks[i];
            workerData[i].vars = vars;
            if (pthread_create(&thread[i], NULL, &renderWorker, (void *)&workerData[i]) != 0) {
                printf("ERROR : pthread create failed.\n");
                return (0);
            }
        }
        //Call pthread_join() for all threads (they will get free) and all threads 
        //will terminate at this position.
        for (int i = 0; i != NUM_THREADS; i++) {
            if (pthread_join(thread[i], NULL) != 0) {
                printf("ERROR : pthread join failed.\n");
                return (0);
            }
        }
        vars->render_lock = 1;
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
    mlx_string_put(vars->mlx, vars->win, 50, 50, YELLOW, ft_itoa(vars->max_iterations));
    return(0);
}