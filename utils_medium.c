/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_medium.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 04:45:00 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 03:54:15 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_temp_array(int *arr, size_t size)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	while (i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		i++;
	}
}

int	run_forced_medium(t_program *prog, long *op_count)
{
	int		*sorted;
	size_t	i;

	sorted = malloc(sizeof(int) * prog->a.size);
	if (!sorted)
		return (0);
	i = -1;
	while (++i < prog->a.size)
		sorted[i] = prog->a.data[i];
	sort_temp_array(sorted, prog->a.size);
	sort_medium(prog, sorted, op_count);
	free(sorted);
	return (1);
}
