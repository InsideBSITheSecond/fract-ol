/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:39 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/19 15:46:56 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <math.h>
#include <stdio.h>

#include "mlx.h"
#include "colors.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/get_next_line.h"


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

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			max_iterations;
	t_vec2d		virt_min;
	t_vec2d		virt_max;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
    t_ivec2d    render_size;
	t_vec2d		constant;
}				t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void 	render(t_vars *vars, t_vec2d constant);

int	create_argb(int a, int r, int g, int b);
int	get_a(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

#endif