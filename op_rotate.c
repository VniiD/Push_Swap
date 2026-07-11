#include "push_swap.h"

void    rotate(t_stack_node **head)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->next;
}

void    reverse_rotate(t_stack_node **head)
{
	if (!head || !*head || (*head)->next == *head)
		return ;
	*head = (*head)->prev;
}
