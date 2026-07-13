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

int		read_line(char *buffer, size_t max_len);
int		execute_checker_op(t_program *prog, const char *op);
void	check_result(t_program *prog);

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

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc < 2)
		return (0);
	if (!init_program(&prog, (size_t)argc))
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
