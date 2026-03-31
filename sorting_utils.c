/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:04:37 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/29 13:43:44 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	size_of_stack(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}

void	sort_two(t_stack **a)
{
	if ((*a)->value > (*a)->next->value)
		swap(a, "sa");
}

void	sort_three(t_stack **a)
{
	int	top;
	int	middle;
	int	bottom;

	top = (*a)->value;
	middle = (*a)->next->value;
	bottom = (*a)->next->next->value;
	if (top < middle && middle > bottom)
	{
		reverse_rotate(a, "rra");
		if (top < bottom)
			swap(a, "sa");
	}
	else if (top > middle && top > bottom)
	{
		rotate(a, "ra");
		if (middle > bottom)
			swap(a, "sa");
	}
	else
		swap(a, "sa");
}
