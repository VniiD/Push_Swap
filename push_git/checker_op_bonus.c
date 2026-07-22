/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_op_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:11:32 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 13:13:50 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	dispatch_rot(t_program *prog, const char *op)
{
	if (ft_strcmp(op, "ra") == 0)
		op_rotate(&prog->a);
	else if (ft_strcmp(op, "rb") == 0)
		op_rotate(&prog->b);
	else if (ft_strcmp(op, "rr") == 0)
	{
		op_rotate(&prog->a);
		op_rotate(&prog->b);
	}
	else if (ft_strcmp(op, "rra") == 0)
		op_reverse_rotate(&prog->a);
	else if (ft_strcmp(op, "rrb") == 0)
		op_reverse_rotate(&prog->b);
	else if (ft_strcmp(op, "rrr") == 0)
	{
		op_reverse_rotate(&prog->a);
		op_reverse_rotate(&prog->b);
	}
	else
		return (0);
	return (1);
}

int	execute_checker_op(t_program *prog, const char *op)
{
	if (ft_strcmp(op, "sa") == 0)
		op_swap(&prog->a);
	else if (ft_strcmp(op, "sb") == 0)
		op_swap(&prog->b);
	else if (ft_strcmp(op, "ss") == 0)
	{
		op_swap(&prog->a);
		op_swap(&prog->b);
	}
	else if (ft_strcmp(op, "pa") == 0)
		op_push(&prog->a, &prog->b);
	else if (ft_strcmp(op, "pb") == 0)
		op_push(&prog->b, &prog->a);
	else if (dispatch_rot(prog, op))
		return (1);
	else
		return (0);
	return (1);
}
