/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:48:43 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:49:15 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_op(const char *op)
{
	size_t	len;

	len = 0;
	while (op[len])
		len++;
	write(1, op, len);
	write(1, "\n", 1);
}

static void	write_bench_num(long num)
{
	char	c;

	if (num >= 10)
		write_bench_num(num / 10);
	c = (num % 10) + '0';
	write(2, &c, 1);
}

static void	write_bench_str(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}

void	print_bench_metrics(t_program *prog, long total_ops, const char *strat)
{
	long	integer_part;
	long	fractional_part;

	write_bench_str("[bench] disorder:\n");
	integer_part = (long)(prog->disorder * 100);
	fractional_part = (long)((prog->disorder * 100 - integer_part) * 100);
	if (fractional_part < 0)
		fractional_part = -fractional_part;
	write_bench_num(integer_part);
	write_bench_str(".");
	if (fractional_part < 10)
		write_bench_str("0");
	write_bench_num(fractional_part);
	write_bench_str("%\n[bench] strategy:\n");
	write_bench_str(strat);
	write_bench_str("\n[bench] total_ops:\n");
	write_bench_num(total_ops);
	write_bench_str("\n");
}
