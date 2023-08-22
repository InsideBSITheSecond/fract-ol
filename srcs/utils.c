/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:03:30 by insidebsi         #+#    #+#             */
/*   Updated: 2023/08/19 22:26:48 by insidebsi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/fractol.h"

// Function to perform linear mapping using multi-point mapping
double mappedlmap(const t_mpmapping *mapping, double input) {
    if (mapping->numPoints < 2)
        return 0.0;

    // Find the two nearest points for interpolation
    t_mappingpoint *point1 = NULL;
    t_mappingpoint *point2 = NULL;

    for (int i = 0; i < mapping->numPoints - 1; ++i) {
        if (input >= mapping->points[i].input && input <= mapping->points[i + 1].input) {
            point1 = &mapping->points[i];
            point2 = &mapping->points[i + 1];
            break;
        }
    }

    if (!point1 || !point2) {
        //fprintf(stderr, "Input value is outside the mapping range: %.2f\n", input);
        return (create_argb(0, 0, 0, 0)); // Return a default value or handle the error as needed
    }

    // Linear interpolation
    double shift = linmap(input, point1->input, point2->input, 0, 255);
    //double output = point1->output + shift * (input - point1->input);
	//printf("%.2f\n", shift);
	int res = colorlinmap(point1->output, point2->output, shift);
    return res;
}

/*int main() {
    // Define the multi-point mapping


    // Test the linear mapping function
	for (double i = 0.1; i <= 2.0; i += 0.1)
	{
		int output = ;
		//printf("%i\n%i\n%i\n", get_r(points[2].output), get_g(points[2].output), get_b(points[2].output));
		printf("Input: %.2f, Output: %i, %i, %i\n", i, get_r(output), get_g(output), get_b(output));
	}

    return 0;
}*/