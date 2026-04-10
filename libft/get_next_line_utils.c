/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:37:45 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/10 20:17:11 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *l1, const char *l2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!l1 || !l2)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc(ft_strlen(l1) + ft_strlen(l2) + 1);
	if (!new)
		return (NULL);
	while (l1[i] != '\0')
	{
		new[i] = l1[i];
		i++;
	}
	while (l2[j] != '\0')
	{
		new[i + j] = l2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}
