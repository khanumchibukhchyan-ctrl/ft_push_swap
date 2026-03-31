/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:12:14 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/28 14:49:25 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **stack1, t_stack **stack2, char *msg)
{
	t_stack	*temp;

	if (!stack1 || !*stack1)
		return ;
	temp = *stack1;
	*stack1 = (*stack1)->next;
	temp->next = *stack2;
	*stack2 = temp;
	if (msg)
	{
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	swap(t_stack **stack, char *msg)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = (*stack)->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	if (msg)
	{
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	rotate(t_stack **stack, char *msg)
{
	t_stack	*temp;
	t_stack	*current;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = *stack;
	current = *stack;
	*stack = (*stack)->next;
	while (current->next != NULL)
		current = current->next;
	current->next = temp;
	temp->next = NULL;
	if (msg)
	{
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	reverse_rotate(t_stack **stack, char *msg)
{
	t_stack	*last;
	t_stack	*prelast;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	prelast = *stack;
	while (prelast->next != NULL && prelast->next->next != NULL)
		prelast = prelast->next;
	last = prelast->next;
	last->next = *stack;
	prelast->next = NULL;
	*stack = last;
	if (msg)
	{
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}
