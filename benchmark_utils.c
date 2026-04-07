/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:35:48 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/06 14:31:14 by kchibukh         ###   ########.fr       */
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

void	print_rotations_line1(t_push_swap_data *data)
{
	char	*num_str;

	ft_putstr_fd("[bench] ra: ", 2);
	num_str = ft_itoa(data->operations_count[ROTATE_A]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  rb: ", 2);
	num_str = ft_itoa(data->operations_count[ROTATE_B]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  rr: ", 2);
	num_str = ft_itoa(data->operations_count[ROTATE_BOTH]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
}

void	print_rotations_line2(t_push_swap_data *data)
{
	char	*num_str;

	ft_putstr_fd("  rra: ", 2);
	num_str = ft_itoa(data->operations_count[REVERSE_ROTATE_A]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  rrb: ", 2);
	num_str = ft_itoa(data->operations_count[REVERSE_ROTATE_B]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  rrr: ", 2);
	num_str = ft_itoa(data->operations_count[REVERSE_ROTATE_BOTH]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putchar_fd('\n', 2);
}

void	print_benchmark_data(t_push_swap_data *data)
{
	print_disorder(data);
	print_strategy(data);
	print_total_ops(data);
	print_operations_line1(data);
	print_operations_line2(data);
	print_rotations_line1(data);
	print_rotations_line2(data);
}
