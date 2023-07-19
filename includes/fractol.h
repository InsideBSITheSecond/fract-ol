/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:39 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/19 18:06:05 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <math.h>
#include <stdio.h>

#include "mlx.h"
#include "colors.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/get_next_line.h"

#define WIDTH 500
#define HEIGHT 250

#define NUMPAD_9 65434
#define NUMPAD_8 65431
#define NUMPAD_7 65429
#define NUMPAD_6 65432
#define NUMPAD_5 65437
#define NUMPAD_4 65430
#define NUMPAD_3 65435
#define NUMPAD_2 65433
#define NUMPAD_1 65436
#define NUMPAD_0 65438
#define NUMPAD_PLUS 65451
#define NUMPAD_MINUS 65453

#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363

#define KEY_ESC 65307
#define KEY_X 120

typedef struct s_vec2d {
    double x;
    double y;
}               t_vec2d;

typedef struct s_ivec2d {
    int x;
    int y;
}               t_ivec2d;

typedef struct s_ivec3d {
	int x;
	int y;
	int z;
}				t_ivec3d;

typedef struct s_fracts {
	int			mandelbrot;
	t_vec2d		julia;
	int			burning;
}				t_fracts;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			max_iterations;
	int			palette;
	t_vec2d		virt_min;
	t_vec2d		virt_max;
	double		zoom;
	t_fracts	fract;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
    t_ivec2d    render_size;
	t_vec2d		constant;
	float		(*function)(struct s_vars *vars, int x, int y, int max_iterations);
}				t_vars;

void		my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void 		render(t_vars *vars);

int			create_argb(int a, int r, int g, int b);
int			get_a(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			which_colour(int it, int palette);

float		ft_mandelbrot_math(t_vars *vars, int x, int y, int max_iterations);

t_vec2d		virtual_to_real(t_vars *vars, int x, int y);
t_vec2d		create_vec2d(double x, double y);
t_vec2d		add_vec2d(t_vec2d a, t_vec2d b);
t_vec2d		sub_vec2d(t_vec2d a, t_vec2d b);
void		real_const_vec2d(t_vec2d *a, double c);
t_vec2d		mult_vec2d(t_vec2d a, t_vec2d b);
t_vec2d		div_vec2d(t_vec2d a, t_vec2d b);
void		sqr_vec2d(t_vec2d *a, double real_c, double img_c);
t_vec2d		power_vec2d(t_vec2d a, int n);
void		ft_zoom(int x, int y, t_vars *vars, int isplus);

#endif