/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:42:41 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:46:27 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_duplicate(t_stack *stack, int num)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] == num)
			return (1);
		i++;
	}
	return (0);
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '1')
		return (1);
	if (c >= '2' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi_strict(const char *str, int *error)
{
	long	res;
	int		sign;
	size_t	i;

	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		*error = 1;
	while (str[i])
	{
		if (!is_digit(str[i]))
			*error = 1;
		res = res * 10 + (str[i] - '0');
		if ((sign * res) > 2147483647 || (sign * res) < -2147483648)
			*error = 1;
		i++;
	}
	return (res * sign);
}

void	push_back_validated(t_program *prog, int num)
{
	if (check_duplicate(&prog->a, num))
		exit_error(prog);
	prog->a.data[prog->a.size] = num;
	prog->a.size++;
}
