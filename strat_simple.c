/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:54:57 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 05:00:02 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted_local(t_stack *stack)
{
	size_t	i;

	if (stack->size < 2)
		return (1);
	i = 0;
	while (i < stack->size - 1)
	{
		if (stack->data[i] > stack->data[i + 1])
			return (0);
		i++;
	}
	return (1);
}

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

void	sort_three(t_program *prog, long *op_count)
{
	int	a;
	int	b;
	int	c;

	a = prog->a.data[0];
	b = prog->a.data[1];
	c = prog->a.data[2];
	if (a > b && b < c && a < c)
		exec_sa(prog, op_count);
	else if (a > b && b > c)
	{
		exec_sa(prog, op_count);
		exec_rra(prog, op_count);
	}
	else if (a > b && b < c && a > c)
		exec_ra(prog, op_count);
	else if (a < b && b > c && a < c)
	{
		exec_sa(prog, op_count);
		exec_ra(prog, op_count);
	}
	else if (a < b && b > c && a > c)
		exec_rra(prog, op_count);
}

void	sort_simple(t_program *prog, long *op_count)
{
	size_t	min_idx;

	if (prog->a.size == 2 && prog->a.data[0] > prog->a.data[1])
		exec_sa(prog, op_count);
	if (prog->a.size <= 3)
	{
		if (prog->a.size == 3 && !is_sorted_local(&prog->a))
			sort_three(prog, op_count);
		return ;
	}
	while (prog->a.size > 3 && !is_sorted_local(&prog->a))
	{
		min_idx = find_min_idx(&prog->a);
		rotate_min_to_top(prog, min_idx, op_count);
		if (!is_sorted_local(&prog->a))
			exec_pb(prog, op_count);
	}
	if (prog->a.size == 3 && !is_sorted_local(&prog->a))
		sort_three(prog, op_count);
	while (prog->b.size > 0)
		exec_pa(prog, op_count);
}
