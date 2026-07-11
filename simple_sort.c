// simple_sort.c
#include "push_swap.h"

void	sort_three(t_stack_node **a)
{
	int	first;
	int	second;

	first = (*a)->value;
	second = (*a)->next->value;
	if (first > second && first > (*a)->prev->value)
		ra(a);
	else if (second > first && second > (*a)->prev->value)
		rra(a);
	first = (*a)->value;
	second = (*a)->next->value;
	if (first > second)
		sa(a);
}

static int	get_min_pos(t_stack_node *head, int min_val)
{
	t_stack_node	*curr;
	int				pos;

	pos = 0;
	curr = head;
	while (curr->value != min_val)
	{
		pos++;
		curr = curr->next;
	}
	return (pos);
}

static int	find_min_value(t_stack_node *head)
{
	t_stack_node	*curr;
	int				min;

	min = head->value;
	curr = head->next;
	while (curr != head)
	{
		if (curr->value < min)
			min = curr->value;
		curr = curr->next;
	}
	return (min);
}

void	sort_small(t_stack_node **a, t_stack_node **b)
{
	int	min;
	int	size;
	int	pos;

	while (get_stack_size(*a) > 3)
	{
		min = find_min_value(*a);
		size = get_stack_size(*a);
		pos = get_min_pos(*a, min);
		if (pos <= size / 2)
		{
			while ((*a)->value != min)
				ra(a);
		}
		else
		{
			while ((*a)->value != min)
				rra(a);
		}
		pb(a, b);
	}
	sort_three(a);
	while (*b)
		pa(b, a);
}