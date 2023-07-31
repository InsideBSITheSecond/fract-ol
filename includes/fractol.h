/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:39 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/31 17:51:06 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

# include "mlx.h"
# include "colors.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# define NUM_THREADS 1
# define WIDTH 1600
# define HEIGHT 800

typedef enum e_fractals{
	mandelbrot,
	julia,
	burning
}				t_fractals;

typedef struct s_vec2d {
	double	x;
	double	y;
}				t_vec2d;

typedef struct s_ivec2d {
	int	x;
	int	y;
}				t_ivec2d;

typedef struct s_ivec3d {
	int	x;
	int	y;
	int	z;
}				t_ivec3d;

typedef struct s_fracts {
	int			mandelbrot;
	t_vec2d		julia;
	int			burning;
}				t_fracts;

typedef struct s_region {
	int	sx;
	int	sy;
	int	ex;
	int	ey;
	int hollow;
}				t_region;

typedef struct s_circle {
	int x;
	int y;
	int rad;
	int hollow;
}				t_circle;

typedef struct	s_cross {
	int x;
	int y;
	int size;
	int space;
}				t_cross;

typedef struct s_text {
	char	*str;
	int		color;
}				t_text;

typedef struct s_debuginfo {
	int			drawdebug;
	t_region	*regions;
	t_circle	*cicles;
	t_text		*texts;
}				t_debuginfo;

typedef struct s_state {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			max_iterations;
	int			palette;
	t_vec2d		virt_min;
	t_vec2d		virt_max;
	double		zoom;
	int			render_lock;
	t_fracts	fract;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_ivec2d	render_size;
	t_vec2d		constant;
	t_region	*screenblocks;
	t_debuginfo	debug;
	float		(*function)(struct s_state *vars, int x, int y, int max_it);
}				t_state;

typedef struct s_workerData {
	t_region	region;
	t_state		*vars;
}				t_workerData;

//colors.c
int			create_argb(int a, int r, int g, int b);
//int			get_a(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			which_colour(int it, int palette);

//fractal.c
t_vec2d		mandelbrot_calc(t_fracts var, t_vec2d val, t_vec2d constant);
float		mandelbrot_math(t_state *vars, int x, int y, int max_iterations);
float		julia_math(t_state *vars, int x, int y, int max_iterations);
float		burning_ship_math(t_state *vars, int x, int y, int max_iterations);

//hooks.c
int			key_hook(int keycode, t_state *vars);
int			mouse_hook(int code, int x, int y, t_state *vars);

//math.c
t_vec2d		virtual_to_real(t_state *vars, int x, int y);
t_vec2d		create_vec2d(double x, double y);
t_vec2d		add_vec2d(t_vec2d a, t_vec2d b);
t_vec2d		sub_vec2d(t_vec2d a, t_vec2d b);
void		real_const_vec2d(t_vec2d *a, double c);
t_vec2d		mult_vec2d(t_vec2d a, t_vec2d b);
t_vec2d		div_vec2d(t_vec2d a, t_vec2d b);
void		sqr_vec2d(t_vec2d *a, double real_c, double img_c);
t_vec2d		power_vec2d(t_vec2d a, int n);

//render.c
void		ft_zoom(int x, int y, t_state *vars, int isplus);
void		my_mlx_pixel_put(t_state *vars, int x, int y, int color);
t_region	*dividescreen(int screenWidth, int screenHeight, int nbx, int nby);
int			render(t_state *vars);

//threads.c
void		*renderworker(void *workerData);

//init.c
void		init_fracts(t_state *vars);
void	switch_fract(t_state *vars, t_fractals new);

#endif
