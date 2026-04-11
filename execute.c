/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:52:01 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/11 15:27:06 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	execute_instruction(char *line, t_stack **a, t_stack **b)
{
	int	op;

	op = get_operation_type(line);
	if (op == PUSH_A)
		push(b, a, NULL);
	else if (op == PUSH_B)
		push(a, b, NULL);
	else if (op == SWAP_A)
		swap(a, NULL);
	else if (op == SWAP_B)
		swap(b, NULL);
	else if (op == SWAP_BOTH)
		ss(a, b, NULL);
	else if (op == ROTATE_A)
		rotate(a, NULL);
	else if (op == ROTATE_B)
		rotate(b, NULL);
	else if (op == ROTATE_BOTH)
		rr(a, b, NULL);
	else if (op == REVERSE_ROTATE_A)
		reverse_rotate(a, NULL);
	else if (op == REVERSE_ROTATE_B)
		reverse_rotate(b, NULL);
	else if (op == REVERSE_ROTATE_BOTH)
		rrr(a, b, NULL);
}
