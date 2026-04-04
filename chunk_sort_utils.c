/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:07:02 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/04 17:00:18 by kchibukh         ###   ########.fr       */
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
	while (size > 1)
	{
		size = size / 2;
		chunk_count++;
	}
	chunk_size = size / chunk_count;
	return (chunk_size);
}

void	update_chunk(int min, int max, int size_of_chunk, int size_of_stack)
{
	min += size_of_chunk;
	max += size_of_chunk;
	if (max >= size_of_stack)
		max = size_of_stack - 1;
}
