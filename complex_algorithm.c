/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:07:07 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/26 18:44:46 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_complex(t_push_swap_data *data)
{
	radix_sort(&data->a, &data->b);
}

void	radix_sort(t_stack **a, t_stack **b)
{
}
