/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:18:32 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/05 19:44:28 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_disorder(t_push_swap_data *data)
{
	char	*disorder_str;
	char	*percent_str;
	int		whole;
	int		decimal;

	ft_putstr_fd("[bench] disorder: ", 2);
	whole = (int)(data->disorder_metric * 100);
	decimal = (int)(data->disorder_metric * 10000) % 100;
	disorder_str = ft_itoa(whole);
	ft_putstr_fd(disorder_str, 2);
	free(disorder_str);
	ft_putchar_fd('.', 2);
	percent_str = ft_itoa(decimal);
	if (decimal < 10)
		ft_putchar_fd('0', 2);
	ft_putstr_fd(percent_str, 2);
	free(percent_str);
	ft_putstr_fd("%\n", 2);
}

void	print_strategy(t_push_swap_data *data)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (data->strategy == SIMPLE)
		ft_putstr_fd("Simple / O(n²)\n", 2);
	else if (data->strategy == MEDIUM)
		ft_putstr_fd("Medium / O(n√n)\n", 2);
	else if (data->strategy == COMPLEX)
		ft_putstr_fd("Complex / O(n·log n)\n", 2);
	else
		ft_putstr_fd("Unknown\n", 2);
}

void	print_total_ops(t_push_swap_data *data)
{
	char	*ops_str;
	int		total;
	int		i;

	total = 0;
	i = 0;
	while (i < OPERATIONS_COUNT)
		total += data->operations_count[i++];
	ft_putstr_fd("[bench] total_ops: ", 2);
	ops_str = ft_itoa(total);
	ft_putstr_fd(ops_str, 2);
	free(ops_str);
	ft_putchar_fd('\n', 2);
}

void	print_operations_line1(t_push_swap_data *data)
{
	char	*num_str;

	ft_putstr_fd("[bench] sa: ", 2);
	num_str = ft_itoa(data->operations_count[SWAP_A]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  sb: ", 2);
	num_str = ft_itoa(data->operations_count[SWAP_B]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  ss: ", 2);
	num_str = ft_itoa(data->operations_count[SWAP_BOTH]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
}

void	print_operations_line2(t_push_swap_data *data)
{
	char	*num_str;

	ft_putstr_fd("  pa: ", 2);
	num_str = ft_itoa(data->operations_count[PUSH_A]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putstr_fd("  pb: ", 2);
	num_str = ft_itoa(data->operations_count[PUSH_B]);
	ft_putstr_fd(num_str, 2);
	free(num_str);
	ft_putchar_fd('\n', 2);
}