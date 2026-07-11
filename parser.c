/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:09:24 by v                 #+#    #+#             */
/*   Updated: 2026/07/09 20:48:40 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

static long long	process_digits(const char *str, 
										int *i, int sign, int *error)
{
	long long	res;

	res = 0;
	if (!ft_is_digit(str[*i]))
		*error = 1;
	while (ft_is_digit(str[*i]) && !*error)
	{
		res = res * 10 + (str[*i] - '0');
		if (sign == 1 && res > 2147483647)
			*error = 1;
		if (sign == -1 && res > 2147483648)
			*error = 1;
		(*i)++;
	}
	return (res);
}

int ft_atoi_strict(const char *str, int *error)
{
	long long	res;
	int			sign;
	int			i;

	sign = 1;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = process_digits(str, &i, sign, error);
	if (str[i] != '\0')
		*error = 1;
	return ((int)(res * sign));
}

int	check_duplicates(int *array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j< size)
		{
			if (array[i] == array[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
