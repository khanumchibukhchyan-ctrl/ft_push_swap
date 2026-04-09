/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:40:41 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/09 19:49:23 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_data(t_push_swap_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->strategy = NONE;
	data->is_benchmark = false;
	data->disorder_metric = 0.0f;
	ft_memset(data->operations_count, 0, sizeof(int) * OPERATIONS_COUNT);
}

void	choose_strategy(t_push_swap_data *data)
{
	if (data->strategy == ADAPTIVE)
	{
		data->is_adaptive = true;
		if (data->disorder_metric < 0.2)
			data->strategy = SIMPLE;
		else if (data->disorder_metric < 0.5)
			data->strategy = MEDIUM;
		else
			data->strategy = COMPLEX;
	}
}

void	sort_stack(t_push_swap_data *data)
{
	int	size;

	if (data->disorder_metric == 0.0f)
		return ;
	size = size_of_stack(data->a);
	if (size <= 1)
		return ;
	if (size == 2)
		sort_two(&data->a);
	else if (size == 3)
		sort_three(&data->a);
	else if (size <= 5)
		sort_five(data);
	else if (data->strategy == SIMPLE)
		sort_simple(data);
	else if (data->strategy == MEDIUM)
		sort_medium(data);
	else
		sort_complex(data);
}

void	check_flag(char *argv, t_push_swap_data *data)
{
	if (!ft_strcmp(argv, "--bench"))
		data->is_benchmark = true;
	else if (!ft_strcmp(argv, "--simple") || !ft_strcmp(argv, "--medium")
		|| !ft_strcmp(argv, "--complex") || !ft_strcmp(argv, "--adaptive"))
	{
		if (data->strategy != NONE)
			print_error(3, "Multiple strategy flags provided", data);
		if (!ft_strcmp(argv, "--simple"))
			data->strategy = SIMPLE;
		else if (!ft_strcmp(argv, "--medium"))
			data->strategy = MEDIUM;
		else if (!ft_strcmp(argv, "--complex"))
			data->strategy = COMPLEX;
		else if (!ft_strcmp(argv, "--adaptive"))
			data->strategy = ADAPTIVE;
	}
	else
		print_error(3, "Invalid flag provided", data);
}

void	parse_data(int argc, char **argv, t_push_swap_data *data)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	if (argc < 2)
		exit(0);
	while (++i < argc)
	{
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == '-')
		{
			check_flag(argv[i], data);
			continue ;
		}
		if (argv[i] && ft_strchr(argv[i], ' '))
		{
			j = -1;
			temp = ft_split(argv[i], ' ');
			while (temp[++j])
				push_to_stack(temp[j], data);
			free_string_array(temp);
		}
		else if (argv[i])
			push_to_stack(argv[i], data);
	}
}
