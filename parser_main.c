/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:44:27 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 12:46:17 by v                ###   ########.fr       */
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

static int	parse_flag(const char *arg, t_program *prog)
{
	if (ft_strcmp(arg, "--simple") == 0)
		prog->strategy = 1;
	else if (ft_strcmp(arg, "--medium") == 0)
		prog->strategy = 2;
	else if (ft_strcmp(arg, "--complex") == 0)
		prog->strategy = 3;
	else if (ft_strcmp(arg, "--adaptive") == 0)
		prog->strategy = 4;
	else if (ft_strcmp(arg, "--bench") == 0)
		prog->bench_mode = 1;
	else
		return (0);
	return (1);
}

void	parse_arguments(int argc, char **argv, t_program *prog)
{
	int		i;
	int		error;
	long	num;

	i = 1;
	error = 0;
	while (i < argc)
	{
		if (parse_flag(argv[i], prog))
		{
			i++;
			continue ;
		}
		num = ft_atoi_strict(argv[i], &error);
		if (error)
			exit_error(prog);
		push_back_validated(prog, (int)num);
		i++;
	}
}
