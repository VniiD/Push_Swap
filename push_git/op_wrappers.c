/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_wrappers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:52:00 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:52:36 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_sa(t_program *prog, long *op_count)
{
	op_swap(&prog->a);
	(*op_count)++;
	print_op("sa");
}

void	exec_sb(t_program *prog, long *op_count)
{
	op_swap(&prog->b);
	(*op_count)++;
	print_op("sb");
}

void	exec_pa(t_program *prog, long *op_count)
{
	op_push(&prog->a, &prog->b);
	(*op_count)++;
	print_op("pa");
}

void	exec_pb(t_program *prog, long *op_count)
{
	op_push(&prog->b, &prog->a);
	(*op_count)++;
	print_op("pb");
}
