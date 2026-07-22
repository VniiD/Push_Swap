/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-alme <vde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:13:20 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 16:58:57 by vde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:13:20 by v                 #+#    #+#             */
/*   Updated: 2026/07/13 13:14:29 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	read_and_execute(t_program *prog)
{
	char	buffer[16];

	while (read_line(buffer, 16))
	{
		if (buffer[0] == '\0')
			continue ;
		if (!execute_checker_op(prog, buffer))
			exit_error(prog);
	}
}

static size_t	get_safe_capacity(int argc)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		count += 4000;
	}
	if (count < 4000)
		count = 4000;
	return (count);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	size_t		capacity;

	if (argc < 2)
		return (0);
	capacity = get_safe_capacity(argc);
	if (!init_program(&prog, capacity))
		return (1);
	parse_arguments(argc, argv, &prog);
	if (prog.a.size == 0)
	{
		free_program(&prog);
		return (0);
	}
	read_and_execute(&prog);
	check_result(&prog);
	free_program(&prog);
	return (0);
}