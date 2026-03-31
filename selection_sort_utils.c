/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 13:42:46 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/29 14:10:16 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	position_of_target(t_stack	*stack, t_stack *target)
{
	int	position;

	position = 0;
	while (stack)
	{
		if (stack == target)
			return (position);
		position++;
		stack = stack->next;
	}
	return (-1);
}

t_stack	*find_minimum(t_stack *stack)
{
	t_stack	*min;

	min = stack;
	while (stack)
	{
		if (stack->value < min->value)
			min = stack;
		stack = stack->next;
	}
	return (min);
}

void	bring_to_top(t_stack **a, t_stack *target)
{
	int	pos;
	int	size;

	size = size_of_stack(*a);
	pos = position_of_target(*a, target);
	if (pos <= size / 2)
	{
		while ((*a) != target)
			rotate(a, "ra");
	}
	else
	{
		while ((*a) != target)
			reverse_rotate(a, "rra");
	}
}
