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

#include "includes/fractol.h"

int	main(int argc, char **argv)
{
	(void)argc;
	t_state	vars;

	if (round(sqrt(NUM_THREADS)) != sqrt(NUM_THREADS))
		return(printf("sqrt(NUM_THREADS) must be an integer"));
	if(round(WIDTH / sqrt(NUM_THREADS)) != WIDTH / sqrt(NUM_THREADS))
		return(printf("WIDTH must be dividable by round(sqrt(NUM_THREADS))"));
	if(round(HEIGHT / sqrt(NUM_THREADS)) != HEIGHT / sqrt(NUM_THREADS))
		return(printf("HEIGHT must be dividable by round(sqrt(NUM_THREADS))"));
	init_system(&vars, atoi(argv[1]));
	switch_fract(&vars, julia);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render, &vars);
	mlx_loop(vars.mlx);
}
