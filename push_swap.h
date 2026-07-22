/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-alme <vde-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:37:04 by v                 #+#    #+#             */
/*   Updated: 2026/07/14 16:49:55 by vde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_stack
{
	int		*data;
	size_t	size;
	size_t	capacity;
}	t_stack;

typedef struct s_program
{
	t_stack	a;
	t_stack	b;
	double	disorder;
	int		bench_mode;
	int		strategy;
}	t_program;

/* utils_memory.c */
void	free_program(t_program *prog);
int		init_program(t_program *prog, size_t capacity);
void	exit_error(t_program *prog);

/* utils_parsing.c */
long	ft_atoi_strict(const char *str, int *error);
void	push_back_validated(t_program *prog, int num);

/* parser_main.c */
void	parse_arguments(int argc, char **argv, t_program *prog);

/* op_swap_push.c */
void	op_swap(t_stack *stack);
void	op_push(t_stack *dst, t_stack *src);

/* op_rot_revrot.c */
void	op_rotate(t_stack *stack);
void	op_reverse_rotate(t_stack *stack);

/* disorder.c */
double	compute_disorder(const int *stack_a, size_t size);

/* writer.c */
void	print_op(const char *op);
void	print_bench_metrics(t_program *prog, long total_ops, const char *strat);

/* op_wrappers.c */
void	exec_sa(t_program *prog, long *op_count);
void	exec_sb(t_program *prog, long *op_count);
void	exec_pa(t_program *prog, long *op_count);
void	exec_pb(t_program *prog, long *op_count);

/* op_wrappers_rot.c */
void	exec_ra(t_program *prog, long *op_count);
void	exec_rb(t_program *prog, long *op_count);
void	exec_rra(t_program *prog, long *op_count);
void	exec_rrb(t_program *prog, long *op_count);

/* op_wrappers_double.c */
void	exec_ss(t_program *prog, long *op_count);
void	exec_rr(t_program *prog, long *op_count);
void	exec_rrr(t_program *prog, long *op_count);

/* Algoritmos de Ordenacao Globais */
void	sort_simple(t_program *prog, long *op_count);
void	sort_medium(t_program *prog, int *sorted, long *op_count);
void	sort_complex(t_program *prog, long *op_count);
void	sort_adaptive(t_program *prog, long *op_count);

/* utils_medium.c */
void	sort_temp_array(int *arr, size_t size);
int		run_forced_medium(t_program *prog, long *op_count);

/* utils_simple.c */
void	rotate_min_to_top(t_program *prog, size_t min_idx, long *op_count);
void	sort_three(t_program *prog, long *op_count);

/* utils_split.c */
char	**ft_split(char const *s, char c);

/* bonus */

int		read_line(char *buffer, size_t max_len);
int		execute_checker_op(t_program *prog, const char *op);
void	check_result(t_program *prog);


#endif