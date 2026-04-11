/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:51:33 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/11 15:36:16 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_push_swap_data	data;

	init_data(&data);
	parse_data(argc, argv, &data);
	read_and_execute(&data);
	if (is_sorted(data.a) && data.b == NULL)
		write (1, "OK\n", 3);
	else
		write (1, "KO\n", 3);
	free_data(&data);
	return (0);
}
