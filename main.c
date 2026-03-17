/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:27:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/17 21:20:09 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *stack)
{
	if (!stack)
		return;
	while (stack)
	{
		ft_putnbr_fd(stack->value, 1);
		write(1, "\n", 1);
		stack = stack->next;
	}
}

int	main(int argc, char **argv)
{
	t_push_swap_data	data;

	init_data(&data);
	parse_data(argc, argv, &data);
	print_stack(data.a);
	// sort_stack(&data);
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