/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:40:14 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:43:13 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_program(t_program *prog)
{
	if (prog->a.data)
	{
		free(prog->a.data);
		prog->a.data = NULL;
	}
	if (prog->b.data)
	{
		free(prog->b.data);
		prog->b.data = NULL;
	}
}

int	init_program(t_program *prog, size_t capacity)
{
	prog->a.data = malloc(sizeof(int) * capacity);
	if (!prog->a.data)
		return (0);
	prog->b.data = malloc(sizeof(int) * capacity);
	if (!prog->b.data)
	{
		free(prog->a.data);
		prog->a.data = NULL;
		return (0);
	}
	prog->a.size = 0;
	prog->a.capacity = capacity;
	prog->b.size = 0;
	prog->b.capacity = capacity;
	prog->bench_mode = 0;
	prog->strategy = 0;
	prog->disorder = 0.0;
	return (1);
}

void	exit_error(t_program *prog)
{
	free_program(prog);
	write(2, "Error\n", 6);
	exit(1);
}
