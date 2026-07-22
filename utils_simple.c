/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 05:48:00 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 05:00:20 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_min_to_top(t_program *prog, size_t min_idx, long *op_count)
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
