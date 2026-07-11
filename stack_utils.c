#include "push_swap.h"

t_stack_node    *create_node(int value)
{
	t_stack_node    *node;

	node = malloc(sizeof(t_stack_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void    append_node(t_stack_node **head, t_stack_node *new_node)
{
	t_stack_node	*last;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
		return ;
	}
	last = (*head)->prev;
	last->next = new_node;
	new_node->prev = last;
	new_node->next = *head;
	(*head)->prev = new_node;
}

void	free_stack(t_stack_node **head)
{
	t_stack_node	*current;
	t_stack_node	*next_node;
	t_stack_node	*last;

	if (!head || !*head)
		return ;
	current = *head;
	last = (*head)->prev;
	while (current != last)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	free(last);
	*head = NULL;
}
