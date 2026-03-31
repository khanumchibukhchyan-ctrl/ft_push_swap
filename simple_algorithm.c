/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:07:12 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/29 14:15:03 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_simple(t_push_swap_data *data)
{
	selection_sort(&data->a, &data->b);
}

void	selection_sort(t_stack **a, t_stack **b)
{
	t_stack	*min;
	int		size;

	size = size_of_stack(*a);
	while (size > 3)
	{
		min = find_minimum(*a);
		bring_to_top(a, min);
		push(a, b, "pb");
		size--;
	}
	sort_three(a);
	while (*b)
		push(b, a, "pa");
}
