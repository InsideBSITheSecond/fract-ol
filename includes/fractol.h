/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:15:39 by insidebsi         #+#    #+#             */
/*   Updated: 2023/09/09 23:06:00 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "colors.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef NUM_THREADS
#  define NUM_THREADS 1
# endif
# define WIDTH 1024
# define HEIGHT 1024
//# define WIDTH 840
//# define HEIGHT 840

# define DPADDING 15
# define DOFFSET 300

typedef enum e_fractals
{
	mandelbrot,
	julia,
	burning,
	black
}					t_fractals;

typedef struct s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct s_ivec2d
{
	int				x;
	int				y;
}					t_ivec2d;

typedef struct s_vec3d
{
	double			x;
	double			y;
	double			z;
}					t_vec3d;

typedef struct s_ivec3d
{
	int				x;
	int				y;
	int				z;
}					t_ivec3d;

typedef struct s_fracts
{
	int				mandelbrot;
	t_vec2d			julia;
	int				burning;
}					t_fracts;

typedef struct s_region
{
	int				sx;
	int				sy;
	int				ex;
	int				ey;
	int				hollow;
}					t_region;

typedef struct s_circle
{
	int				x;
	int				y;
	int				rad;
	int				hollow;
	int				color;
}					t_circle;

typedef struct s_cross
{
	int				x;
	int				y;
	int				size;
	int				space;
}					t_cross;

typedef struct s_text
{
	char			*str;
	int				color;
}					t_text;

typedef struct s_debuginfo
{
	int				drawdebug;
	int				drawtext;
	int				drawiter;
	int				drawgraph;
	int				drawlasthit;
	int				drawhelp;
	t_vec2d			lasthitreal;
	t_vec2d			lhvmax;
	t_vec2d			lhvmin;
}					t_debuginfo;

typedef struct s_mappingpoint
{
	double			input;
	int				output;
}					t_mappingpoint;

typedef struct s_mpmapping
{
	int				numpoints;
	t_mappingpoint	*points;
}					t_mpmapping;

typedef struct s_state
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	t_mpmapping		*pal;
	int				max_iterations;
	int				palette;
	t_vec2d			virt_min;
	t_vec2d			virt_max;
	double			zoom;
	int				render_lock;
	t_fracts		fract;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_ivec2d		render_size;
	t_vec2d			constant;
	t_region		*screenblocks;
	t_debuginfo		debug;
	float			(*function)(struct s_state *vars,
			t_ivec2d vector,
			int max_it,
			int dc);
}					t_state;

typedef struct s_workerData
{
	t_region		region;
	t_state			*vars;
}					t_workerData;

t_mappingpoint		*getpalette1(void);
t_mappingpoint		*getpalette2(void);
void				parse(int argc, char **argv, t_state *vars);
int					create_argb(int a, int r, int g, int b);
//int				get_a(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					which_colour(int it, int palette, int max_it);
t_vec2d				vec2d_pow_add(t_fracts var, t_vec2d val, t_vec2d constant);
float				mandelbrot_math(t_state *vars, t_ivec2d vector,
						int max_iterations, int displaychain);
float				julia_math(t_state *vars, t_ivec2d vector,
						int max_iterations, int displaychain);
float				burning_ship_math(t_state *vars, t_ivec2d vector,
						int max_iterations, int displaychain);
float				empty(t_state *vars, t_ivec2d vector,
						int max_iterations, int displaychain);
int					key_hook(int keycode, t_state *vars);
int					mouse_hook(int code, int x, int y, t_state *vars);
int					suicide(t_state *vars, char *reason);
void				consoleprint(t_state *vars);
t_vec2d				virtual_to_real(t_state *vars, int x, int y);
t_vec2d				virtual_to_real2(t_vec2d virt_min, t_vec2d virt_max, int x,
						int y);
t_ivec2d			real_to_virtual(t_state *vars, float x, float y);
t_ivec2d			real_to_virtual2(t_vec2d virt_min,
						t_vec2d virt_max,
						float x,
						float y);
t_vec2d				create_vec2d(double x, double y);
t_vec2d				add_vec2d(t_vec2d a, t_vec2d b);
t_vec2d				sub_vec2d(t_vec2d a, t_vec2d b);
void				real_const_vec2d(t_vec2d *a, double c);
t_vec2d				mult_vec2d(t_vec2d a, t_vec2d b);
t_vec2d				div_vec2d(t_vec2d a, t_vec2d b);
void				sqr_vec2d(t_vec2d *a, double real_c, double img_c);
t_vec2d				power_vec2d(t_vec2d a, int n);
void				ft_zoom(int x, int y, t_state *vars, int isplus);
void				mlx_put_pixel(t_state *vars, int x, int y, int color);
t_region			*dividescreen(int screenWidth, int screenHeight, int nbx,
						int nby);
int					renderpoolmanager(t_state *vars);
void				*renderworker(void *workerData);
void				init_system(t_state *vars, int max_iterations);
void				switch_fract(t_state *vars, t_fractals new);
void				draw_line_with_width(t_state *vars, t_ivec2d start,
						t_ivec2d end, int width);
void				drawsquare(t_state *vars, t_region region);
void				drawcircle(t_state *vars, t_circle circle);
void				drawgraph(t_state *vars, int size);
void				drawline(t_state *vars, t_ivec2d start, t_ivec2d end,
						int color);
void				kb_movement(int keycode, t_state *vars);
void				kb_modifiers(int keycode, t_state *vars);
void				kb_debugmode(int keycode, t_state *vars);
void				kb_misc(int keycode, t_state *vars);
void				renderdebug(t_state *vars);
double				linmap(double val, t_vec2d range1, t_vec2d range2);
int					colorlinmap(int a, int b, float ratio);
double				mappedlmap(const t_mpmapping *mapping, double input);
char				*gettitle(void);

#endif
