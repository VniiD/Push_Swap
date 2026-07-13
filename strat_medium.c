/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_medium.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:56:52 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 14:35:35 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	ft_sqrt(size_t n)
{
	size_t	res;

	res = 1;
	while (res * res <= n)
		res++;
	return (res - 1);
}

static size_t	find_max_idx(t_stack *stack)
{
	size_t	i;
	size_t	max_idx;

	i = 1;
	max_idx = 0;
	while (i < stack->size)
	{
		if (stack->data[i] > stack->data[max_idx])
			max_idx = i;
		i++;
	}
	return (max_idx);
}

static void	push_chunk_to_b(t_program *prog, int *sorted, long *op_count)
{
	size_t	c_size;
	size_t	total_size;
	size_t	limit_idx;

	c_size = ft_sqrt(prog->a.size);
	total_size = prog->a.size;
	while (prog->a.size > 0)
	{
		limit_idx = prog->b.size + c_size;
		if (limit_idx >= total_size)
			limit_idx = total_size - 1;
		if (prog->a.data[0] <= sorted[limit_idx])
		{
			exec_pb(prog, op_count);
			if (prog->b.size > 1 && prog->b.data[0] < sorted[prog->b.size - 1])
				exec_rb(prog, op_count);
		}
		else
			exec_ra(prog, op_count);
	}
}

void	sort_medium(t_program *prog, int *sorted, long *op_count)
{
	size_t	max_idx;

	(void)sorted;
	push_chunk_to_b(prog, sorted, op_count);
	while (prog->b.size > 0)
	{
		max_idx = find_max_idx(&prog->b);
		if (max_idx <= prog->b.size / 2)
		{
			while (max_idx > 0)
			{
				exec_rb(prog, op_count);
				max_idx--;
			}
		}
		else
		{
			while (max_idx < prog->b.size)
			{
				exec_rrb(prog, op_count);
				max_idx++;
			}
		}
		exec_pa(prog, op_count);
	}
}
