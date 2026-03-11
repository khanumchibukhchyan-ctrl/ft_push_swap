/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:27:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/09 18:59:26 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_strategy	strategy;

	if (argc < 2)
		return (0);
	parse_args(argc, argv);
	init_stack(&stack_a, &stack_b, argc, argv);
	sort_stack(stack_a, stack_b, strategy);
	return (0);
}
