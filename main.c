/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:14 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/18 19:15:14 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int squareWidth = 50;
int squareHeight = 50;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	makesquare(t_vars *vars, t_square square)
{
	for (int i = square.startX; i <= square.endX; i++)
	{
		for (int j = square.startY; j <= square.endY; j++)
		{
			my_mlx_pixel_put(vars, i, j, square.color);
		}
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_UP)
		vars->constant.x += 0.05;
	if (keycode == KEY_DOWN)
		vars->constant.x -= 0.05;
	if (keycode == KEY_LEFT)
		vars->constant.y -= 0.05;
	if (keycode == KEY_RIGHT)
		vars->constant.y += 0.05;

	printf("%f %f\n", vars->constant.x, vars->constant.y);
	return (0);
}

int mouse_hook(int code, t_vars *vars)
{
	(void)code;
	(void)vars;
	ft_printf("Hello from mouse_hook!\n");
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	t_square	square;

	render(vars, vars->constant);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.render_size = (t_ivec2d){.x = 500, .y = 500};
	vars.constant = (t_vec2d){.x = -0.75, .y = 0.05};

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.render_size.x, vars.render_size.y, "UwU");
	vars.img= mlx_new_image(vars.mlx, vars.render_size.x, vars.render_size.y);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);


	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
