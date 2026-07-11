#include "push_swap.h"

int get_stack_size(t_stack_node *head)
{
	t_stack_node	*current;
	int				size;

	if (!head)
		return (0);
	size = 1;
	current = head->next;
	while (current != head)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static int	count_inversions(t_stack_node *head, t_stack_node *current)
{
	t_stack_node	*runner;
	int				inversions;

	inversions = 0;
	runner = current->next;
	while (runner != head)
	{
		if (current->value > runner->value)
			inversions++;
		runner = runner->next;
	}
	return (inversions);
}

int	calculate_disorder_metric(t_stack_node *head)
{
	t_stack_node	*current;
	int				total_inversions;

	if (!head || head->next == head)
		return (0);
	total_inversions = 0;
	current = head;
	total_inversions += count_inversions(head, current);
	current = current->next;
	while (current != head)
	{
		total_inversions += count_inversions(head, current);
		current = current->next;
	}
	return (total_inversions);
}
