/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:01:23 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 03:24:50 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	find_target_in_a(t_stack *a, int val_b)
{
	size_t	i;
	size_t	target_idx;
	long	diff;
	long	min_diff;

	target_idx = 0;
	min_diff = 9223372036854775807L;
	i = -1;
	while (++i < a->size)
	{
		diff = (long)a->data[i] - val_b;
		if (diff > 0 && diff < min_diff)
		{
			min_diff = diff;
			target_idx = i;
		}
	}
	if (min_diff != 9223372036854775807L)
		return (target_idx);
	i = 0;
	while (++i < a->size)
		if (a->data[i] < a->data[target_idx])
			target_idx = i;
	return (target_idx);
}

static int	get_abs_cost(int cost_a, int cost_b)
{
	int	abs_a;
	int	abs_b;

	abs_a = cost_a;
	if (cost_a < 0)
		abs_a = -cost_a;
	abs_b = cost_b;
	if (cost_b < 0)
		abs_b = -cost_b;
	if (cost_a >= 0 && cost_b >= 0)
	{
		if (cost_a > cost_b)
			return (cost_a);
		return (cost_b);
	}
	if (cost_a < 0 && cost_b < 0)
	{
		if (abs_a > abs_b)
			return (abs_a);
		return (abs_b);
	}
	return (abs_a + abs_b);
}

static void	get_best_move(t_program *prog, int *best_a, int *best_b)
{
	size_t	i;
	int		c_a;
	int		c_b;
	int		total;

	*best_a = 0;
	*best_b = 2147483647;
	i = -1;
	while (++i < prog->b.size)
	{
		c_a = (int)find_target_in_a(&prog->a, prog->b.data[i]);
		if ((size_t)c_a > prog->a.size / 2)
			c_a = -((int)(prog->a.size - (size_t)c_a));
		c_b = (int)i;
		if (i > prog->b.size / 2)
			c_b = -((int)(prog->b.size - i));
		total = get_abs_cost(c_a, c_b);
		if (total < get_abs_cost(*best_a, *best_b))
		{
			*best_a = c_a;
			*best_b = c_b;
		}
	}
}

static void	exec_rotations(t_program *prog, int cost_a, int cost_b, long *ops)
{
	while (cost_a > 0 && cost_b > 0 && cost_a-- && cost_b--)
		exec_rr(prog, ops);
	while (cost_a < 0 && cost_b < 0 && cost_a++ && cost_b++)
		exec_rrr(prog, ops);
	while (cost_a > 0 && cost_a--)
		exec_ra(prog, ops);
	while (cost_a < 0 && cost_a++)
		exec_rra(prog, ops);
	while (cost_b > 0 && cost_b--)
		exec_rb(prog, ops);
	while (cost_b < 0 && cost_b++)
		exec_rrb(prog, ops);
}

void	sort_complex(t_program *prog, long *op_count)
{
	int		best_b;
	int		best_a;
	size_t	i;

	while (prog->a.size > 3)
		exec_pb(prog, op_count);
	sort_simple(prog, op_count);
	while (prog->b.size > 0)
	{
		get_best_move(prog, &best_a, &best_b);
		exec_rotations(prog, best_a, best_b, op_count);
		exec_pa(prog, op_count);
	}
	i = 0;
	best_a = 0;
	while (++i < prog->a.size)
		if (prog->a.data[i] < prog->a.data[best_a])
			best_a = (int)i;
	best_b = best_a;
	if ((size_t)best_a > prog->a.size / 2)
		best_b = -((int)(prog->a.size - best_a));
	exec_rotations(prog, best_b, 0, op_count);
}
