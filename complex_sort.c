#include "push_swap.h"

static void	push_complex_chunks(t_stack_node **a, t_stack_node **b, int size)
{
	int	chunk_size;
	int	i;

	chunk_size = ft_sqrt(size) * 25 / 10;
	i = 0;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			pb(a, b);
			rb(b);
			i++;
		}
		else if ((*a)->index <= i + chunk_size)
		{
			pb(a, b);
			i++;
		}
		else
		{
			ra(a);
		}
	}
}

static int  find_max_index_pos(t_stack_node *b, int max_idx)
{
	t_stack_node	*curr;
	int				pos;

	pos = 0;
	curr = b;
	while (curr->index != max_idx)
	{
		pos++;
		curr = curr->next;
	}
	return (pos);
}

void	complex_sort(t_stack_node **a, t_stack_node **b)
{
	int	size;
	int	pos;

	set_stack_indices(*a);
	size = get_stack_size(*a);
	push_complex_chunks(a, b, size);
	while (*b)
	{
		size = get_stack_size(*b);
		pos = find_max_index_pos(*b, size -1);
		if (pos <= size / 2)
		{
			while ((*b)->index != size -1)
				rb(b);
		}
		else
		{
			while ((*b)->index != size - 1)
				rrb(b);
		}
		pa(b, a);
	}
}
