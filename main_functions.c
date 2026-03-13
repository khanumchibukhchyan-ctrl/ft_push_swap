/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:40:41 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/13 21:23:46 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_data(t_pushswap_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->strategy = ADAPTIVE;
	data->is_benchmark = false;
	data->disorder_metric = 0.0f;
}

void	parse_data(t_pushswap_data data)
{
	
}
