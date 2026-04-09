/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:07:07 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/09 20:30:46 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_complex(t_push_swap_data *data)
{
	radix_sort(&data->a, &data->b);
}

int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = 0;
	while (a)
	{
		if (a->index > max)
			max = a->index;
		a = a->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack **a, t_stack **b)
{
	int		i;
	int		j;
	int		size;
	int		max_bits;
	t_stack	*head;

	size = size_of_stack(*a);
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			head = *a;
			if (((head->index >> i) & 1) == 1)
				rotate(a, "ra");
			else
				push(a, b, "pb");
			j++;
		}
		while (*b)
			push(b, a, "pa");
		i++;
	}
}
