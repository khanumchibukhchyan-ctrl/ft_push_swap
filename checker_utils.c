/* ************************************************************************** */
/*																	        */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:58:01 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/11 15:35:48 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	read_and_execute(t_push_swap_data *data)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (line[0] && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			print_error(1, NULL, data);
		}
		if (get_operation_type(line) == -1)
		{
			free(line);
			print_error(1, NULL, data);
		}
		execute_instruction(line, &(data->a), &(data->b));
		free(line);
		line = get_next_line(STDIN_FILENO);
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
