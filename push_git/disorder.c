/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:47:12 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:48:05 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(const int *stack_a, size_t size)
{
	size_t	i;
	size_t	j;
	double	mistakes;
	double	total_pairs;

	if (size < 2)
		return (0.0);
	mistakes = 0.0;
	total_pairs = 0.0;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			total_pairs += 1.0;
			if (stack_a[i] > stack_a[j])
				mistakes += 1.0;
			j++;
		}
		i++;
	}
	return (mistakes / total_pairs);
}
