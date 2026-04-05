/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:35:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/05 14:25:46 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_operation_type(char *operation)
{
	if (ft_strcmp(operation, "pa") == 0)
		return (PUSH_A);
	if (ft_strcmp(operation, "pb") == 0)
		return (PUSH_B);
	if (ft_strcmp(operation, "sa") == 0)
		return (SWAP_A);
	if (ft_strcmp(operation, "sb") == 0)
		return (SWAP_B);
	if (ft_strcmp(operation, "ss") == 0)
		return (SWAP_BOTH);
	if (ft_strcmp(operation, "ra") == 0)
		return (ROTATE_A);
	if (ft_strcmp(operation, "rb") == 0)
		return (ROTATE_B);
	if (ft_strcmp(operation, "rr") == 0)
		return (ROTATE_BOTH);
	if (ft_strcmp(operation, "rra") == 0)
		return (REVERSE_ROTATE_A);
	if (ft_strcmp(operation, "rrb") == 0)
		return (REVERSE_ROTATE_B);
	if (ft_strcmp(operation, "rrr") == 0)
		return (REVERSE_ROTATE_BOTH);
	return (-1);
}

int	total_operations(t_push_swap_data *data)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < OPERATIONS_COUNT)
	{
		total += data->operations_count[i++];
	}
	return (total);
}
