/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:58:33 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/31 16:10:37 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Draw a single point at coordinates (x, y) with the given width.
// For simplicity, you can draw a square or circle centered at (x, y)
// with the given width.

/*void	draw_line_point(t_state *vars, int x, int y, int width)
{
	t_ivec2d	ij;

	ij.x = -width / 2;
	while (ij.x++ <= width / 2)
	{
		ij.y = -width / 2;
		while (ij.y++ <= width / 2)
			if ((x + ij.x >= 0 && x + ij.x <= WIDTH)
				&& (y + ij.y >= 0 && y + ij.y <= HEIGHT))
				mlx_put_pixel(vars, x + ij.x, y + ij.y,
					create_argb(0, 127, 0, 127));
	}
}*/

/*void	drawsquare(t_state *vars, t_region region)
{
	for (int y = region.sy; y < region.ey; y++)
	{
		for (int x = region.sx; x < region.ex; x++)
		{
			if (region.hollow && ((y == region.sy || 
			y == region.ey - 1) || (x == region.sx || x == region.ex - 1)))
				mlx_put_pixel(vars, x, y, create_argb(0, 127, 0, 127));
			else if (region.hollow == 0)
				mlx_put_pixel(vars, x, y, create_argb(0, 127, 0, 127));
		}
	}
}*/

void	drawcircle(t_state *vars, t_circle circle)
{
	const double	pi = 3.1415926535;
	t_vec3d			xyi;

	xyi.z = 0;
	while (xyi.z < 360)
	{
		xyi.x = circle.rad * cos(xyi.z * pi / 180);
		xyi.y = circle.rad * sin(xyi.z * pi / 180);
		if ((circle.x + xyi.x >= 0 && circle.x + xyi.x <= WIDTH)
			&& (circle.y + xyi.y >= 0 && circle.y + xyi.y <= HEIGHT))
			mlx_put_pixel(vars, circle.x + xyi.x, circle.y + xyi.y,
				circle.color);
		xyi.z += 0.1;
	}
}

void	drawgraph_segments(t_state *vars, float i, float base, int mult)
{
	drawline(vars, real_to_virtual(vars, i * -1, base * mult),
		real_to_virtual(vars, i * -1, base * -1 * mult), RED);
	drawline(vars, real_to_virtual(vars, i, base * mult),
		real_to_virtual(vars, i, base * -1 * mult), RED);
	drawline(vars, real_to_virtual(vars, base * mult, i * -1),
		real_to_virtual(vars, base * -1 * mult, i * -1), RED);
	drawline(vars, real_to_virtual(vars, base * mult, i),
		real_to_virtual(vars, base * -1 * mult, i), RED);
}

void	drawline(t_state *vars, t_ivec2d start, t_ivec2d end,
	int color)
{
	int		pixels;
	t_vec2d	delta;
	t_vec2d	pixel;

	delta = (t_vec2d){.x = end.x - start.x, .y = end.y - start.y};
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel = (t_vec2d){.x = pixel.x = start.x, .y = pixel.y = start.y};
	while (pixels)
	{
		mlx_put_pixel(vars, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		--pixels;
	}
}

void	drawgraph(t_state *vars, int size)
{
	int		mult;
	float	base;
	int		n;
	float	i;

	base = 0.01;
	n = 0;
	i = 0.1;
	drawline(vars, real_to_virtual(vars, 0, size * -1),
		real_to_virtual(vars, 0, size), RED);
	drawline(vars, real_to_virtual(vars, size * -1, 0),
		real_to_virtual(vars, size, 0), RED);
	while (i <= size)
	{
		if (++n % 10 == 0)
			mult = 5;
		else
			mult = 1;
		drawgraph_segments(vars, i, base, mult);
		i += 0.1;
	}
}

/*void	draw_line_with_width(t_state *vars, t_ivec2d start,
		t_ivec2d end, int width)
{
	t_ivec2d	dxy;

	dxy = (t_ivec2d){.x = abs(end.x - start.x), .y = abs(end.y - start.y)};
	if (dxy.x == 0 && dxy.y == 0)
	{
		// If the start and end points are the same, draw a single point.
		draw_line_point(vars, start.x, start.y, width);
		return ;
	}
	int steep = dxy.y > dxy.x;
	if (steep)
	{
		// Swap x and y for steep lines.
		int temp = start.x;
		start.x = start.y;
		start.y = temp;

		temp = end.x;
		end.x = end.y;
		end.y = temp;
	}
	if (start.x > end.x)
	{
		// Make sure the start point is always on the left.
		t_ivec2d temp = start;
		start = end;
		end = temp;
	}

	dxy.x = abs(end.x - start.x);
	dxy.y = abs(end.y - start.y);
	
	int ystep = (start.y < end.y) ? 1 : -1;
	int error = dxy.x / 2;
	int y = start.y;

	for (int x = start.x; x <= end.x; x++) 
	{
		if (steep)
			draw_line_point(vars, y, x, width);
		else 
			draw_line_point(vars, x, y, width);

		error -= dxy.y;
		if (error < 0)
		{
			y += ystep;
			error += dxy.x;
		}
	}
}*/
