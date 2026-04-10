/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:54:40 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/10 20:24:01 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ss(t_stack **a, t_stack **b, char *msg)
{
	swap(a, NULL);
	swap(b, NULL);
	if (msg)
	{
		if (*a && (*a)->data && (*a)->data->is_benchmark)
			(*a)->data->operations_count[SWAP_BOTH]++;
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	rr(t_stack **a, t_stack **b, char *msg)
{
	rotate(a, NULL);
	rotate(b, NULL);
	if (msg)
	{
		if (*a && (*a)->data && (*a)->data->is_benchmark)
			(*a)->data->operations_count[ROTATE_BOTH]++;
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	rrr(t_stack **a, t_stack **b, char *msg)
{
	reverse_rotate(a, NULL);
	reverse_rotate(b, NULL);
	if (msg)
	{
		if (*a && (*a)->data && (*a)->data->is_benchmark)
			(*a)->data->operations_count[REVERSE_ROTATE_BOTH]++;
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
}
