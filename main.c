/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:06:43 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 14:08:26 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_already_sorted(t_stack *stack)
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

static void	execute_forced_strategy(t_program *prog, long *op_count)
{
	if (prog->strategy == 1)
	{
		sort_simple(prog, op_count);
		if (prog->bench_mode)
			print_bench_metrics(prog, *op_count, "Forced / O(n^2)");
	}
	else if (prog->strategy == 3)
	{
		sort_complex(prog, op_count);
		if (prog->bench_mode)
			print_bench_metrics(prog, *op_count, "Forced / O(n log n)");
	}
	else
	{
		sort_adaptive(prog, op_count);
	}
}

int	main(int argc, char **argv)
{
	t_program	prog;
	long		op_count;

	if (argc < 2)
		return (0);
	op_count = 0;
	if (!init_program(&prog, (size_t)argc))
		return (1);
	parse_arguments(argc, argv, &prog);
	if (prog.a.size == 0)
	{
		free_program(&prog);
		return (0);
	}
	if (is_already_sorted(&prog.a))
	{
		free_program(&prog);
		return (0);
	}
	execute_forced_strategy(&prog, &op_count);
	free_program(&prog);
	return (0);
}
