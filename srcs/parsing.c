/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:18:48 by llegrand          #+#    #+#             */
/*   Updated: 2023/09/09 16:18:48 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	parse(int argc, char **argv, t_state *vars)
{
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "mandelbrot") == 0)
			switch_fract(vars, mandelbrot);
		else if (ft_strcmp(argv[1], "julia") == 0)
			switch_fract(vars, julia);
		else if (ft_strcmp(argv[1], "burningship") == 0)
			switch_fract(vars, burning);
		else if (ft_strcmp(argv[1], "black") == 0)
			switch_fract(vars, black);
		else
			suicide(vars, "please provide a valid set: \
			[mandelbrot/julia/burningship/black]");
	}
	else
		suicide(vars, "please provide a valid set: \
		[mandelbrot/julia/burningship/black]");
}
