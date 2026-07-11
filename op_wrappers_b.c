
#include "push_swap.h"

void	rb(t_stack_node **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void	rrb(t_stack_node **b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}

void	pa(t_stack_node **b, t_stack_node **a)
{
	push(b, a);
	write(1, "pa\n", 3);
}
