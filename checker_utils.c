/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:58:01 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/10 19:40:56 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	read_and_execute(t_stack **a, t_stack **b)
{
	char	*line;

	line = get_next_line(0);
	while ((line))
	{
		if ((line[0] && line[ft_strlen(line) - 1] == '\n'))
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			error_exit(a, b);
		}
		if (get_operation_type(line) == -1)
		{
			free(line);
			error_exit(a, b);
		}
		execute_instruction(line, a, b);
		free(line);
	}
}

int	is_sorted(t_stack *a)
{
	while (a && a->next)
	{
		if (a->value > a->next->value)
			return (0);
		a = a->next;
	}
	return (1);
}

void	error_exit(t_stack **a, t_stack **b)
{
	write(2, "Error\n", 6);
	free_stack(a);
	free_stack(b);
	exit(1);
}
