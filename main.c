/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:27:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/06 17:33:29 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//TODO: remove after testing
void	print_stack(t_stack *stack)
{
	if (!stack)
		return ;
	while (stack)
	{
		printf("Index: %d, Value: %d\n", stack->index, stack->value);
		stack = stack->next;
	}
}

void	assign_indexes(t_push_swap_data *data)
{
	int		index;
	t_stack	*min;

	index = 0;
	min = find_min_number_no_index(data->a);
	while (min)
	{
		min->index = index;
		min->data = data;
		index++;
		min = find_min_number_no_index(data->a);
	}
}

int	main(int argc, char **argv)
{
	t_push_swap_data	data;

	init_data(&data);
	parse_data(argc, argv, &data);
	compute_disorder(&data);
	choose_strategy(&data);
	assign_indexes(&data);
	sort_stack(&data);
	if (data.is_benchmark)
		print_benchmark_data(&data);
	//print_stack(data.a);
	free_data(&data);
	return (0);
}
