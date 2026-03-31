/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:27:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/31 17:42:58 by kchibukh         ###   ########.fr       */
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
		// ft_putnbr_fd(stack->value, 1);
		// write(1, "\n", 1);
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
	print_stack(data.a);
	free_data(&data);
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	char **temp = ft_split("  556 4 56 7 54     56 77 8", ' ');
// 	int i = -1;
// 	while (temp[i++])
// 		printf("%s\n", temp[i]);

// 	return 0;
// }
