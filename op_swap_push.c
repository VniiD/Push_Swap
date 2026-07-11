#include "push_swap.h"

void	swap(t_stack_node **head)
{
	t_stack_node	*first;
	t_stack_node	*second;
	int				tmp_val;
	int				tmp_idx;

	if (!head || !*head || (*head)->next == *head)
		return ;
	first = *head;
	second = first->next;
	tmp_val = first->value;
	tmp_idx = first->index;
	first->value = second->value;
	first->index = second->index;
	second->value = tmp_val;
	second->index = tmp_idx;
}

static t_stack_node	*detach_node(t_stack_node **src)
{
	t_stack_node	*push_node;

	push_node = *src;
	if (push_node->next == push_node)
		*src = NULL;
	else
	{
		push_node->prev->next = push_node->next;
		push_node->next->prev = push_node->prev;
		*src = push_node->next;
	}
	return (push_node);
}


void	push(t_stack_node **src, t_stack_node **dst)
{
	t_stack_node	*push_node;

	if (!src || !*src)
		return ;
	push_node = detach_node(src);
	if (!*dst)
	{
		*dst = push_node;
		push_node->next = push_node;
		push_node->prev = push_node;
	}
	else
	{
		push_node->next = *dst;
		push_node->prev = (*dst)->prev;
		(*dst)->prev->next = push_node;
		(*dst)->prev = push_node;
		*dst = push_node;
	}
}
