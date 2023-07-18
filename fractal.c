/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:14:24 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/18 22:12:20 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vec2d computeNext(t_vec2d current, t_vec2d constant)
{
    float zr;
    float zi;

    zr = current.x * current.x - current.y * current.y;
    zi = 2.0 * current.x * current .y;

    return (t_vec2d){.x = zr + constant.x, .y = zi+ constant.y};
}

float mod2(t_vec2d z)
{
    return z.x * z.x + z.y * z.y;
}

int computeIterations(t_vec2d z0, t_vec2d constant, int max_iterations)
{
    t_vec2d zn = z0;
    int iteration = 0;
    
    while (mod2(zn) < 4.0 && iteration < max_iterations)
    {
        zn = computeNext(zn, constant);
        iteration++;
    }
    return iteration;
}

float computeIterationsSmooth(t_vec2d z0, t_vec2d constant, int max_iterations)
{
    t_vec2d zn = z0;
    int iteration = 0;
    
    while (mod2(zn) < 4.0 && iteration < max_iterations)
    {
        zn = computeNext(zn, constant);
        iteration++;
    }
    float mod = sqrt(mod2(zn));
    float smooth_iteration = (float)iteration - log2(fmax(1.0f, log2(mod)));
    return smooth_iteration;
}

double linmap(double val, double lower1, double upper1, double lower2, double upper2) {
  return ((val - lower1) / (upper1 - lower1)) * (upper2 - lower2) + lower2;
}

void render(t_vars *vars, t_vec2d constant)
{
    float scale = 1.0f / (float)(vars->render_size.y / 2);

    for (int y = 0; y < vars->render_size.y; ++y)
    {
        for (int x = 0; x < vars->render_size.x; ++x)
        {
            float px = (float)(x - vars->render_size.x / 2) * scale;
            float py = (float)(y - vars->render_size.y / 2) * scale;

            float iterations = computeIterationsSmooth((t_vec2d){.x = px, .y = py}, constant, 255);
            //ft_printf("%i ", map);
            my_mlx_pixel_put(vars, x, y, create_argb(0, iterations, iterations, iterations));
        }
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
    }
}