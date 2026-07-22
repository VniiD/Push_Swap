/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_adaptive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:02:50 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 02:06:43 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_int_array(int *array, size_t size)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	normalize_stack_a(t_program *prog, int *sorted)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < prog->a.size)
	{
		j = 0;
		while (j < prog->a.size)
		{
			if (prog->a.data[i] == sorted[j])
			{
				prog->a.data[i] = (int)j;
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	execute_regime(t_program *prog, int *sorted, long *op_count)
{
	if (prog->a.size <= 5)
		sort_simple(prog, op_count);
	else if (prog->disorder < 0.15)
		sort_medium(prog, sorted, op_count);
	else
	{
		normalize_stack_a(prog, sorted);
		sort_complex(prog, op_count);
	}
}

void	sort_adaptive(t_program *prog, long *op_count)
{
	int		*sorted;
	size_t	i;

	sorted = malloc(sizeof(int) * prog->a.size);
	if (!sorted)
		exit_error(prog);
	i = 0;
	while (i < prog->a.size)
	{
		sorted[i] = prog->a.data[i];
		i++;
	}
	sort_int_array(sorted, prog->a.size);
	prog->disorder = compute_disorder(prog->a.data, prog->a.size);
	execute_regime(prog, sorted, op_count);
	free(sorted);
}
