/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-alme <vde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:44:27 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 20:48:34 by vde-alme         ###   ########.fr       */
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
	else if (ft_strcmp(arg, "--count-only") == 0)
		prog->bench_mode = 1;
	else
		return (0);
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	process_split(t_program *prog, char **split)
{
	int		j;
	int		error;
	long	num;

	j = 0;
	while (split[j])
	{
		error = 0;
		num = ft_atoi_strict(split[j], &error);
		if (error)
		{
			free_split(split);
			exit_error(prog);
		}
		push_back_validated(prog, (int)num);
		j++;
	}
}

void	parse_arguments(int argc, char **argv, t_program *prog)
{
	int		i;
	char	**split;

	i = 0;
	while (++i < argc)
	{
		if (parse_flag(argv[i], prog))
			continue ;
		split = ft_split(argv[i], ' ');
		if (!split || !split[0])
		{
			free_split(split);
			exit_error(prog);
		}
		process_split(prog, split);
		free_split(split);
	}
}
