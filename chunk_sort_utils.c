/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:07:02 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/08 17:02:26 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	chunk_size(t_stack *a)
{
	int	chunk_size;
	int	chunk_count;
	int	size;

	size = size_of_stack(a);
	chunk_count = 0;
	while (chunk_count * chunk_count <= size)
		chunk_count++;
	size = size_of_stack(a);
	chunk_size = size / chunk_count;
	return (chunk_size);
}

void	update_chunk(int *min, int *max, int size_of_chunk, int size_of_stack)
{
	*min = *max + 1;
	*max = *min + size_of_chunk - 1;
	if (*max >= size_of_stack)
		*max = size_of_stack - 1;
}

int	count_in_range(t_stack *a, int min, int max)
{
	int	count;

	count = 0;
	while (a)
	{
		if (a->index >= min && a->index <= max)
			count++;
		a = a->next;
	}
	return (count);
}

int	find_max_index(t_stack *stack)
{
	int	max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	find_position(t_stack *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (pos);
}
