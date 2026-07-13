/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:10:07 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 13:10:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_stack_sorted(t_stack *stack)
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

int	read_line(char *buffer, size_t max_len)
{
	size_t	i;
	ssize_t	read_bytes;
	char	c;

	i = 0;
	c = 0;
	while (i < max_len - 1)
	{
		read_bytes = read(0, &c, 1);
		if (read_bytes <= 0)
			break ;
		if (c == '\n')
			break ;
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	if (read_bytes <= 0 && i == 0)
		return (0);
	return (1);
}

void	check_result(t_program *prog)
{
	if (is_stack_sorted(&prog->a) && prog->b.size == 0)
	{
		write(1, "OK\n", 3);
	}
	else
	{
		write(1, "KO\n", 3);
	}
}
