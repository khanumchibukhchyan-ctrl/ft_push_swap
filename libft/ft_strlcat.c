/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:23:30 by kchibukh          #+#    #+#             */
/*   Updated: 2026/02/09 14:57:23 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dest);
	s = ft_strlen(src);
	if (src && dest)
	{
		if (d >= size)
			return (size + s);
		i = 0;
		while (src[i] && d + i < size - 1)
		{
			dest[d + i] = src[i];
			i++;
		}
		dest[i + d] = '\0';
		return (d + s);
	}
	return (0);
}
