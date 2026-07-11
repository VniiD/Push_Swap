
#include "push_swap.h"

void	sa(t_stack_node **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void	ra(t_stack_node **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void	rra(t_stack_node **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

void	pb(t_stack_node **a, t_stack_node **b)
{
	push(a, b);
	write(1, "pb\n", 3);
}
