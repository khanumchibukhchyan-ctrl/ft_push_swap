/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:07:09 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/05 19:04:44 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_medium(t_push_swap_data *data)
{
	chunk_sort(&data->a, &data->b);
}

void	push_back_sorted(t_stack **a, t_stack **b)
{
	int	max_index;
	int	position;
	int	size;

	while (*b)
	{
		size = size_of_stack(*b);
		max_index = find_max_index(*b);
		position = find_position(*b, max_index);
		if (position <= size / 2)
		{
			while ((*b)->index != max_index)
				rotate(b, "rb");
		}
		else
		{
			while ((*b)->index != max_index)
				reverse_rotate(b, "rrb");
		}
		push(b, a, "pa");
	}
}

void	chunk_sort(t_stack **a, t_stack **b)
{
	int	min;
	int	max;
	int	size;
	int	size_of_chunk;

	min = 0;
	size = size_of_stack(*a);
	size_of_chunk = chunk_size(*a);
	max = size_of_chunk - 1;
	while (*a)
	{
		if (count_in_range(*a, min, max) == 0)
				update_chunk(&min, &max, size_of_chunk, size);
		if ((*a)->index >= min && (*a)->index <= max)
		{
			push(a, b, "pb");
			if ((*b) && (*b)->index < ((min + max) / 2))
				rotate(b, "rb");
		}
		else
			rotate(a, "ra");
	}
	push_back_sorted(a, b);
}
