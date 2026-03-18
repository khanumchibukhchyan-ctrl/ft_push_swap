/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 19:50:21 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/18 17:29:15 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_data(t_push_swap_data *data)
{
	free_stack(&(data->a));
	free_stack(&(data->b));
}

void	free_stack(t_stack	**stack)
{
	t_stack	*temp;

	if (!stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free (*stack);
		*stack = temp;
	}
}

void	print_error(int error, char *msg, t_push_swap_data *data)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 1);
	free_data(data);
	exit(error);
}
