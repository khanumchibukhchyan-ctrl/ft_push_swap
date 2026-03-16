/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:24:18 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/14 19:12:48 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	compute_disorder(t_push_swap_data *data)
{
	int		mistakes;
	int		total_pairs;
	t_stack	*current;

	mistakes = 0;
	total_pairs = 0;
	current = data->a;
	while (current && current->next)
	{
		total_pairs++;
		if (current->value > current->next->value)
			mistakes++;
		current = current->next;
	}
	if (total_pairs == 0)
		data->disorder_metric = 0.0f;
	else
		data->disorder_metric = (float)(mistakes / total_pairs);
}
