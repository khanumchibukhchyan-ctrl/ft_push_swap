/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:04:37 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/10 18:19:19 by kchibukh         ###   ########.fr       */
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
	if (!a || !(*a) || !(*a)->next)
		return ;
	if ((*a)->value > (*a)->next->value)
		swap(a, "sa");
}

void	sort_three(t_stack **a)
{
	int	top;
	int	mid;
	int	bot;

	top = (*a)->value;
	mid = (*a)->next->value;
	bot = (*a)->next->next->value;
	if (top > mid && top > bot && mid < bot)
		rotate(a, "ra");
	else if (top < mid && mid > bot && top < bot)
	{
		reverse_rotate(a, "rra");
		swap(a, "sa");
	}
	else if (top > mid && top < bot)
		swap(a, "sa");
	else if (top < mid && mid > bot && top > bot)
		reverse_rotate(a, "rra");
	else if (top > mid && mid > bot)
	{
		swap(a, "sa");
		reverse_rotate(a, "rra");
	}
}

void	push_min_to_top(t_stack **stack)
{
	t_stack	*min_node;
	t_stack	*current;
	int		min_position;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	min_node = find_minimum(*stack);
	min_position = 0;
	current = *stack;
	while (current != min_node)
	{
		min_position++;
		current = current->next;
	}
	if (min_position <= size_of_stack(*stack) / 2)
	{
		while (*stack != min_node)
			rotate(stack, "ra");
	}
	else
	{
		while (*stack != min_node)
			reverse_rotate(stack, "rra");
	}
}

void	sort_five(t_push_swap_data *data)
{
	while (size_of_stack(data->a) > 3)
	{
		push_min_to_top(&data->a);
		push(&data->a, &data->b, "pb");
	}
	sort_three(&data->a);
	while (data->b)
		push(&data->b, &data->a, "pa");
}
