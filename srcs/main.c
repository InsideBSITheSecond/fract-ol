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

#include "../includes/fractol.h"

int squareWidth = 50;
int squareHeight = 50;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("key: %i\n", keycode);
	if (keycode == KEY_LEFT)
	{
		vars->virt_min.x -= 0.15 * vars->zoom;
		vars->virt_max.x -= 0.15 * vars->zoom;;
	}
	if (keycode == KEY_RIGHT)
	{
		vars->virt_min.x += 0.15 * vars->zoom;
		vars->virt_max.x += 0.15 * vars->zoom;;
	}
	if (keycode == KEY_UP)
	{
		vars->virt_min.y -= 0.15 * vars->zoom;
		vars->virt_max.y -= 0.15 * vars->zoom;;
	}
	if (keycode == KEY_DOWN)
	{
		vars->virt_min.y += 0.15 * vars->zoom;
		vars->virt_max.y += 0.15 * vars->zoom;;
	}
	if (keycode == NUMPAD_PLUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 1);
	if (keycode == NUMPAD_MINUS)
		ft_zoom(WIDTH / 2, HEIGHT / 2, vars, 0);
	if (keycode == NUMPAD_7)
		vars->max_iterations -= 10;
	if (keycode == NUMPAD_9)
		vars->max_iterations += 10;
	if (keycode == NUMPAD_4)
		vars->fract.mandelbrot -= 1;
	if (keycode == NUMPAD_6)
		vars->fract.mandelbrot += 1;
	if (keycode == KEY_ESC || keycode == KEY_X)
		mlx_destroy_window(vars->mlx, vars->win);

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
	render(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 50, 50, YELLOW, ft_itoa(vars->max_iterations));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.render_size = (t_ivec2d){.x = WIDTH, .y = HEIGHT};
	vars.constant = (t_vec2d){.x = -0.75, .y = 0.05};
	vars.max_iterations = ft_atoi(argv[1]);
	vars.virt_min = (t_vec2d){.x = -2, .y = -2};
	vars.virt_max = (t_vec2d){.x = 2, .y = 2};
	vars.fract.mandelbrot = 2;
	vars.zoom = 1.0f;
	vars.palette = 2;
	vars.function = &ft_mandelbrot_math;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.render_size.x, vars.render_size.y, "UwU");
	vars.img= mlx_new_image(vars.mlx, vars.render_size.x, vars.render_size.y);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

	mlx_do_key_autorepeaton(vars.mlx);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
