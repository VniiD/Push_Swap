#include "push_swap.h"

static int  count_smaller(t_stack_node *head, int value)
{
	t_stack_node	*runner;
	int				count;

	count = 0;
	runner = head;
	if (runner->value < value)
		count++;
	runner = runner->next;
	while (runner != head)
	{
		if (runner->value < value)
			count++;
		runner = runner->next;
	}
	return (count);
}

void	set_stack_indices(t_stack_node *head)
{
	t_stack_node	*curr;

	if (!head)
		return ;
	curr = head;
	curr->index = count_smaller(head, curr->value);
	curr = curr->next;
	while (curr != head)
	{
		curr->index = count_smaller(head, curr->value);
		curr = curr->next;
	}
}
