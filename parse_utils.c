/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:40:58 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/26 16:53:34 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_stack(char *num, t_push_swap_data *data)
{
	int	temp;

	temp = ft_atol(num, data);
	if (is_num_repeat(temp, data->a))
		print_error(5, "Duplicates found", data);
	lstadd_back(&(data->a), lstnew(temp));
}

void	free_string_array(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0 ;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_stack	*find_min_number_no_index(t_stack *stack)
{
	t_stack	*min_num;
	t_stack	*iterator;

	if (!stack)
		return (NULL);
	iterator = stack;
	min_num = NULL;
	while (iterator)
	{
		if (iterator->index == -1)
		{
			if (min_num == NULL || iterator->value < min_num->value)
				min_num = iterator;
		}
		iterator = iterator->next;
	}
	return (min_num);
}

bool	is_num_repeat(int num, t_stack *stack)
{
	while (stack)
	{
		if (num == stack->value)
			return (true);
		stack = stack->next;
	}
	return (false);
}
