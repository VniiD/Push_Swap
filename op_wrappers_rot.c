/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_wrappers_rot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:53:07 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:53:31 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_ra(t_program *prog, long *op_count)
{
	op_rotate(&prog->a);
	(*op_count)++;
	print_op("ra");
}

void	exec_rb(t_program *prog, long *op_count)
{
	op_rotate(&prog->b);
	(*op_count)++;
	print_op("rb");
}

void	exec_rra(t_program *prog, long *op_count)
{
	op_reverse_rotate(&prog->a);
	(*op_count)++;
	print_op("rra");
}

void	exec_rrb(t_program *prog, long *op_count)
{
	op_reverse_rotate(&prog->b);
	(*op_count)++;
	print_op("rrb");
}
