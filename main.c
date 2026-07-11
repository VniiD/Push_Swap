#include "push_swap.h"

static int	is_already_sorted(t_stack_node *head)
{
	t_stack_node	*curr;

	if (!head)
		return (1);
	curr = head;
	while (curr->next != head)
	{
		if (curr->value > curr->next->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}

static void	select_sort_strategy(t_stack_node **a, t_stack_node **b)
{
	int	size;

	size = get_stack_size(*a);
	if (is_already_sorted(*a))
		return ;
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 10)
		sort_small(a, b);
	else if (size <= 100)
		medium_sort(a, b);
	else
		complex_sort(a, b);
}

static int	fill_stack_from_array(t_stack_node **a, int *array, int size)
{
	int				i;
	t_stack_node	*new_node;

	i = 0;
	while (i < size)
	{
		new_node = create_node(array[i]);
		if (!new_node)
		{
			return (0);
		}
		append_node(a, new_node);
		i++;
	}
	return (1);
}

static int	parse_to_array(char **argv, int argc, int *array)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (i < argc)
	{
		array[i - 1] = ft_atoi_strict(argv[i], &error);
		if (error)
			return (0);
		i++;
	}
	if (check_duplicates(array, argc - 1))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	int				*array;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	array = malloc(sizeof(int) * (argc - 1));
	if (!array || !parse_to_array(argv, argc, array)
		|| !fill_stack_from_array(&a, array, argc - 1))
	{
		free(array);
		free_stack(&a);
		write(2, "Error\n", 6);
		return (1);
	}
	free(array);
	select_sort_strategy(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}