/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:54:57 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 13:42:08 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	find_min_idx(t_stack *stack)
{
	size_t	i;
	size_t	min_idx;

	i = 1;
	min_idx = 0;
	while (i < stack->size)
	{
		if (stack->data[i] < stack->data[min_idx])
			min_idx = i;
		i++;
	}
	return (min_idx);
}

static void	rotate_min_to_top(t_program *prog, size_t min_idx, long *op_count)
{
	if (min_idx <= prog->a.size / 2)
	{
		while (min_idx > 0)
		{
			exec_ra(prog, op_count);
			min_idx--;
		}
	}
	else
	{
		while (min_idx < prog->a.size)
		{
			exec_rra(prog, op_count);
			min_idx++;
		}
	}
}

void	sort_simple(t_program *prog, long *op_count)
{
	size_t	min_idx;

	while (prog->a.size > 0)
	{
		min_idx = find_min_idx(&prog->a);
		rotate_min_to_top(prog, min_idx, op_count);
		if (prog->a.size > 0)
			exec_pb(prog, op_count);
	}
	while (prog->b.size > 0)
		exec_pa(prog, op_count);
}
