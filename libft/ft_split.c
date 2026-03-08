/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/02/13 18:16:02 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	w_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_all(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
	return (NULL);
}

static size_t	w_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	new = ft_calloc(w_count(s, c) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			new[j] = ft_calloc(w_len(&s[i], c) + 1, sizeof(char));
			if (!new[j])
				return (free_all(new, j));
			ft_strlcpy(new[j++], &s[i], w_len(&s[i], c) + 1);
			i += w_len(&s[i], c);
		}
		else
			i++;
	}
	return (new);
}
