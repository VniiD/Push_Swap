/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_wrappers_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:53:58 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:54:12 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_ss(t_program *prog, long *op_count)
{
	op_swap(&prog->a);
	op_swap(&prog->b);
	(*op_count)++;
	print_op("ss");
}

void	exec_rr(t_program *prog, long *op_count)
{
	op_rotate(&prog->a);
	op_rotate(&prog->b);
	(*op_count)++;
	print_op("rr");
}

void	exec_rrr(t_program *prog, long *op_count)
{
	op_reverse_rotate(&prog->a);
	op_reverse_rotate(&prog->b);
	(*op_count)++;
	print_op("rrr");
}
