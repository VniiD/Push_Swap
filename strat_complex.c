/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:58:26 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 13:01:10 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(size_t size)
{
	int	max_bits;

	max_bits = 0;
	while ((size >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

static void	apply_radix_shift(t_program *prog, int bit, long *op_count)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = prog->a.size;
	while (i < size)
	{
		if (((prog->a.data[0] >> bit) & 1) == 1)
			exec_ra(prog, op_count);
		else
			exec_pb(prog, op_count);
		i++;
	}
}

void	sort_complex(t_program *prog, long *op_count)
{
	int		bit;
	int		max_bits;

	max_bits = get_max_bits(prog->a.size);
	bit = 0;
	while (bit < max_bits)
	{
		apply_radix_shift(prog, bit, op_count);
		while (prog->b.size > 0)
			exec_pa(prog, op_count);
		bit++;
	}
}
