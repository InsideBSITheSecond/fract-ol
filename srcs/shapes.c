/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:58:33 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/02 18:54:51 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void draw_line_point(t_state *vars, int x, int y, int width) {
    // Draw a single point at coordinates (x, y) with the given width.
    // For simplicity, you can draw a square or circle centered at (x, y) with the given width.
    for (int i = -width / 2; i <= width / 2; i++) {
        for (int j = -width / 2; j <= width / 2; j++) {
            if ((x + i >= 0 && x + i <= WIDTH) && (y + j >= 0 && y + j <= HEIGHT))
                mlx_put_pixel(vars, x + i, y + j, create_argb(0, 127, 0, 127));
        }
    }
}

void draw_line_with_width(t_state *vars, t_ivec2d start, t_ivec2d end, int width) {
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);

    if (dx == 0 && dy == 0) {
        // If the start and end points are the same, draw a single point.
        draw_line_point(vars, start.x, start.y, width);
        return;
    }

    int steep = dy > dx;
    if (steep) {
        // Swap x and y for steep lines.
        int temp = start.x;
        start.x = start.y;
        start.y = temp;

        temp = end.x;
        end.x = end.y;
        end.y = temp;
    }

    if (start.x > end.x) {
        // Make sure the start point is always on the left.
        t_ivec2d temp = start;
        start = end;
        end = temp;
    }

    dx = abs(end.x - start.x);
    dy = abs(end.y - start.y);
    int ystep = (start.y < end.y) ? 1 : -1;

    int error = dx / 2;
    int y = start.y;

    for (int x = start.x; x <= end.x; x++) {
        if (steep) {
            draw_line_point(vars, y, x, width);
        } else {
            draw_line_point(vars, x, y, width);
        }

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void drawsquare(t_state *vars, t_region region)
{
	for (int y = region.sy; y < region.ey; y++)
	{
		for (int x = region.sx; x < region.ex; x++)
		{
			if (region.hollow && ((y == region.sy || y == region.ey - 1) || (x == region.sx || x == region.ex - 1)))
				mlx_put_pixel(vars, x, y, create_argb(0, 127, 0, 127));
			else if (region.hollow == 0)
				mlx_put_pixel(vars, x, y, create_argb(0, 127, 0, 127));
		}
	}
}

void drawcircle(t_state *vars, t_circle circle)
{
	const double pi = 3.1415926535;
	
	double x1, y1;
	for (double i = 0; i < 360; i += 0.1)
	{
		x1 = circle.rad * cos(i * pi / 180);
		y1 = circle.rad * sin(i * pi / 180);
		mlx_put_pixel(vars, circle.x + x1, circle.y + y1, create_argb(0, 127, 0, 127));
	}
}

void drawgraph(t_state *vars, int size, int chevronsize)
{        
    float   mult = 1;
    float   base = 0.01;
    int     n = 0;
    
    draw_line_with_width(vars, real_to_virtual(vars, 0, size * -1), real_to_virtual(vars, 0, size), 3);
	draw_line_with_width(vars, real_to_virtual(vars, size * -1, 0), real_to_virtual(vars, size, 0), 3);
	
    for (float i = 0.1; i <= size; i += 0.1)
    {
        if (++n % 10 == 0)
            mult = 5;
        else
            mult = 1;
        draw_line_with_width(vars, 
            real_to_virtual(vars, i * -1, base * mult), 
            real_to_virtual(vars, i * -1, base * -1 * mult), 3);
        draw_line_with_width(vars, 
            real_to_virtual(vars, i, base * mult), 
            real_to_virtual(vars, i, base * -1 * mult), 3);
        draw_line_with_width(vars, 
            real_to_virtual(vars, base * mult, i * -1), 
            real_to_virtual(vars, base * -1 * mult, i * -1), 3);
        draw_line_with_width(vars, 
            real_to_virtual(vars, base * mult, i), 
            real_to_virtual(vars, base * -1 * mult, i), 3);
    }
}