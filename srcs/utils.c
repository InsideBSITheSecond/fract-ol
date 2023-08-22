/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:03:30 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/22 19:10:10 by llegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/fractol.h"

// Function to perform linear mapping using multi-point mapping
double	mappedlmap(const t_mpmapping *mapping, double input)
{
	int				i;
	t_mappingpoint	*point1;
	t_mappingpoint	*point2;

	i = 0;
	point1 = NULL;
	point2 = NULL;
	if (mapping->numpoints < 2)
		return (create_argb(0, 0, 0, 0));
	while (i < mapping->numpoints - 1)
	{
		if (input >= mapping->points[i].input
			&& input <= mapping->points[i + 1].input)
		{
			point1 = &mapping->points[i];
			point2 = &mapping->points[i + 1];
			break ;
		}
		i++;
	}
	if (!point1 || !point2)
		return (create_argb(0, 0, 0, 0));
	return (colorlinmap(point1->output, point2->output, 
			linmap(input, point1->input, point2->input, 0, 255)));
}
