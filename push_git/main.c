/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-alme <vde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:06:43 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 21:08:39 by vde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

extern int bench_silence;

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

static void	select_strategy(t_program *prog, long *op_count)
{
	if (prog->a.size <= 5)
		sort_simple(prog, op_count);
	else if (prog->strategy == 1)
	{
		if (prog->a.size <= 10)
			sort_simple(prog, op_count);
		else if (!run_forced_medium(prog, op_count))
			exit_error(prog);
	}
	else if (prog->strategy == 2)
	{
		if (!run_forced_medium(prog, op_count))
			exit_error(prog);
	}
	else if (prog->strategy == 3)
		sort_complex(prog, op_count);
	else
		sort_adaptive(prog, op_count);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	long		op_count;
	const char	*m;

	if (argc < 2 || !init_program(&prog, (size_t)argc))
		return (argc < 2 ? 0 : 1);
	op_count = 0;
	parse_arguments(argc, argv, &prog);
	prog.disorder = compute_disorder(prog.a.data, prog.a.size);
	if (prog.a.size == 0 || is_already_sorted(&prog.a))
		prog.disorder = 0.0;
	else
		select_strategy(&prog, &op_count);
	m = "adaptive";
	if (prog.strategy == 1)
		m = "simple";
	else if (prog.strategy == 2)
		m = "medium";
	else if (prog.strategy == 3)
		m = "complex";
	if (prog.bench_mode)
		print_bench_metrics(&prog, op_count, m);
	free_program(&prog);
	return (0);
}
