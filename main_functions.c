/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:40:41 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/16 19:46:42 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_data(t_push_swap_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->strategy = ADAPTIVE;
	data->is_benchmark = false;
	data->disorder_metric = 0.0f;
}

void	sort_stack(t_push_swap_data *data)
{
	if (data->disorder_metric == 0.0f)
		return ;
	if (data->strategy == ADAPTIVE)
	{
		if (data->disorder_metric < 0.2)
			data->strategy = SIMPLE;
		else if (data->disorder_metric < 0.5)
			data->strategy = MEDIUM;
		else
			data->strategy = COMPLEX;
	}
	if (data->strategy == SIMPLE)
		sort_simple(data);
	else if (data->strategy == MEDIUM)
		sort_medium(data);
	else
		sort_complex(data);
}

void	parse_data(int argc, char **argv, t_push_swap_data *data)
{
	int		i;
	char	*joined;
	char	**result;

	i = 0;
	if (argc < 2)
		print_error(1);
	while (++i < argc)
	{
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == '-')
			check_flag(argv[i], data);
		if (validate_argv_element(argv[i]))
			print_error(1, "Validation error\n");
	}
	joined = join_args(argc, argv);
	result = ft_split(joined, ' ');
	build_stack(result, &data->a);
	free(joined);
	free_string_array(result);
}

bool	validate_argv_element(char *elem)
{
	int	i;

	i = 0;
	if (elem[0] == '-' || elem[0] == '+')
		i++;
	if (!elem[i])
		return (false);
	while (elem[i])
	{
		if (!ft_isdigit(elem[i]))
			return (false);
		i++;
	}
}

void	check_flag(char *argv, t_push_swap_data *data)
{
	if (!ft_strncmp(argv, "--bench", 7)
		&& (argv[7] == '\0' || ft_isspace(argv[7])))
		data->is_benchmark = true;
	else if (!ft_strncmp(argv, "--simple", 8)
		&& (argv[8] == '\0' || ft_isspace(argv[8])))
		data->strategy = SIMPLE;
	else if (!ft_strncmp(argv, "--medium", 8)
		&& (argv[8] == '\0' || ft_isspace(argv[8])))
		data->strategy = MEDIUM;
	else if (!ft_strncmp(argv, "--complex", 9)
		&& (argv[9] == '\0' || ft_isspace(argv[9])))
		data->strategy = COMPLEX;
	else if (!ft_strncmp(argv, "--adaptive", 10)
		&& (argv[10] == '\0' || ft_isspace(argv[10])))
		data->strategy = ADAPTIVE;
	else
		print_error(1, "");
}
