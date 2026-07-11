// push_swap.h
#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_stack_node
{
	int                  value;
	int                  index;
	struct s_stack_node  *next;
	struct s_stack_node  *prev;
}	t_stack_node;

/* Módulo de Parsing e Validação - parser.c */
int				ft_atoi_strict(const char *str, int *error);
int				check_duplicates(int *array, int size);

/* Utilitários de Stack - stack_utils.c */
t_stack_node	*create_node(int value);
void			append_node(t_stack_node **head, t_stack_node *new_node);
void			free_stack(t_stack_node **head);
int				get_stack_size(t_stack_node *head);

/* Operações Fundamentais de Ponteiros - op_swap_push.c & op_rotate.c */
void			swap(t_stack_node **head);
void			push(t_stack_node **src, t_stack_node **dst);
void			rotate(t_stack_node **head);
void			reverse_rotate(t_stack_node **head);

/* Wrappers de Exibição das Operações - op_wrappers_a.c & op_wrappers_b.c */
void			sa(t_stack_node **a);
void			ra(t_stack_node **a);
void			rra(t_stack_node **a);
void			pb(t_stack_node **a, t_stack_node **b);
void			rb(t_stack_node **b);
void			rrb(t_stack_node **b);
void			pa(t_stack_node **b, t_stack_node **a);

/* Módulo de Métrica de Desordem e Indexação - disorder_metric.c & indexer.c */
int				calculate_disorder_metric(t_stack_node *head);
void			set_stack_indices(t_stack_node *head);

/* Utilitários Matemáticos - math_utils.c */
int				ft_sqrt(int number);

/* Algoritmos de Ordenação - simple_sort.c, medium_sort.c & complex_sort.c */
void			sort_three(t_stack_node **a);
void			sort_small(t_stack_node **a, t_stack_node **b);
void			medium_sort(t_stack_node **a, t_stack_node **b);
void			complex_sort(t_stack_node **a, t_stack_node **b);

#endif