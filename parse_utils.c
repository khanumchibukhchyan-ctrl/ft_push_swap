/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:40:58 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/16 19:31:09 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*join_args(int argc, char **argv)
{
	int		i;
	char	*result;
	char	*temp;

	i = 1;
	result = ft_strdup(argv[1]);
	while (i < argc)
	{
		temp = ft_strjoin(result, " ");
		free(result);
		result = ft_strjoin(temp, argv[i]);
		free(temp);
		i++;
	}
	return (result);
}

void	build_stack(char **nums, t_list **stack)
{
	int	i;

	i = 0;
	while (nums[i])
	{
		ft_lstadd_back(stack, ft_lstnew(ft_atoi(nums[i])));
		i++;
	}
}

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
