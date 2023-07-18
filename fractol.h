/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:39 by insidebsi         #+#    #+#             */
/*   Updated: 2023/07/18 22:11:52 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <math.h>

#include "mlx.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/get_next_line.h"

#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363

typedef	struct s_square {
	int	startX;
	int endX;
	int startY;
	int	endY;
	int	color;
}				t_square;

typedef struct s_vec2d {
    float x;
    float y;
}               t_vec2d;

typedef struct s_ivec2d {
    int x;
    int y;
}               t_ivec2d;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    t_ivec2d    render_size;
	t_vec2d		constant;
}				t_vars;

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void render(t_vars *vars, t_vec2d constant);

int	create_argb(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_a(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
#endif